const int TOP = 400;
float maxinput_v = 1.5;
float maxinput_units = 1023*maxinput_v/5.0;
float scale = TOP / maxinput_units;
//int scale = 2;

void setup()
{
  DDRC = B0;
  
  DDRB = B100; //set pin 13(6TH BIT) as output
  TCCR1A = 0;
  TCCR1B = 0;
 //WGM1(3:0) = 1111 fast pwm mode  ;  CS1(2:0) = 001 16Mhz clk not prescaled
 //COM1B(1:0) = 11 set oc1b on compare match
 //TCCR1A = B1011xx11 ; TCCR1B = B00011001
  TCCR1A = _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11) | _BV(WGM10); 
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
  OCR1A = TOP;
  OCR1B = 200;
  
  Serial.begin(9600);
  
  Serial.println('print');
  Serial.println(maxinput_units);
  Serial.println(scale);
}

void loop()
{
  int a = analogRead(0);
  //Serial.println(a);
  OCR1B = (int) a*scale;
  
  
  //change OCR1B
}
