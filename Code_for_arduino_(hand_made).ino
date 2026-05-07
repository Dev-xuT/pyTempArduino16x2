#include <LiquidCrystal.h>

const int pwmpin = 9;
const int rs = 13, en = 12, d4 = 8, d5 = 7, d6 = 4, d7 = 2; // LCD conection exclude the PWM capable pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pwmout = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  TCCR1B = (TCCR1B & 0b11111000) | 0x01; // Enable 31 khz PWM output 
  analogWrite(pwmpin, 0);
}

void loop() {
  if (Serial.available() > 0) {
    String temp = Serial.readStringUntil('\n');
    String usage = Serial.readStringUntil('\n');
    String pwm = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(temp);
    lcd.setCursor(0, 1);
    lcd.print(usage);
    sscanf(pwm.c_str(), "pwm = %d", &pwmout);
    analogWrite (pwmpin, pwmout);
  }    
}
