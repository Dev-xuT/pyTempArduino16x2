const int pwmCPUpin = 9;
const int pwmCASpin = 10;

int pwmCPUout = 0;
int pwmCASout = 0;
int tempsts = 0;
int CASrest = 133;
int CPUrest = 105;

void setup() {
  Serial.begin(9600);
  TCCR1B = (TCCR1B & 0b11111000) | 0x01; // Enable 31 khz PWM output. Only for pins 9 & 10
  analogWrite(pwmCPUpin, 162); // 50% CPU fan speed in boot
  analogWrite(pwmCASpin, 0); // 20% CASe fan speed in boot
}

void loop() {
  if (Serial.available() > 0) {
    String pwmCPU = Serial.readStringUntil('\n');
    String pwmCAS = Serial.readStringUntil('\n');
    sscanf(pwmCPU.c_str(), "pwmCPU = %d", &pwmCPUout);
    sscanf(pwmCAS.c_str(), "pwmCAS = %d", &pwmCASout);
    if (pwmCPUout >= 105) {
      analogWrite(pwmCPUpin, pwmCPUout);
    } else {
      analogWrite(pwmCPUpin, CPUrest);
    }
    if (pwmCASout >= 133) {
      analogWrite(pwmCASpin, pwmCASout);
      tempsts = 1;
    } else if (pwmCASout <= 51) {
      analogWrite(pwmCASpin, 0);
      tempsts = 0;
    } else if (pwmCASout >= 52 <= 132 && tempsts == 1) {
      analogWrite(pwmCASpin, CASrest);
    }
  }
}
