//By this code we can count the number of time push button pressed.
int buttonState = 0;
int pre,n;
int c=0;

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
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
  
  Serial.print("       ");
  Serial.println(c);
  delay(10);
}
