
#include "smqtt.h"

char* SMqtt::mHost;
int SMqtt::mPort;
char* SMqtt::mUser;
char* SMqtt::mPass;
bool SMqtt::isConnected = false;
AsyncMqttClient SMqtt::mqttClient;
unsigned long SMqtt::lastCheck = 0;
void(*SMqtt::onConnectCB)() = NULL;
void(*SMqtt::onMessageCB)(char* topic, char* payload, size_t len ) = NULL;

void SMqtt::Setup()
{
  mqttClient.onConnect(SMqtt::intOnMqttConnect);
  mqttClient.onDisconnect(SMqtt::intOnMqttDisconnect);
  mqttClient.onSubscribe(SMqtt::intOnMqttSubscribe);
  mqttClient.onUnsubscribe(SMqtt::intOnMqttUnsubscribe);
  mqttClient.onMessage(SMqtt::intOnMqttMessage);
  mqttClient.onPublish(SMqtt::intOnMqttPublish);
}

void SMqtt::Loop(bool iswifiOk) {
  if (millis() - SMqtt::lastCheck < 1000) return;
  SMqtt::lastCheck = millis();
  if (iswifiOk && !mqttClient.connected()) {
    mqttClient.connect();
  }
}

bool SMqtt::IsConnected() {
  return SMqtt::isConnected;
}

bool SMqtt::SendMessage(const char* topic, const char* msg, bool retention, uint8_t qos ) {
  return (SMqtt::mqttClient.publish(topic, qos, retention, msg) > 0);
}

void SMqtt::SetWill(const char* topic, const char* msg, bool retention, uint8_t qos ) {
  SMqtt::mqttClient.setWill(topic, qos, retention, msg);
}

void SMqtt::Subscribe(const char* topic, uint8_t qos)
{
    SMqtt::mqttClient.subscribe(topic, qos);    
}

void SMqtt::Unsubscribe(const char* topic)
{
    SMqtt::mqttClient.unsubscribe(topic);    
}

void SMqtt::intOnMqttConnect(bool sessionPresent) {
  SMqtt::isConnected = true;
  if (SMqtt::onConnectCB != NULL) SMqtt::onConnectCB();
}

void SMqtt::intOnMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  SMqtt::isConnected = false;
}

void SMqtt::intOnMqttSubscribe(uint16_t packetId, uint8_t qos) {};
void SMqtt::intOnMqttUnsubscribe(uint16_t packetId) {};
void SMqtt::intOnMqttPublish(uint16_t packetId) {};
void SMqtt::intOnMqttMessage(char* topic, char* payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
    if (SMqtt::onMessageCB != NULL) SMqtt::onMessageCB(topic, payload, len);
}
