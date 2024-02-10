/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

  
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}
uint8_t strtflg=1;
void loop() {
  if(strtflg){
   char sndmsg[] = "QuadMsg1";
  radio.write(&sndmsg, sizeof(sndmsg));
  strtflg=0;
   radio.startListening();
  delay(100);
 
  }
  while(radio.available())
  {
     delay(500);
    char rcvmsg[8] = "";
    radio.read(&rcvmsg, sizeof(rcvmsg));
     delay(100);
    radio.stopListening();
    rcvmsg[7]=rcvmsg[7] +1;
    radio.openWritingPipe(address);
    radio.write(&rcvmsg, sizeof(rcvmsg));
     delay(100);
     radio.begin();
      radio.openReadingPipe(0, address);
     radio.startListening();
    
    }
}
