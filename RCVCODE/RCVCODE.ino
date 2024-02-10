/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
 #include <LiquidCrystal.h>
 
RF24 radio(7, 3); // CE, CSN
 
  LiquidCrystal lcd(8, 9, 6, 5, 4, 3);

const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MAX);
   lcd.println("Waiting");
  radio.startListening();
  
}
void loop() {
 
  while (radio.available()) {
    delay(500);
    lcd.clear();
    
    char rcvmsg[8] = "";
    radio.read(&rcvmsg, sizeof(rcvmsg));
    
    Serial.println(rcvmsg);
    lcd.println("Data Available");
    lcd.setCursor(0,1);
    lcd.println(rcvmsg);
    delay(1000);
    lcd.clear();
    lcd.println("Sending..");
    radio.stopListening();
    radio.openWritingPipe(address);
   // const char sndmsg[8] = "QuadmsgS";
   rcvmsg[7]=rcvmsg[7] +1;
    radio.write(&rcvmsg, sizeof(rcvmsg));
    radio.begin();
      radio.openReadingPipe(0, address);
    radio.startListening();
  
    
  }
  
}
