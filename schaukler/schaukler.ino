#include <Encoder.h>
#include <Servo.h>

Servo motor1;
Encoder rotaryEncoder(2,3);
#define switch 7

#define baseDelay 3000
#define min_angle 0
#define max_angle 90


int counterMultiplyer = 20;
int counter = 0;
boolean active = true;



boolean motor_left = true;
unsigned long last_millis = millis();


void setup() {
  motor1.attach(5);
  pinMode(switch, INPUT_PULLUP);
  Serial.begin(9600);

}



void loop() {

  int tempEncoder = rotaryEncoder.read();
  if (tempEncoder != counter){
    counter = tempEncoder;
    Serial.println(counter);
  }
  
  //delay(baseDelay + counter * counterMultiplyer);
  if (millis() > last_millis+baseDelay + counter * counterMultiplyer){
    if (active){
      flip();
    }
    last_millis = millis();
  }
  //Serial.println(digitalRead(switch));
  if(digitalRead(switch)==LOW){
    active = !active;
    Serial.println(active);
    delay(500);
  }
  
}

void flip(){
  Serial.println("flipping");
    if (motor_left){
    motor1.write(max_angle);
    motor_left = false;
  }else{
    motor1.write(min_angle);
    motor_left = true;  
  }
  

}
