//In Serial communication we can send data up to 2^8-1 = 255
//But by using this code we can send data up to 32767

int i=32767;//32767;
void setup()
{
  Serial.begin(9600);
  Serial.flush();
}

void loop()
{
  Serial.write(i/256);
  Serial.write(i%256);
  delay(10);
}
