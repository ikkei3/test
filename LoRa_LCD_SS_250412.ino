/*
  Arduino UNO + ES920LR3
  RX data LCD display

*/

#include <LiquidCrystal.h>
#include "LoRa.h"

const int rs = 4, en = 6, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("LoRa Display");
  lcd.setCursor(0, 1);
  lcd.print("Stand-by");
  if (LoRaInit() < 0){
    Serial.println("Serial Error");
    while (1);
  }
}

void loop(){
  String rxs = rxdata();
  if (rxs.length() > 0){
    Serial.print(rxs);
    char Buf[5];
    rxs.toCharArray(Buf, 5);
    int16_t rssi = strtol(Buf,NULL,16);
    rxs = rxs.substring(4);
    lcd.clear();
    delay(300);
    lcd.setCursor(0, 0);
    if (rxs.length() > 12){
      lcd.print(rxs.substring( 2, 6 ) + " C " );
      lcd.setCursor(0, 1);
      lcd.print(rxs.substring( 8,12 ) + " % "  );
      if (rxs.length() > 16){
        lcd.setCursor(7, 0);
        lcd.print(rxs.substring(14,18 ) + " hPa ");
      }
    } else {
      lcd.print(rxs);
    }
    lcd.setCursor(7, 1);
    lcd.print(rssi);
    lcd.print(" dBm ");
  }
}
