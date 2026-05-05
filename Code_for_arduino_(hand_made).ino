#include <LiquidCrystal.h>

const int pwmpin = 10;
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int pwmout = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  //Start fans in full speed in case of erros
  analogWrite(pwmpin, 255);
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
