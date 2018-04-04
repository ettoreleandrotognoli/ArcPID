#include <PID.h>

const int LED = A1;
const int POT = A2;
const int LDR = A3;

arc::PID<double> ledPid(5.0,0.5,0.2);


void setup() {
  Serial.begin(115200);
  pinMode(LED,OUTPUT);
  pinMode(POT,INPUT);
  pinMode(LDR,INPUT);
}

unsigned char ledValue = 0;

void loop() {
  delay(100);
  unsigned short ldrRaw = analogRead(LDR);
  unsigned short potRaw = analogRead(POT);
  ledPid.setTarget(potRaw);
  ledPid.setInput(ldrRaw);
  ledValue = min(255,max(0,ledValue + ledPid.getOutput()));
  Serial.print("{\"ldr\":");
  Serial.print(ldrRaw,DEC);
  Serial.print(",\"pot\":");
  Serial.print(potRaw,DEC); 
  Serial.print(",\"led\":");
  Serial.print(ledValue,DEC); 
  Serial.println("}");
  analogWrite(LED,ledValue);
}
