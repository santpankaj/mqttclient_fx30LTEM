#include "legato.h"

#include "MQTTClient.h"
#include "AVMQTTClient.h"

#define MQTT_SSL_SERVER     "ssl://eu.airvantage.net:8883"
// AirVantage public certificate. Must be bundled into application. See Component.cdef
#define AV_PUBLIC_CRT_FILE  "/cert/gdroot-g2.crt"

static AV_MQTT_ConnectionLost* connHandler;
static MQTTClient client;

static char pubTopic[100] = { '0' };
static char tasktopic[100] = { '0' };
static char ackTopic[100] = { '0' };

/*
 * This function is called by the paho library each time a message is received on subscribed topics
 */
static int onReceivedMessage(void* context, char* topicName, int topicLen, MQTTClient_message* m)
{
    LE_INFO("Got message from server on topic %s", topicName);
    LE_INFO("Message: %s", (char* )m->payload);
    /*
     * This piece of code does not parse the entire message.
     * It just shows how to receive and ack messages coming from AirVantage:
     *  1 - Parse the message and retrieve UID of the message
     *  2 - Get message type : write | command
     *  3 - Finish message parsing according to the type of the message then do the specific treatment
     *  4 - Finally acknowledge of nack the command using the retrieved UID
     */
    char message[100] = { '0' };
    char uid[128] = { '0' };
    char* token;
    const char* delim = "\"";
    token = strtok(m->payload, delim);
    /* retrieve UID of the message */
    while (token != NULL)
    {
        if (strncmp(token, "uid", 3) == 0)
        {
            token = strtok(NULL, delim); // should be ':'
            token = strtok(NULL, delim); // should be message UID
            snprintf(uid, sizeof(uid), token);
        }
        token = strtok(NULL,delim);
    }
    /* build ack response then publish it to AirVantage "ackTopic"
     * For a complete description see:
     *        https://doc.airvantage.net/av/reference/hardware/protocols/mqtt-av/#acknowledging-tasks:340d2b256dbb6e244c6ca528a8bf510a
     */
    sprintf(message, "[{\"uid\": \"%s\", \"status\" : \"OK\"}]", uid);
    MQTTClient_publish(client, ackTopic, strlen(message), (char*) message, 0, 0, NULL);
    return 1;
}
static void onConnLost(void *context, char *cause)
{
    LE_ERROR("Connection to broker lost [%s]", cause);
    // calling user call back
    connHandler(cause);
}

int AV_MQTT_connect(const char* username, const char* password, AV_MQTT_ConnectionLost* avMqttConnHandler)
{
    int rc;
    static int initialized = 0;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_SSLOptions ssl_opts = MQTTClient_SSLOptions_initializer;

    // set AirVantage topics name
    // see https://doc.airvantage.net/av/reference/hardware/protocols/mqtt-av/ for more details
    sprintf(pubTopic, "%s/messages/json", username);
    sprintf(ackTopic, "%s/acks/json", username);
    sprintf(tasktopic, "%s/tacks/json", username);

    if (!initialized)
    {
        // Create MQTT client. Using username as clientId
        rc = MQTTClient_create(&client, MQTT_SSL_SERVER, username, MQTTCLIENT_PERSISTENCE_NONE, NULL);
        if (rc != MQTTCLIENT_SUCCESS)
        {
            LE_ERROR("Cannot create MQTT client: %d", rc);
            return rc;
        }
        initialized = 1;
    }
    else
    {
        LE_INFO("Client already created, connecting to AV");
    }
    // Incoming messages callback
    MQTTClient_setCallbacks(client, NULL, onConnLost, onReceivedMessage, NULL);
    conn_opts.keepAliveInterval = 900; // set MQTT ping to 15 minutes.
                                       // Only required to keep the connection opened if no data are sent wihtin this period
                                       // This ping introduce a small data consumption overhead, fine tune it according to your use case.
    conn_opts.reliable = 0;
    conn_opts.cleansession = 1;
    conn_opts.username = username;
    conn_opts.password = password;

    conn_opts.ssl = &ssl_opts;
    conn_opts.ssl->trustStore = AV_PUBLIC_CRT_FILE;

    LE_INFO("MQTT Client correctly configured:");
    LE_INFO("\t Server url: %s", MQTT_SSL_SERVER);
    LE_INFO("\t User name: %s", username);
    LE_INFO("\t password: %s", password);
    LE_INFO("\t Publish topic: %s", pubTopic);

    if ((rc = MQTTClient_connect(client, &conn_opts)) != 0)
    {
        LE_ERROR("Cannot connect to AirVantage :%d", rc);
    }
    else
    {
        if(MQTTClient_subscribe(client, tasktopic, 1) != 0)
        {
            LE_WARN("Cannot subscribe to AirVantage tasks topic");
            // TODO specific treatment
        }
        connHandler = avMqttConnHandler;
    }
    return rc;
}

int AV_MQTT_publishMessage(const char* message)
{
    return MQTTClient_publish(client, pubTopic, strlen(message), (char*) message, 0, 0, NULL);
}
