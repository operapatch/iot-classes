#include <SoftwareSerial.h>
   
const int RX1 = 8;
const int TX1 = 9;



// create SoftwareSerial objects
SoftwareSerial SoftSerialOne(RX1,TX1);

   void setup()
   {
     pinMode(RX1, INPUT);
     pinMode(TX1, OUTPUT);

     Serial.begin(9600);
     Serial.println("Test Start");
     Serial.setTimeout(5000);
     SoftSerialOne.begin(9600);
    
   }
   
   void loop()
   {
     
     while(Serial.available())
     {
       
       SoftSerialOne.write(Serial.read());
     }
     while(SoftSerialOne.available())
     {
       Serial.write(SoftSerialOne.read());
       Serial.setTimeout(5000);
     }
     
    
   }
