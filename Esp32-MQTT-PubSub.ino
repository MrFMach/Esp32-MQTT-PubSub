
#include <WiFi.h>
#include <PubSubClient.h>

// GPIOs acccording your wiring
#define YEL 12
#define RED 13
#define GRE 14

// Wi-Fi ssid and password
const char* ssid = "your ssid";
const char* password = "your password";

// Your Raspberry Pi IP, in this format
IPAddress server(000, 000, 000, 000); 

// Callback function, listen to the incoming message
void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Incoming message - ASCII decimal: ");
  Serial.println(*payload);

  // message handling
  switch (*payload) {
    case 114:                     // the letter "r" ASCII
      digitalWrite(RED, HIGH);
      digitalWrite(YEL, LOW);
      digitalWrite(GRE, LOW);
      break;
    case 121:                     // the letter "y" ASCII
      digitalWrite(RED, LOW);
      digitalWrite(YEL, HIGH);
      digitalWrite(GRE, LOW);
      break;
    case 103:                     // the letter "g" ASCII
      digitalWrite(RED, LOW);
      digitalWrite(YEL, LOW);
      digitalWrite(GRE, HIGH);
      break;
    default:
      digitalWrite(RED, LOW);
      digitalWrite(YEL, LOW);
      digitalWrite(GRE, LOW);
      break;
  }
}

WiFiClient esp32Client;
PubSubClient client(server, 1883, callback, esp32Client);

void startWifi() {
  Serial.print("\nEsp32 connect with ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Starting wifi connect...");
    WiFi.begin(ssid, password);
    delay(2000);
  }
  Serial.println("Wifi connected!");
  Serial.print("Esp32 IP address: ");
  Serial.println(WiFi.localIP());
}

void connectBroker() {
  // User and password configured in the broker
  if (client.connect("espClient", "mqtt_user", "mqtt_password")) {
    client.publish("outTopic", "Ready to publish in <outTopic>"); //Esp32 publish in outTopic
    client.subscribe("inTopic"); //Esp32 subscribe inTopic. See callback function
    Serial.println("Broker connected!");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(RED, OUTPUT);
  pinMode(YEL, OUTPUT);
  pinMode(GRE, OUTPUT);

  startWifi();
  connectBroker();
}

void loop()
{
  client.loop();
}
