void setup()
{
  DDRB = B100; //set pin 13(6TH BIT) as output
  TCCR1A = 0;
  TCCR1B = 0;
  // B11000011 bit6=toggle OC on match, 
    //bit(2:1)=B10 bit PWM
  TCCR1A =  _BV(COM1A0) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11) | _BV(WGM10); 
  
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(0); // B00001001 bit3 = clear on compare
  OCR1A = 400;
  OCR1B = 200;
  Serial.begin(9600);  
  Serial.println(WGM13);
  Serial.println(WGM12);
  Serial.println(WGM11);
  Serial.println(WGM10);
  Serial.println(COM2B1);
  Serial.println(COM2A0);
}

void loop()
{
  
}
