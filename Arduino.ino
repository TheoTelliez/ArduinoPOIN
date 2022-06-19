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

// AIR QUALITY SENSOR
#include "Air_Quality_Sensor.h"
AirQualitySensor airsensor(A0);

// BAROMETER
#include <HP20x_dev.h>
#include "Wire.h"
unsigned char ret = 0;

// SUNLIGHT SENSOR
#include "SI114X.h"
SI114X SI1145 = SI114X();
 
void setup() {
    Serial.begin(9600);
    delay(150);
    
    // AIR QUALITY SENSOR
    Serial.println("Waiting sensor to init...");
    delay(20000);

    if (airsensor.init()) {
        Serial.println("Sensor ready.");
    } else {
        Serial.println("Sensor ERROR!");
    }

    // BAROMETER
    HP20x.begin();
    delay(200);

    // SUNLIGHT SENSOR
    while (!SI1145.Begin()) {
      Serial.println("Si1145 is not ready!");
      delay(1000);
    }
    Serial.println("Si1145 is ready!");
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
    Serial.print("Moisture: " + resultMoistureSensor + " : " + sensorMoistureValue + " \n");
    delay(20000);

    
    // HUMIDITY AND TEMPERATURE SENSOR
    float temp_hum_val[2] = {0};
    if (!dht.readTempAndHumidity(temp_hum_val)) {
      Serial.print("Humidity: ");
      Serial.print(temp_hum_val[0]);
      Serial.print(" % \n");
      delay(20000);
      Serial.print("Temperature: ");
      Serial.print(temp_hum_val[1]);
      Serial.print(" *C\n");
      delay(20000);
    } else {
        Serial.println("Failed to get temprature and humidity value.");
    }


    // AIR QUALITY SENSOR
    int quality = airsensor.slope();
    Serial.print("AirQuality: ");
    Serial.print(airsensor.getValue());
    Serial.print(" \n");
    delay(20000);


    // BAROMETER
    long Pressure = HP20x.ReadPressure();
    Serial.print("Pressure: ");
    float pres = Pressure / 100.0;
    Serial.print(pres);
    Serial.print(" hPa \n");
    delay(20000);


    // SUNLIGHT SENSOR
    Serial.print("Vis: "); Serial.print(SI1145.ReadVisible()); Serial.print(" \n");
    delay(20000);
    Serial.print("IR: "); Serial.print(SI1145.ReadIR());  Serial.print(" \n");
    delay(20000);
    Serial.print("UV: ");  Serial.print((float)SI1145.ReadUV()/100);  Serial.print(" \n");
    delay(20000);


    // FINAL WAIT 5MIN
    delay(300000);
}
