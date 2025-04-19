//
//  920MHz LoRa/FSK RF module ES920LR3 
//
//  MaiaR create
//

#ifndef LoRa_h
#define LoRa_h

#include "Arduino.h"

String rxdata();
int LoRaInit();
int LoRaCommand(String s);

#endif
