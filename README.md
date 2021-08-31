# SMqtt

Just another ESP32 Mqtt client.
Features: AsyncMqttClient wrapper. (so install https://github.com/marvinroger/async-mqtt-client/ too, to use this)


## Usage:

```cpp
...
#include <smqtt.h>
...


void onMqttConnect()
{
    SMqtt::Subscribe("/home/example/set");
    SMqtt::SetWill("/home/example/status", "Dead", false, 0);
    SMqtt::SendMessage("/home/example/status", "Alive", false, 0);

}

void onMqttMessage(char* topic, char* payload)
{
  //do something with it
}


void setup() {
  //....
  //connect to Wifi, do stuff
  //....
  
  SMqtt::SetParams("192.168.1.100", 1883, "user", "pass"); //change it to your mqtt broker settings
  SMqtt::Setup();
  SMqtt::SetOnConnectCallBack(onMqttConnect);
  SMqtt::SetOnMessageCallBack(onMqttMessage);

}


void loop() {
  //...
  //do stuff
  //...
  
  SMqtt::Loop(WiFi.status() == WL_CONNECTED);  //or simply put true there
  
  //...
}
``` 