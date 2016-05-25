#define lednum 20

void setup()
{
  pinMode(8,OUTPUT);
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
}
int dly;
float a;

void loop()
{
  a=analogRead(0);
  dly=(a/1024.0)*100;
  
  digitalWrite(8,HIGH);
  digitalWrite(2,HIGH);
  delay(dly);
  digitalWrite(8,LOW);
  digitalWrite(2,LOW);
  delay(dly); 
}
