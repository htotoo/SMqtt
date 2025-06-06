#ifndef __SMQTT_H
#define __SMQTT_H

#include <espMqttClientAsync.h>

class SMqtt
{
  public:
    static void SetParams(char host[], int port, char user[], char pass[]) {
      mHost = host;
      mPort = port;
      mUser = user;
      mPass = pass;
      mqttClient.setServer(mHost, mPort);
      mqttClient.setCredentials(mUser, mPass);
      mqttClient.setKeepAlive(45);
    }
    static void Loop(bool iswifiOk);
    static void Setup();
    static bool IsConnected();
    static bool SendMessage(const char* topic, const char* msg, bool retention = false, uint8_t qos = 0);
    static void SetWill(const char* topic, const char* msg, bool retention = false, uint8_t qos = 0);
    static void Subscribe(const char* topic, uint8_t qos = 0);
    static void Unsubscribe(const char* topic);
    static void SetOnConnectCallBack(void(*fp)()) {
      onConnectCB = fp;
    }
    static void SetOnMessageCallBack(void(*fp)(char* topic, char* payload, size_t len)) {
      onMessageCB = fp;
    }

  protected:
    static char* mHost;
    static int mPort;
    static char* mUser;
    static char* mPass;
    static bool isConnected;
    static espMqttClientAsync mqttClient;
    static void intOnMqttConnect(bool sessionPresent);
    static void intOnMqttDisconnect(espMqttClientTypes::DisconnectReason reason);
    static void intOnMqttSubscribe(uint16_t packetId, const espMqttClientTypes::SubscribeReturncode* codes, size_t len);
    static void intOnMqttUnsubscribe(uint16_t packetId);
    
    static void intOnMqttMessage(const espMqttClientTypes::MessageProperties& properties, const char* topic, const uint8_t* payload, size_t len, size_t index, size_t total);
    static void intOnMqttPublish(uint16_t packetId);
    static unsigned long lastCheck;
    static void(*onConnectCB)();
    static void(*onMessageCB)(char* topic, char* payload, size_t len);
};



#endif
