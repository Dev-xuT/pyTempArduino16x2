#include <LiquidCrystal.h>

const int pwmCPUpin = 9;
const int pwmCHApin = 10;
const int rs = 13, en = 12, d4 = 8, d5 = 7, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pwmCPUout = 0;
int pwmCHAout = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  TCCR1B = (TCCR1B & 0b11111000) | 0x01; // Enable 31 khz PWM output 
  analogWrite(pwmCPUpin, 200);  // Set minimal speed for system boot
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("..Initializing..");
  lcd.setCursor(0, 1);
  delay(1000);
  lcd.print("Not Conected!!!");
}

void loop() {
  if (Serial.available() > 0) {
    String temp = Serial.readStringUntil('\n');
    String usage = Serial.readStringUntil('\n');
    String pwmCPU = Serial.readStringUntil('\n');
    String pwmCHA = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(temp);
    lcd.setCursor(0, 1);
    lcd.print(usage);
    sscanf(pwmCPU.c_str(), "pwmCPU = %d", &pwmCPUout);
    sscanf(pwmCHA.c_str(), "pwmCHA = %d", &pwmCHAout);
    analogWrite(pwmCPUpin, pwmCPUout);
    analogWrite(pwmCHApin, pwmCHAout);
  }    
}
