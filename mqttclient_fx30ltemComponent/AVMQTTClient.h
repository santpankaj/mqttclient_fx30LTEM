#ifndef AVMQTTCLIENT_H
#define AVMQTTCLIENT_H

typedef void AV_MQTT_ConnectionLost(char* cause);

/* Initiliaze a MQTT client then connection this client to AirVantage
 * AV_MQTT_ConnectionLost* connHandler function is a hook to notify the user when the MQTT connection is lost
 */
int AV_MQTT_connect(const char* username, const char* password, AV_MQTT_ConnectionLost* connHandler);

/* Publish message given as parameter to AV MQTT message topic*/
int AV_MQTT_publishMessage(const char* message);

#endif //AVMQTTCLIENT_H
