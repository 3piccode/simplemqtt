#include "simplemqtt.h"

const char *host;
uint16_t port;
const char *user;
const char *pswd;
const char *cli_ID;

const char *DEBUG_X_Return;

String Simplemqtt_Subscribe_Msg_String;
String MQTT_cli_Subscribe_Msg_String;

PubSubClient pubcli;

void initSimplemqtt(const char *domain_host, uint16_t port, const char *user, const char *pwd, const char *cli_ID)
{
	host = domain_host;
	port = port;
	user = user;
	pswd = pwd;
	cli_ID = cli_ID;
	pubcli.setServer(host, port);
	MQTT_cli_Subscribe_Msg_String = "";
}

void initSimplemqtt(const char *domain_host, uint16_t port, const char *client_ID)
{
	host = domain_host;
	port = port;
	pubcli = mPubSubClient;
	user = "";
	pswd = "";
	cli_ID = client_ID;
	pubcli.setServer(host, port);
	MQTT_cli_Subscribe_Msg_String = "";
}

void Simplemqtt_ReConnect(const char *subTopic)
{
	while(!pubcli.connected()){
		if(strlen(user)>0 && strlen(pswd)>0){
			if(pubcli.connect(cli_ID, user, pswd)){
				if(pubcli.subscribe(subTopic, 1)){
#if DEBUX_MQTT
					DEBUG_X_Return = "Subscribe";
#endif				
				}else{
					// failed
				}
			} else {
#if DEBUX_MQTT
				DEBUG_X_Return = pubcli.state();
#endif
				delay(5000);
			}
		} else {
			if(pubcli.connect(cli_ID)){
				if(pubcli.subscribe(subTopic, 1)){
#if DEBUX_MQTT
					DEBUG_X_Return = "Subscribe";
#endif				
				}else{
					// failed
				}
			} else {
#if DEBUX_MQTT
				DEBUG_X_Return = pubcli.state();
#endif
				delay(5000);
			}
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
	DEBUG_X_Return = "Message Arrived";
#endif
	MQTT_cli_Subscribe_Msg_String = "";
	for (int i = 0; i < length; i++) {
		MQTT_cli_Subscribe_Msg_String += (char)payload[i];
#if DEBUX_MQTT
		DEBUG_X_Return = (char)payload[i];
#endif
	}
}

void initSimplemqtt_callBack()
{
	pubcli.setCallback(Simplemqtt_callback_fn);
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
