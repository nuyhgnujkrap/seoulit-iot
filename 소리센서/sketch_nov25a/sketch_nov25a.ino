#include <Servo.h>    //서보모터 라이브러리 include


/* 버튼 */
const int buttonPin = 2; 


/* 서보모터 */
Servo microServo;    //서보모터 객체 선언
const int servoPin = 9;    //서보모터 제어핀 할당
int angle = 1; // 서보모터 벨류


/* 사운드 센서 */
const int SOUND_SENSOR = A0; //사운드센서 아날로그0번 핀

//소리 인식 범위
const int threshold1_1 = 680; 
const int threshold1_2 = 750;
const int threshold2_1 = 860;
const int threshold2_2 = 890;

const int clapGap = 300;  // 박수 간격


const int numberOfSamples = 200;
const int numberOfSamples2 = 2000;
int sensorValue = 0;
int statePin = LOW;
int state = 0;
 
void setup(){
  pinMode(SOUND_SENSOR, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.print("1");
  microServo.attach(servoPin);
  microServo.write(140);
  
}

void servoPlay(){
  int i; // 각도
  int early = 140;
  if(angle == 1) {
    angle = 2;
    for (i= 240; i >= 140; i--) {
      microServo.write(i);    //angle(각도)값으로 서보모터 제어
      Serial.println(i);        //각도 값 출력
      delay(1);                    //delay로 각도의 변화 속도를 조절
    }
  } else if(angle == 2) {
    angle = 1;
    for (i = 50; i <= 140; i++) {
      microServo.write(i);    //angle(각도)값으로 서보모터 제어
      Serial.println(i);        //각도 값 출력
      delay(1);                    //delay로 각도의 변화 속도를 조절
    }
  } else {
    Serial.print("fail");
  }
  
  microServo.write(early); // 제자리로 돌려놓음.
}
 
void loop(){

  /**
   *  버튼
   */


   int buttonState;
   buttonState = digitalRead(buttonPin);

   if(buttonState == LOW) {
      servoPlay();
      delay(2000);
   }
  
  /**
   *  사운드 센서
   */

   sensorValue = analogRead(SOUND_SENSOR);
  /*Serial.print("SensorValue");
  Serial.println(sensorValue);*/
  if(threshold1_1 < sensorValue && sensorValue < threshold1_2){
    Serial.print("-First knock!-");
    Serial.println(sensorValue);
    delay(150);
    for(int j=0; j<150; j++){
      sensorValue = analogRead(SOUND_SENSOR);
      if(threshold2_1 < sensorValue && sensorValue < threshold2_2){
        state = state + 1;
      }
      else{
        state = state - 1;
      }
    }
      
      Serial.print("state=");
      Serial.println(state);
      
      if(state < 0){
    for(int i=0; i<numberOfSamples; i++){
      sensorValue = analogRead(SOUND_SENSOR);
      if(threshold2_1 < sensorValue && sensorValue < threshold2_2){
        Serial.print("-Second knock!-");
        Serial.println(sensorValue);
        delay(150);
        
        for(int k = 0; k < numberOfSamples2 ; k++){
          sensorValue = analogRead(SOUND_SENSOR);
          state = 0;
          if(threshold2_1 < sensorValue && sensorValue < threshold2_2){
            state = state + 1;
          }
          else{
            state = state - 1;
          }
          
        }
        if(state < 0){
         Serial.print("state2=");
         Serial.println(state);
        statePin = !statePin;
        i=numberOfSamples;
        Serial.print("Turn on");
        servoPlay();
        }
        else{
          delay(1);
        }
      }
      else{
        delay(1);
      }
    }
      }
      else{
        Serial.print("break");
        Serial.println(sensorValue);
        delay(1);
        
      }
      
  }
  state = 0;


  /**
   * 사운드 센서 끝
   */
} 
