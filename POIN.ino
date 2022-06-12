// MOISTURE
int sensorMoisturePin = A0;
int sensorHumidityPin = A1;
int sensorMoistureValue = 0;
String resultMoistureSensor = String();

// HUMIDITY AND TEMPERATURE SENSOR
#include "DHT.h"
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN 2     // what pin we're connected to（DHT10 and DHT20 don't need define it）
DHT dht(DHTPIN, DHTTYPE);
 
void setup() {
    Serial.begin(9600);
}
void loop() {
    // MOISTURE SENSOR
    
    sensorMoistureValue = analogRead(sensorMoisturePin);
    delay(1000);
    if(0 <= sensorMoistureValue and sensorMoistureValue < 300){
      resultMoistureSensor = "Dry";
    } else if (300 <= sensorMoistureValue and sensorMoistureValue < 600){
      resultMoistureSensor = "Moist";
    } else{
      resultMoistureSensor = "Wet";
    };
    Serial.print("Moisture = " + resultMoistureSensor + " : " + sensorMoistureValue + "\n");
    
    // HUMIDITY AND TEMPERATURE SENSOR
    
    float temp_hum_val[2] = {0};
    if (!dht.readTempAndHumidity(temp_hum_val)) {
      Serial.print("Humidity: ");
      Serial.print(temp_hum_val[0]);
      Serial.print(" %\n");
      Serial.print("Temperature: ");
      Serial.print(temp_hum_val[1]);
      Serial.println(" *C\n");
    } else {
        Serial.println("Failed to get temprature and humidity value.");
    }
}
