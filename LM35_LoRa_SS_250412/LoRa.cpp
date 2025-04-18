//
//  920MHz LoRa/FSK RF module ES920LR3 
//  via Software Serial
//
//  MaiaR create
//

#include "LoRa.h"

int resetPin = 9; // PB1

#include <SoftwareSerial.h>
SoftwareSerial SwSerial(2, 3); // RX, TX


void LoRaReset(){
  pinMode(resetPin, OUTPUT); // NRST "L"
  digitalWrite(resetPin, LOW);
  delay(10);
  pinMode(resetPin, INPUT);  // NRST open
}


void LoRaConfigMode(){
  Serial.begin(115200);
  SwSerial.begin(115200);
  SwSerial.setTimeout(20);
  while(1){
    LoRaReset();
    String rx = SwSerial.readString();
    Serial.println(rx);
    if (rx.indexOf("Select Mode") >= 0) break;
    LoRaCommand("config");
  }
}

int LoRaCommand(String s){
  SwSerial.print(s + "\r\n");
  SwSerial.flush();
  Serial.println(s);
  String rx = SwSerial.readStringUntil('\n');
  Serial.println(rx);
  return (rx.indexOf("OK"));
}

int LoRaInit(){
  LoRaConfigMode();
  SwSerial.print("2\r\n");   // processor mode
  delay(1);
  SwSerial.print("r 4\r\n"); // baudrate 57600
  delay(2);
  SwSerial.begin(57600);
  if (LoRaCommand("b 4"   ) < 0) return(-1); // band width
  if (LoRaCommand("c 12"  ) < 0) return(-1); // spread factor
  if (LoRaCommand("d 3"   ) < 0) return(-1); // channel
  if (LoRaCommand("e 2345") < 0) return(-1); // PAN ID
  if (LoRaCommand("f 0"   ) < 0) return(-1); // own ID
  if (LoRaCommand("g ffff") < 0) return(-1); // broadcast
  if (LoRaCommand("p 1"   ) < 0) return(-1); // RSSI on
  if (LoRaCommand("z"     ) < 0) return(-1); // start
  return(0);
}