#include "simplemqtt.h"

PubSubClient pubcli;
const char *host;
uint16_t port;
const char *user;
const char *pswd;
const char *cli_ID;

String Simplemqtt_Subscribe_Msg_String;

void initSimplemqtt(const char *domain_host, uint16_t port, PubSubClient cli, const char *user, const char *pwd, const char *cli_ID)
{
	host = domain_host;
	port = port;
	pubcli = cli;
	user = user;
	pswd = pwd;
	cli_ID = cli_ID;
	pubcli.setServer(host, port);
	MQTT_cli_Subscribe_Msg_String = "";
}

void Simplemqtt_ReConnect(const char *subTopic)
{
	while(!pubcli.connected()){
#if DEBUX_MQTT
		Serial.println("Attempt Mqtt connection");
#endif
		if(pubcli.connect(cli_ID, user, pswd)){
#if DEBUX_MQTT
			Serial.println("Mqtt Connected");
#endif
			if(pubcli.subscribe(subTopic, 1)){
#if DEBUX_MQTT
				Serial.println("Success Subscribe");
#endif				
			}else{
				// todo:
			}
		} else {
#if DEBUX_MQTT
			Serial.print("failed, rc=");
			Serial.print(pubcli.state());
			Serial.println(" try again in 5 seconds");
#endif
			delay(5000);
		}
	}
}

bool Simplemqtt_subscribe(const char *topic, uint8_t qos)
{
	return pubcli.subscribe(topic, qos);
}

bool MQTT_cli_unSubscribe(const char* topic)
{
	return pubcli.unsubscribe(topic);
}


void Simplemqtt_callback_fn(char* topic, byte* payload, unsigned int length)
{
#if DEBUX_MQTT
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
#endif
	MQTT_cli_Subscribe_Msg_String = "";
	for (int i = 0; i < length; i++) {
		MQTT_cli_Subscribe_Msg_String += (char)payload[i];
#if DEBUX_MQTT
		Serial.print((char)payload[i]);
#endif
	}
}

void initSimplemqtt_callBack()
{
	pubcli.setCallback(MQTT_cli_callback_fn);
}

String Simplemqtt_callBack_Subscribe_Msg_String()
{
	return MQTT_cli_Subscribe_Msg_String;
}

bool Simplemqtt_publish(const char* topic, const char* payload, bool retained)
{
	return pubcli.publish(topic, payload, retained);
}

void Simplemqtt_loop()
{
	pubcli.loop();
}

void Simplemqtt_disconnect()
{
	pubcli.disconnect();
}

