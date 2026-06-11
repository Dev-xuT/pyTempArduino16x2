#include <LiquidCrystal.h>

const int pwmCPUpin = 9;
const int pwmCASpin = 10;
int pwmCPUout = 0;
int pwmCASout = 0;

void setup() {
  Serial.begin(9600);
  TCCR1B = (TCCR1B & 0b11111000) | 0x01; // Enable 31 khz PWM output. Only for pins 9 & 10
  analogWrite(pwmCPUpin, 172); // 50% CPU fan speed in boot
  analogWrite(pwmCASpin, 90); // 20% CASe fan speed in boot
  delay(1000);
}

void loop() {
  if (Serial.available() > 0) {
    String pwmCPU = Serial.readStringUntil('\n');
    String pwmCAS = Serial.readStringUntil('\n');
    sscanf(pwmCPU.c_str(), "pwmCPU = %d", &pwmCPUout);
    sscanf(pwmCAS.c_str(), "pwmCAS = %d", &pwmCASout);
    analogWrite(pwmCPUpin, pwmCPUout);
    analogWrite(pwmCASpin, pwmCASout);
  }
}
