# This is the client side of things.
# to see this in action - start the app on the 
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };

char server[] = "m12.cloudmqtt.com";

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
  char command[10]; // to store on and off.
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    command[i] = (char)payload[i];
  }
  command[length]  ='\0';
  Serial.println();

  if ( strncmp(command, "on", 2) == 0 ) {
     Serial.println ("Your wish was to ON, setting pin 9 to high");
      digitalWrite(9, HIGH); 
  }else if ( strncmp ( command, "off", 3) == 0 ) {
     Serial.println ("Your wish was to OFF, setting pin 9 to low");
      digitalWrite(9, LOW); 
  }
  //Serial.println (command );
}

EthernetClient ethClient;
PubSubClient client(server, 19757, callback, ethClient);

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac);
  pinMode(9, OUTPUT);
  
  if (client.connect("arduinoClient", "oxefqvkn", "aKpQPSFiTpXp")) {
    Serial.println ("Connected successfully");
    Serial.println ("If you want to see any message published from apps, start the apps on remote side");
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
