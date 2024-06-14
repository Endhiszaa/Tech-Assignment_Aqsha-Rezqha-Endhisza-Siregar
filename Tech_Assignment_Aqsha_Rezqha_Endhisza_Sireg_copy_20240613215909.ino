#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>

// Define the DHT sensor pin and type
#define DHTPIN 13
#define DHTTYPE DHT11

// WiFi credentials
const char* ssid = "KBM_Access";
const char* password = "erfinisna";

// Server endpoint for data submission
const char* serverName = "http://192.168.1.101:5000/data";

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  Serial.begin(9600);
  
  dht.begin();
  
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(2500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

void loop() {
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

   
    String postData = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + "}";

    
    int httpResponseCode = http.POST(postData);

    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

  
    http.end();
  } else {
  
    Serial.println("WiFi Disconnected");
  }

 
  delay(5000);
}
