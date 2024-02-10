#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>


 
RF24 radio(7, 3); // CE, CSN
LiquidCrystal lcd(8, 9, 6, 5, 4, 3);



const byte address[6] = "00001";
 

 
void setup() {
 
Serial.begin(115200);
 
Serial.print("Init");

 
 radio.begin();
 lcd.begin(16,2);
 
// Set the PA Level low to prevent power supply related issues since this is a
 
// getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
 radio.enableAckPayload();
 radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

 
}
char inputdata[5]={'F','W','D','H','2'};
char rcv[2];
void loop() {
 
 
 /* if(Serial.available())*/{                
   //inputdata=Serial.read();
  
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print(inputdata);
   if (!radio.write( &inputdata, 5 )){
 
     Serial.println("Error writing pipe");
     lcd.setCursor(0,1);
     lcd.print("transmission error!");
   } 
 
  delay(1000);
  }
  if(radio.isAckPayloadAvailable()){
    radio.read(rcv,2);
    Serial.println( rcv);
    radio.printDetails();
   // Serial.println( );
    }
 
}
 
