#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"


FPS_GT511C3 fps(3,2);
int solenoidPin = 5;
void setup() {
  Serial.begin(9600);
  delay(100);
  fps.Open();
  fps.SetLED(true);
  pinMode(solenoidPin, OUTPUT);

}
void loop() {
  if (fps.IsPressFinger()) {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id <200) {
      Serial.print("Verified ID:");
      Serial.println(id);
      if (id == 1) {
      digitalWrite(solenoidPin, HIGH);
      Serial.print(id);
      Serial.println("th Finger");
      fps.SetLED(false);
      delay(5000);
      fps.SetLED(true);
      digitalWrite(solenoidPin, LOW);
      } else if (id == 2) {
      Serial.print(id);
      Serial.println("th Finger");                  
      } else if (id == 1){
      Serial.print(id);
      Serial.println("th Finger");
      }
    }else{
        Serial.println("Finger Not Found");
        fps.SetLED(false);
        delay(300);
        fps.SetLED(true);
        delay(100);
      }
  }
  delay(100);
}
