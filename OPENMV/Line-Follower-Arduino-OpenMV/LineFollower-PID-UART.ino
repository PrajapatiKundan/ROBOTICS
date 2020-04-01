#include<PID_v1.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void getline(char *buffer, int max_len)
{
  uint8_t idx = 0;
  char c;
  do
  {
    if(idx >= max_len) return;
    while (mySerial.available() == 0) ; // wait for a char this causes the blocking
    c = mySerial.read();
    buffer[idx++] = c;
  }
  while (c != '\n' && c != '\r'); 
  if(idx >= max_len) return;
  buffer[idx] = 0;
}
//2,0.001,0.5
const double Kp=5;
const double Ki=0.0;
const double Kd=0.01;

 double Setpoint=87;
 double Input,Output;
 int baseSpeed;               // Base speed for your motors                                      
 int maxSpeed;
 int SpeedB;
 int SpeedA;
 PID srA(&Input,&Output,&Setpoint,Kp,Ki,Kd,DIRECT);
  const byte dir_A1 = 2;
  const byte dir_A2 = 4; 

  const byte dir_B1 = 7;
  const byte dir_B2 = 8;
  
  const byte pwm_A = 5;
  const byte pwm_B = 6;
   
void setup()
{
 Serial.begin(19200);
 mySerial.begin(19200); 
 srA.SetMode(AUTOMATIC);
 pinMode(dir_A1,OUTPUT);
 pinMode(dir_B1,OUTPUT);
 
 pinMode(pwm_A,OUTPUT);
 pinMode(pwm_B,OUTPUT);
 
 pinMode(dir_A2,OUTPUT);
 pinMode(dir_B2,OUTPUT);
 
 analogWrite(pwm_A,LOW);
 analogWrite(pwm_B,LOW);
      digitalWrite(dir_A1,0);
      digitalWrite(dir_A2,1);
      digitalWrite(dir_B1,0);
      digitalWrite(dir_B2,1);
 
}

void loop() {
 
  char buffer [63+1];
  int max_len = 63;
  getline(buffer, max_len);
  Input=atoi(buffer);
  
  srA.SetSampleTime(5);
 
      baseSpeed=150;
      maxSpeed=100;
      srA.Compute();
      srA.SetOutputLimits(-baseSpeed,baseSpeed);
      SpeedA=baseSpeed+Output;
      SpeedB=baseSpeed-Output;
      
      Serial.print(Output); 
      Serial.print("    angle= ");
      Serial.print(Input);
      Serial.print("  ");
      if(Input>=300)
      {
        SpeedA=0;
        SpeedB=0;
        analogWrite(pwm_A,SpeedA);
        analogWrite(pwm_B,SpeedB);
        Serial.print("STOP  ");
      }
      else
      {
        analogWrite(pwm_A,SpeedA);
        analogWrite(pwm_B,SpeedB);
      }
       
       Serial.print("speedA=");
       Serial.print(SpeedA);
       Serial.print("  ");
       Serial.print("speedB=");
       Serial.print(SpeedB);
       Serial.println("  ");
}
