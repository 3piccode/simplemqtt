#include "include/PubSubClient.h"

#ifndef simplemqtt_H
#define simplemqtt_H

void initSimplemqtt(const char *domain_host, uint16_t port, const char *client_ID);

void initSimplemqtt(const char *domain_host, uint16_t port, const char *user, const char *pwd, const char *cli_ID);
void initSimplemqtt_callBack();

void Simplemqtt_ReConnect(const char *subTopic);

bool Simplemqtt_subscribe(const char *topic, uint8_t qos);

bool Simplemqtt_unSubscribe(const char* topic);

String Simplemqtt_callBack_Subscribe_Msg_String();

bool Simplemqtt_publish(const char* topic, const char* payload, bool retained);

void Simplemqtt_loop();

void Simplemqtt_disconnect();	

#endif
