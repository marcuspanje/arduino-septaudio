void setup()
{
  DDRB = B100000;  
  PORTB = B100000;
}

void loop()
{
  PORTB = B100000;
  delay(100);
 // PORTB = PORTB | (0 << 6);
  PORTB = B000000;
  delay(100);
}
