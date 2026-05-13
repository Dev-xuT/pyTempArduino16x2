#include <LiquidCrystal.h>

const int pwmCPUpin = 9;
const int pwmCASpin = 10;
const int rs = 13, en = 12, d4 = 8, d5 = 7, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pwmCPUout = 0;
int pwmCASout = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  TCCR1B = (TCCR1B & 0b11111000) | 0x01; // Enable 31 khz PWM output. Only for pins 9 & 10
  analogWrite(pwmCPUpin, 191); // 70% CPU fan speed in boot
  analogWrite(pwmCASpin, 127); // 50% CASe fan speed in boot
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("..Initializing..");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Not Conected!!!");
}

void loop() {
  if (Serial.available() > 0) {
    String tempCPU = Serial.readStringUntil('\n');
    String tempGPU = Serial.readStringUntil('\n');
    String pwmCPU = Serial.readStringUntil('\n');
    String pwmCAS = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(tempCPU);
    lcd.setCursor(0, 1);
    lcd.print(tempGPU);
    sscanf(pwmCPU.c_str(), "pwmCPU = %d", &pwmCPUout);
    sscanf(pwmCAS.c_str(), "pwmCHA = %d", &pwmCASout);
    analogWrite(pwmCPUpin, pwmCPUout);
    analogWrite(pwmCASpin, pwmCASout);
  }
}
