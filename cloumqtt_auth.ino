# This only connects to the Cloudmqtt broker
# Upload this to Arduino IDE and connect to the broker 
# Go to WebSockets UI and watch the incoming stream of data
#
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

char server[] = "m12.cloudmqtt.com";

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, 19757, callback, ethClient);

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  
  if (client.connect("arduinoClient", "oxefqvkn", "aKpQPSFiTpXp")) {
    Serial.println ("Connected successfully");
    client.publish("outTopic","hello worldGowriDay");
    client.subscribe("inTopic");
  }
}

void loop()
{
    client.publish("outTopic","hello worldGowriDay");
    Serial.println ("Published to Outtopic");
    
    delay ( 1000);
  client.loop();
}