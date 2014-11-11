
void setup()
{
  Serial.begin(9600);
  //pinMode(11, OUTPUT);
  DDRB = B100000;;
}

void loop()
{
  PORTB = B100000;
  delay(1000);
  PORTB = B0;
  delay(1000);
}

