#include <Arduino.h>
#include <MQ135.h>

MQ135 gasSensor = MQ135(A0);

int gas_din=2;
int gas_ain=A0;
int ad_value;
uint32 count = 0;
float runningPPMCount = 0;
float runningRZeroCount = 0;

float SMAPPM(float dataPoint) {
  static float DPArray[20] = {400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0,400.0};

  for (int i = 0; i < 19; i++) {
    DPArray[i] = DPArray[i+1];
  }
  DPArray[19] = dataPoint;

  int total = 0;
  for (int i = 0; i < 19; i++) {
    total += DPArray[i];
  }

  return (total / 20.0);
}

uint32 SMAAD(uint32 dataPoint) {
  static float DPArray[10] = {0,0,0,0,0,0,0,0,0,0};

  for (int i = 0; i < 9; i++) {
    DPArray[i] = DPArray[i+1];
  }
  DPArray[9] = dataPoint;

  uint32 total = 0;
  for (int i = 0; i < 10; i++) {
    total += DPArray[i];
  }

  return (total / 10);
}

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
//  Serial.print(":  ");
//  Serial.print("Resistance: ");
//  Serial.print(gasSensor.getResistance());

  Serial.print("    PPM: ");
  float gasPPM = gasSensor.getPPM();
//  Serial.print(gasPPM);
//  Serial.print(" (");
//  Serial.print(PPMAvg(gasPPM));
//  Serial.print(")");
//  Serial.print(" (");
  Serial.print(SMAPPM(gasPPM));
//  Serial.print(")");
/*
  Serial.print("    RZero: ");
  Serial.print(gasSensor.getRZero());
  Serial.print(" (");
  Serial.print(RZeroAvg(gasSensor.getRZero()));
  Serial.print(")");

  Serial.print("    A/D Read: ");
  uint32 adr = analogRead(gas_ain);
  Serial.print(adr);
  Serial.print(" (");
  Serial.print(SMAAD(adr));
  Serial.print(")");
*/
  Serial.println("");

  delay(1000);
}
