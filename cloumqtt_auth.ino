/* This Arduino sketch connects to the Cloudmqtt broker
 Upload this to Arduino IDE and connect to the broker 
 Go to WebSockets UI and watch the incoming stream of data
 If this did not work - check the port, restart the service on the cloudmqtt.com,
 Open serial port and check or look for debug messages.
*/
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
    client.publish("outTopic","hello world - first message from Arduino Sketch to CloudMQTT");
    client.subscribe("inTopic");
  }
}

void loop()
{
    client.publish("outTopic","hello from Arduino Sketch..");
    Serial.println ("Published to Outtopic, Open serial port ");
    
    delay ( 1000);
    client.loop();
}
