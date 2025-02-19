#include <Servo.h>

//Digital Input Pin
int PWM_ROLL = 13;
int PWM_PITCH = 12;
int PWM_THROTTLE = 11;
int PWM_YAW = 10;
int PWM_SWA = 9;
int PWM_VRA = 8;
//Digital Output Pin
int OUT_THROTTLE = 3;
int OUT_SWA = 7;
int OUT_VRA = 6;
Servo rollServo;
Servo pitchServo;
Servo yawServo;

void setup() {
  pinMode(PWM_ROLL, INPUT);
  pinMode(PWM_PITCH, INPUT);
  pinMode(PWM_THROTTLE, INPUT);
  pinMode(PWM_YAW, INPUT);
  pinMode(PWM_SWA, INPUT);
  pinMode(PWM_VRA, INPUT);
  
  pinMode(OUT_THROTTLE, OUTPUT);
  pinMode(OUT_SWA, OUTPUT);
  pinMode(OUT_VRA, OUTPUT);
  
  rollServo.attach(5);
  pitchServo.attach(4);
  yawServo.attach(2);
  
  Serial.begin(115200);
}

void loop() {
  int roll = pulseIn(PWM_ROLL, HIGH);
  int pitch = pulseIn(PWM_PITCH, HIGH);
  int throttle = pulseIn(PWM_THROTTLE, HIGH);
  int yaw = pulseIn(PWM_YAW, HIGH);
  int swA = pulseIn(PWM_SWA, HIGH);
  int vrA = pulseIn(PWM_VRA, HIGH);
  
  // Map input PWM signals to servo range (1000-2000 us to 0-180 degrees)
  int rollOut = map(roll, 1000, 2000, 0, 180);
  int pitchOut = map(pitch, 1000, 2000, 0, 180);
  int yawOut = map(yaw, 1000, 2000, 0, 180);
  
  rollServo.write(rollOut);
  pitchServo.write(pitchOut);
  yawServo.write(yawOut);
  
  // Map input PWM signals to PWM output range (0-255)
  int throttleOut = map(throttle, 1000, 2000, 0, 255);
  int swAOut = map(swA, 1000, 2000, 0, 255);
  int vrAOut = map(vrA, 1000, 2000, 0, 255);
  
  throttleOut = constrain(throttleOut, 0, 255);
  swAOut = constrain(swAOut, 0, 255);
  vrAOut = constrain(vrAOut, 0, 255);
  
  analogWrite(OUT_THROTTLE, throttleOut);
  analogWrite(OUT_SWA, swAOut);
  analogWrite(OUT_VRA, vrAOut);
  
  Serial.print(" PWM CH1 Roll: ");
  Serial.print(roll-1500);
  Serial.print(" PWM CH2 Pitch: ");
  Serial.print(pitch-1500);
  Serial.print(" PWM CH3 Throttle: ");
  Serial.println(throttle-1014);
  Serial.print(" PWM CH4 Yaw: ");
  Serial.print(yaw-1495);
  Serial.print(" PWM CH5 swA: ");
  Serial.print(swA-995);
  Serial.print(" PWM CH6 vrA: ");
  Serial.println(vrA-995);
}