int sensorPin = A0;
int sensorMoistureValue = 0;
String resultMoistureSensor = String();
 
void setup() {
    Serial.begin(9600);
}
void loop() {
    // read the value from the sensor:
    sensorMoistureValue = analogRead(sensorPin);
    delay(1000);
    if(0 <= sensorMoistureValue and sensorMoistureValue < 300){
      resultMoistureSensor = "Dry";
    } else if (300 <= sensorMoistureValue and sensorMoistureValue < 600){
      resultMoistureSensor = "Moist";
    } else{
      resultMoistureSensor = "Wet";
    };
    Serial.print("Moisture = " + resultMoistureSensor + " : " + sensorMoistureValue + "\n");
            
}
