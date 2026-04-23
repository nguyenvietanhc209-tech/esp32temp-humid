#include <WiFi.h>
#include "DHT.h"
#include "ThingSpeak.h"

const char* WIFI_NAME = "BKSTAR"; // Name of the WiFi network
const char* WIFI_PASSWORD = "stemstar"; // Password of the WiFi network
const int myChannelNumber = 3355432; // ThingSpeak channel number
const char* myApiKey = "14D7K39VTT31ANSG"; // ThingSpeak API key
const char* server = "api.thingspeak.com"; // ThingSpeak server address

#define DHTPIN 4     
#define DHTTYPE DHT22  
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client; // Create a WiFi client object

void setup() {
  Serial.begin(115200); // Initialize the serial communication at a baud rate of 115200
  dht.begin();
  WiFi.begin(WIFI_NAME, WIFI_PASSWORD); // Connect to the WiFi network
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Wifi not connected"); // Print a message if WiFi is not connected
  }
  Serial.println("Wifi connected !"); // Print a message if WiFi is connected
  Serial.println("Local IP: " + String(WiFi.localIP())); // Print the local IP address
  WiFi.mode(WIFI_STA); // Set the WiFi mode to station mode
  ThingSpeak.begin(client); // Initialize the ThingSpeak library
}
void loop() {
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.println(F("°C "));
  ThingSpeak.setField(1,t); // Set the value of field 1 in the ThingSpeak channel to the temperature
  ThingSpeak.setField(2,h); // Set the value of field 2 in the ThingSpeak channel to the humidity

  
  int y = ThingSpeak.writeFields(myChannelNumber,myApiKey); // Write the data to the ThingSpeak channel
  
  if(y == 200){
    Serial.println("Data pushed successfully"); // Print a message if the data was successfully pushed to ThingSpeak
  }else{
    Serial.println("Push error" + String(y)); // Print an error message with the HTTP status code if there was an error pushing the data
  }
  Serial.println("---"); // Print a separator line

  delay(10000); // Delay for 10 seconds
}