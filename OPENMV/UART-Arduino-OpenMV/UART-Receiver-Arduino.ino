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

void setup() {
Serial.begin(19200);
mySerial.begin(19200); 
}

void loop(){
  char buffer [63+1];
  int max_len = 63;
  getline(buffer, max_len);
  Serial.print(buffer);
}
