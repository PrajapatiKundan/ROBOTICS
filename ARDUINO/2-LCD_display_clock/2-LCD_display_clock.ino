#include<LiquidCrystal.h>
LiquidCrystal LCD(10,9,5,4,3,2);
int h=0,m=0,s=0;

void setup() 
{
  LCD.begin(16,2);
  LCD.setCursor(0,0);
  LCD.print("H    M    S");
  Serial.begin(9600);
}

void loop() {
  
  if(s==60)
  {
    m++;
    s=0;
    if(m==60)
    {
      h++;
      m=0;
      LCD.setCursor(0,1);
      LCD.print("                ");
      if(h==24)
      {
        h=0;
        LCD.setCursor(0,1);
        LCD.print("                ");
      }
      
    }
  }
    
  
  LCD.setCursor(0,1);
  LCD.print(h);
  LCD.setCursor(5,1);
  LCD.print(m);
  LCD.setCursor(10,1);
  LCD.print(s);
  delay(1000);
  s++;
  
}
