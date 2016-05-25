// piezo speaker connected to pin 8 and ground
//#define wait 1
//#define time 10
//int freq = 0;
#define offbuzz 2
#define onbuzz 3
#define lamp 6
#define indicator 7
#define buzz 8
#define offlamp 4
#define onlamp 5
#define trig 9
#define echo 10

void setup()
{
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
  pinMode(offbuzz,INPUT);
  pinMode(onbuzz,INPUT);
  pinMode(offlamp,INPUT);
  pinMode(onlamp,INPUT);
  pinMode(indicator,OUTPUT);
  pinMode(lamp,OUTPUT);
}
const float pi = 3.14;

unsigned long time_L;
int freq=150;
boolean buzzer,dir;

unsigned long time_S,update,time_SG;
byte step_s;
float range;

void loop()
{
  if(millis()>time_L+1)
  {
    time_L=millis();
    
    if(buzzer)
    {
      int duty=(1.0+sin(2*pi*time_L/1000.0))*127.5;
      analogWrite(indicator,duty);
      if(dir)
      {
        tone(buzz,freq);
        freq++;
      }
      else
      {
        tone(buzz,freq);
        freq--;
      }
      if(freq<150 || freq>1800)
      {
        dir^=1;
      }
    }
    else
    {
      noTone(buzz);
      freq=150;
      analogWrite(indicator,0);
    }
  }
  
  if(digitalRead(offbuzz))
  {
    buzzer=false;
  }
  
  if(digitalRead(onbuzz))
  {
    buzzer=true;    
  }
  
  if(digitalRead(offlamp))
  {
    digitalWrite(lamp,LOW);
  }
  
  if(digitalRead(onlamp))
  {
    digitalWrite(lamp,HIGH);
  }
  
  
  if(step_s == 0)
  {
//    guard_s=millis();
    digitalWrite(trig,LOW);
    if(!digitalRead(echo))
    {
      step_s=1;
    }
  }   
  if(step_s == 1)//send trig signal
  {
    digitalWrite(trig,HIGH);
    step_s=2;
    time_S=micros();
  }
  if(step_s == 2)//turn off trig signal after 10us
  {
    if(time_S+10<micros())
    {
      digitalWrite(trig,LOW);
      step_s=3;
      time_SG=micros();
    }
  }
  if(step_s == 3)//time counter start
  {
    if(micros()>time_SG+100)
    {
      step_s=0;
    }
    if(digitalRead(echo))
    {
      time_S=micros();
      step_s=4;
    }
  }
  if(step_s == 4)//time counter stop and update ultrasonic sensor data
  {
    if (!digitalRead(echo))
    {
      range=micros()-time_S;
      range=range/58.2;
      step_s=0;
    }
  }
  
  if(millis()>update+100)
  {
    update=millis();
    Serial.print(step_s);
    Serial.print('\t');
    Serial.println(range,2);
    if(range<15.0)
    {
      buzzer=true;
    }
  }
  
}

