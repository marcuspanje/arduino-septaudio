#include <avr/pgmspace.h>


unsigned int i = 0;
int pin12 = B1000000;
const int TOP = 400;
float input_TOP = 1024.0;
//float input_BOTTOM = 0;
float scale = TOP/input_TOP;

void setup_pwm() {
  DDRB |= pin12; //pin12 is PWM output

//configure timer1 for pwm generation
 //WGM1(3:0)=1111 fast pwm mode; CS1(2:0)=001 16Mhz clk not prescaled
 //COM1B(1:0) = 11 set oc1b on compare match
  TCCR1A = B00110011; 
  TCCR1B = B00011001;
  
  //TCNT counts from O to OCR1A. 
  //if TCNT > OCR1B, output = High; else output = low;
  OCR1B = 100;
  OCR1A = TOP;

  //enable ISR(timer1) when TCNT1 reaches top
  //TIMSK1 |= B10;
}
void setup()
{
  Serial.begin(9600);
  
  cli();
  setup_pwm();
  setup_ADC();
  sei();
 
}


void setup_ADC() //configure ADC on analog input
{
  DDRA = 0;//pin0 is input for sampling
//MUX(3:0)=0000 ADC0(pin0) input; REFS(1:0)=01 Vref=Vcc(5V). 
//ADPS(2:0)=101 ADCclk=16MHz/32=500kHz. Conversion takes 13 tcks of ADCclk 
  ADMUX = 0;
  ADCSRA = 0;
  ADMUX = _BV(REFS0);
  ADCSRA |= _BV(ADPS2) | _BV(ADPS0);
  ADCSRA |= _BV(ADEN); //turn on adc
}

void sample_input()
{
  ADCSRA |= _BV(ADSC);//start ADC
  int low = ADCL;
  int high = ADCH; 
  int adc = (high << 8) | low; 
  
  OCR1B = (unsigned int) adc >> 1; //actual formuala is top * 1024 / Vref
  //this means max value of Vin is 800*5/1024
  
}

void loop()
{ 
  sample_input();

}
