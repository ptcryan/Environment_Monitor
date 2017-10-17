#include <Arduino.h>
#include <MQ135.h>

MQ135 gasSensor = MQ135(A0);

int gas_din=2;
int gas_ain=A0;
int ad_value;
uint32 count = 0;
float runningPPMCount = 0;
float runningRZeroCount = 0;

float PPMAvg(float PPMAverage) {
  runningPPMCount += PPMAverage;
  return (runningPPMCount / count);
}

float RZeroAvg(float RZeroAverage) {
  runningRZeroCount += RZeroAverage;
  return (runningRZeroCount / count);
}

void setup() {
  pinMode(gas_din,INPUT);
  pinMode(gas_ain,INPUT);
  Serial.begin(9600);
}

void loop() {
  count++;
  Serial.print(count);
  Serial.print(":  ");
  Serial.print("Resistance: ");
  Serial.print(gasSensor.getResistance());
  Serial.print("    PPM: ");
  Serial.print(gasSensor.getPPM());
  Serial.print(" (");
  Serial.print(PPMAvg(gasSensor.getPPM()));
  Serial.print(")");
  Serial.print("    RZero: ");
  Serial.print(gasSensor.getRZero());
  Serial.print(" (");
  Serial.print(RZeroAvg(gasSensor.getRZero()));
  Serial.print(")");
  Serial.print("    A/D Read: ");
  Serial.println(analogRead(gas_ain));

  delay(2000);
}
