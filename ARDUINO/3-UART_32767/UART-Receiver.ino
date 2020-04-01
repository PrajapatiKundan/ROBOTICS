//In Serial communication we can send data up to 2^8-1 = 255
//But by using this code we can send data up to 32767

byte b1;
byte b2;
int s;
void setup()
{
  Serial.begin(9600);
  Serial.flush();
}

void loop()
{
  b1=Serial.read();
  b2=Serial.read();
  s=(int)(b1*256)+(int)b2;
  Serial.println(s);
  delay(10);
  
}
