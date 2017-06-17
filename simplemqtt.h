#include <PubSubClient.h>

#ifndef simplemqtt_H
#define simplemqtt_H

void initMQTT_cli(const char *domain_host, uint16_t port, PubSubClient cli, const char *user, const char *pwd, const char *cli_ID);
void initMQTT_cli_callBack();

void MQTT_cli_ReConnect(const char *subTopic);

bool MQTT_cli_subscribe(const char *topic, uint8_t qos);

bool MQTT_cli_unSubscribe(const char* topic);

String MQTT_cli_callBack_Subscribe_Msg_String();

bool MQTT_cli_publish(const char* topic, const char* payload, bool retained);

void MQTT_cli_loop();

void MQTT_cli_disconnect();	

#endif
