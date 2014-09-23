const int TOP = 400;
float input_TOP = 1024.0;
float input_BOTTOM = 0;
float scale = TOP/input_TOP;

void setup()
{
  Serial.begin(9600);
  cli();
  DDRB = B100; //set pin 13(6TH BIT) as output
  
//configure timers for pwm generation
  TCCR1A = 0;
  TCCR1B = 0;
 //WGM1(3:0)=1111 fast pwm mode; CS1(2:0)=001 16Mhz clk not prescaled
 //COM1B(1:0) = 11 set oc1b on compare match
 //TCCR1A = B1011xx11 ; TCCR1B = B00011001
  TCCR1A = _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11) | _BV(WGM10); 
  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);
  OCR1A = TOP;
  OCR1B = 200;
  
  //configure ADC on analog input
  DDRC = 0;//pin0 is input
//MUX(3:0)=0000 ADC0(pin0) input; REFS(1:0)=01 Vref=Vcc(5V). 
//ADPS(2:0)=101 ADCclk=16MHz/32=500kHz. Conversion takes 13 tcks of ADCclk 
  ADMUX = 0;
  ADCSRA = 0;
  ADMUX = _BV(REFS0);
  ADCSRA |= _BV(ADPS2) | _BV(ADPS0);
  ADCSRA |= _BV(ADEN); //turn on adc
  sei();
  
   
}

void loop()
{
  //read input
  ADCSRA |= _BV(ADSC);//start ADC
  int low = ADCL;
  int high = ADCH; 
  int adc = (high << 8) | low;
  //Serial.println(adc); 
  OCR1B = (int) adc*scale;
 
}