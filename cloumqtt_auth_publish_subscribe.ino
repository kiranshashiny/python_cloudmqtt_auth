/* This lets you publish and subscribe to Cloudmqtt.com
 Run this on Arduino at one end, and python-cloudmqtt On/Off on
 your laptop to receive the messages ( or subscribe )
*/
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

char server[] = "m12.cloudmqtt.com";

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
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
    client.subscribe("/frommothership");
  }
}

void loop()
{
    // Uncomment only if you want to publish over and over 
    //client.publish("outTopic","hello worldGowriDay");
    //Serial.println ("Published to Outtopic");
    // delay ( 1000);
  // stay in loop listening to any commands being published from applications
  // or from the laptop.
  client.loop();
}
