/*
  Arduino UNO + ES920LR3
  TX LM35 data

*/

#include "LoRa.h"

int sensorPin = A0;

void setup(){
  if (LoRaInit() < 0){
    Serial.println("Serial Error");
    while (1);
  }
}

void loop(){
   int sensorValue = analogRead(sensorPin);
   float temp = (float)(sensorValue) * 5 * 100 / 1024;
   LoRaCommand("MC"+String(temp));
   delay(5000);
}

