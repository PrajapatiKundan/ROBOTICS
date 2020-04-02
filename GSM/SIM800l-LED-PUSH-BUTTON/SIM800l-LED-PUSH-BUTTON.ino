#include <SoftwareSerial.h>
SoftwareSerial sim(10, 11);
int _timeout;
String _buffer;
String number = "**********";//put the phone number here 


//button
int buttonState = 0;
int pre,n;
int c=0;
int flag1=0;
int flag2=0;

int led=13;
void setup() 
{
  delay(2000); 
  Serial.begin(9600);
  pinMode(2, INPUT);
  _buffer.reserve(50);
  Serial.println("Sistem Started...");
  sim.begin(9600);
  delay(1000);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() 
{
  buttonState = digitalRead(2);
  n=buttonState;
  if(n!=pre && n==1)
  {
    c++; 
  }
  pre=n;
  //if(c>3)c=0;

  Serial.print("c = ");
  Serial.println(c);

  if(c==1 && flag1==0)//c=1
  {
    for(int i=0;i<2;i++)
    {
     digitalWrite(led,HIGH);
     delay(500);
     digitalWrite(led,LOW);
     delay(500);
    }
    digitalWrite(led,LOW);
    SendMessage();
  }
  if(c==2 && flag1==1 && flag2==0)
  {
    for(int i=0;i<3;i++)
    {
     digitalWrite(led,HIGH);
     delay(500);
     digitalWrite(led,LOW);
     delay(500);
    }
    digitalWrite(led,LOW);
    callNumber();
    
  }
  if(c==3)
  {
    flag1=0;
    flag2=0;
    c=0;
  }
    
  if (sim.available() > 0)
    Serial.write(sim.read());
}


void SendMessage()
{
  Serial.println("Send msg");
  sim.println("AT+CMGF=1");    
  sim.println("AT+CMGS=\"" + number + "\"\r"); 
  delay(1000);
  String SMS = "write your msg here that you want to send";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(1000);
  _buffer = _readSerial();
  //flag=1;
  flag1=1;
}


void RecieveMessage()
{
  Serial.println ("SIM800L Read an SMS");
  delay (1000);
  sim.println("AT+CNMI=2,2,0,0,0"); 
  delay(1000);
  Serial.write ("Unread Message done");
}

String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}

void callNumber()
{
  Serial.println("call number");
  sim.print (F("ATD"));
  sim.print (number);
  sim.print (F(";\r\n"));
  _buffer = _readSerial();
  Serial.println(_buffer);
  //delay(1000);
  Serial.println("call end");
  //flag=1;
  flag2=1;
}
