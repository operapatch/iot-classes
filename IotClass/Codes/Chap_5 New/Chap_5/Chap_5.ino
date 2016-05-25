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
8:05AM

Chap_4_2_.ino
Chap_5.ino

#include <SoftwareSerial.h>
#define RX1 8
#define TX1 9
SoftwareSerial uart(RX1,TX1);

#define SSID2 "REKA"
#define PASS "workhardstayhumble1"
#define IP "108.61.133.162"
String GET = "GET /patch/miniot1/REKA5002/setangle.php?vol=";
String PHP = " HTTP/1.1\r\nHost: expo.encl.space\r\n\r\n\r\n";

String dataIn,cmd;
char temp;

void setup()
{
  uart.begin(9600);
  Serial.begin(9600);
  while(!Serial)
  {
  }
  
  uart.println("AT+CWMODE=1\r");
  dataIn="";
  while(1)
  {
    if(uart.available()>0)
    {
      temp=uart.read();
      if(temp=='\r')
      {
//        Serial.println(dataIn);
//        dataIn+='\r';
        if(dataIn.indexOf("OK")>0)
        {
          Serial.println(dataIn);
          break;
        }
        else if(dataIn.indexOf("no change")>0)
        {
          Serial.println(dataIn);
          break;
        }
      }
      else
      {
        dataIn+=temp;
      }
    }
  }
  
  uart.print("AT+CWJAP=\"");
  uart.print(SSID2);
  uart.print("\",\"");
  uart.print(PASS);
  uart.println("\"\r");
  dataIn="";
  while(1)
  {
    if(uart.available()>0)
    {
      temp=uart.read();
      if(temp=='\r')
      {
//        Serial.println(dataIn);
//        dataIn+='\r';
        if(dataIn.indexOf("OK")>0)
        {
          Serial.println(dataIn);
          break;
        }
      }
      else
      {
        dataIn+=temp;
      }
    }
  }
}

void loop()
{
  uart.print("AT+CIPSTART=\"TCP\",\"");
  uart.print(IP);
  uart.print("\",80");
  uart.println("\r");
  dataIn="";
  while(1)
  {
    if(uart.available()>0)
    {
      temp=uart.read();
      if(temp=='\r')
      {
//        dataIn+='\r';
        
        if(dataIn.indexOf("Linked")>0)
        {
          Serial.println(dataIn);
          break;
        }
        else if(dataIn.indexOf("ALREADY CONNECT")>0)
        {
          Serial.println(dataIn);
          break;
        }
      }
      else
      {
        dataIn+=temp;
      }
    }
  }
  
  float asdfg=analogRead(0);
  asdfg=asdfg/1024.0;
  asdfg=asdfg*270;
  cmd = "";
  cmd += GET;
//  cmd += 75;  
  cmd += String(asdfg,0);
  cmd += PHP;
//  Serial.println(cmd);
  uart.print("AT+CIPSEND=");
  uart.print(cmd.length());
  uart.println("\r");
//  Serial.println(cmd.length());
//  dataIn="";
  while(1)
  {
    if(uart.available()>0)
    {
      temp=uart.read();
//      Serial.write(temp);
      if(temp=='>')
      {
        Serial.print(">");
        break;
      }
//      else
//      {
//        dataIn+=temp;
//      }
    }
  }
  
  uart.print(cmd);
  dataIn="";
  while(1)
  {
    if(uart.available()>0)
    {
      temp=uart.read();
      if(temp=='\r')
      {
//        Serial.println(dataIn);
//        dataIn+='\r';
        if(dataIn.indexOf("SEND OK")>0)
        {
          Serial.println(dataIn);
//          Serial.println(dataIn);
          break;
        }
      }
      else
      {
        dataIn+=temp;
      }
    }
  }
  
  dataIn="";
  while(1)
  {
    if(uart.available()>0)
    {
      temp=uart.read();
      if(temp=='\n')
      {
        dataIn+='\n';
        if(dataIn.indexOf("OK")>0)
        {
          delay(1500);
          uart.println("AT+CIPCLOSE");
          delay(1000);
          Serial.println(dataIn);
          break;
        }
      }
      else
      {
        dataIn+=temp;
      }
    }
  }
//  uart.flush();
}
