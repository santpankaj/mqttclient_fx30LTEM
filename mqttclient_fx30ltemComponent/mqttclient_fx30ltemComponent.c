#include <math.h>

#include "legato.h"
#include "interfaces.h"
#include "AVMQTTClient.h"

// device identifier (IMEI)
#define MQTT_USERNAME "1234567895236"
// device password
#define MQTT_PASSWD   "123456"
// data publication period in seconds
#define PUBLISH_PERIOD 60

static le_timer_Ref_t publishTimer = NULL;
static bool isCellularConnected = false;
static bool mqttConnected = false;

static void avMqttConnLost(char* cause);
static void retryMQTTConnect(le_timer_Ref_t timer);


static double getHumidity()
{
    static double humidity = 50.0;
    /* generated a random value between -5.0 & 5.0 */
    srandom(time(0));
    long int rvalue = random();
    double delta = (((double) (rvalue % 100)) / 10) - 5;

    // add this value to humidity static var
    humidity += delta;
    return humidity;
}

static double getTemperature()
{
    static double temp = 20.0;
    /* generated a random value between -0.5 & 0.5 */
    srandom(time(0));
    long int rvalue = random();
    double delta = (((double) (rvalue % 100)) / 100) - 0.5;

    temp += delta;
    return temp;
}

static void sendData(le_timer_Ref_t timer)
{
    char message[100];
    struct timeval tv;
    uint64_t utcMilliSec;

    if(!mqttConnected)
    {
        LE_WARN("No more connected to AV, canceling data sending...");
        le_timer_Stop(timer);
        return;
    }

    // retrieve UTC time in milliseconds
    gettimeofday(&tv, NULL);
    utcMilliSec = (uint64_t) (tv.tv_sec) * 1000 + (uint64_t) (tv.tv_usec) / 1000;

    // formating data then sending them to AV
    // to have a complete description of AV MQTT format
    // see https://doc.airvantage.net/av/reference/hardware/protocols/mqtt-av/#publish-data
    sprintf(message, "{\"%llu\":{\"room.temperature\": %.1f, \"room.humidity\": %.1f }}",
            utcMilliSec, getTemperature(), getHumidity());

    LE_DEBUG("Publishing message %s", message);
    AV_MQTT_publishMessage(message);
    // TODO handle publish errors: retry, keep data in ram / filesystem to send them later
}

/*
 * Connect to the AV MQTT broker then initialize a timer to publish data to AV
 */
static void startClient()
{
    int rc = AV_MQTT_connect(MQTT_USERNAME, MQTT_PASSWD, &avMqttConnLost);
    if (rc == 0)
    {
        LE_INFO("Connected to AirVantage, starting data sending");
        mqttConnected = true;
        if (publishTimer == NULL)
        {
            publishTimer = le_timer_Create("publishTimer");
            le_clk_Time_t clk = { .sec = PUBLISH_PERIOD };
            le_timer_SetInterval(publishTimer, clk);
            le_timer_SetRepeat(publishTimer, 0);
            le_timer_SetHandler(publishTimer, sendData);
        }
        le_timer_Start(publishTimer);
    }
    else
    {
        LE_WARN("Connection to AirVantage failed %d, retrying in a minute", rc);
        le_timer_Ref_t t= le_timer_Create("publishTimer");
        le_clk_Time_t clk = { .sec = 60 };
        le_timer_SetInterval(t, clk);
        le_timer_SetRepeat(t, 1);
        le_timer_SetHandler(t, retryMQTTConnect);
        le_timer_Start(t);
    }
}

static void retryMQTTConnect(le_timer_Ref_t timer)
{
    startClient();
}

/*
 * Hook called by AVMQTTClient to handle MQTT disconnection
 */
static void avMqttConnLost(char *cause)
{
    LE_WARN("MQTT connection lost, Trying to reconnect");
    /* This callback is called from a paho thread outside any legato context
     * To be able to call a legato API current thread must be attached to legato
     */
    le_thread_InitLegatoThreadData("MQTTReconnectHandler");
    mqttConnected = false;
    if (isCellularConnected)
    {
        // cellular connection available, just try to reconnect to AV MQTT broker
        startClient();
    }
    else
    {
        LE_WARN("Network not available, waiting for a connection");
        // Do nothing else, onDataConnStateChange will restart the data polling once network will be back
    }
}

static void onDataConnStateChange(const char* intfName, bool isConnected, void* contextPtr)
{
    if (isConnected)
    {
        LE_INFO("Connected to network, trying to connect to AirVantage");
        startClient();
    }
    else
    {
        LE_WARN("Network connectivity lost");
        mqttConnected = false;
        // do nothing else, avMqttConnLost will do the job
    }
    isCellularConnected = isConnected;
}

COMPONENT_INIT
{
    le_data_SetTechnologyRank(1, LE_DATA_CELLULAR); // set Cellular connection as prefered data connection
    le_data_AddConnectionStateHandler(onDataConnStateChange, NULL); //attach a hook to data connection state
    le_data_Request(); // request a data connection
}
