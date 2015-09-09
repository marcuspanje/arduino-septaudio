#include <avr/pgmspace.h>

/*
output pins: 12 (PWM wave) input pins: 2 (enable output switch)

MATLAB model PWModulates an input sound file, obtaining duty cycle
data for each period at 40 kHz. These values are stored in Flash (32kB) if 
PROGMEM is specified. If not, values are stored in SRAM(2kB).
see arduino.cc/en/Tutorial/Memory
 
setup() configures the internal PWM to do the following:
timer counts from 0 to 400.
At tick i, if counter > signal[i], output = HIGH;
else output = LOW;
See Fast PWM Mode in pg 145 of atmega 2560 datasheet:
*/

//siren sound
const int len = 10;
short int const sig[len] PROGMEM = 
{20, 171, 300, 171, 20, 229, 300, 22, 25, 229};

unsigned int i = 0;
int pin12 = B1000000;

void setup()
{
  //Serial.begin(9600);
  cli();
  DDRB |= pin12; //pin12 is PWM output

//configure timer1 for pwm generation
 //WGM1(3:0)=1111 fast pwm mode; CS1(2:0)=001 16Mhz clk not prescaled
 //COM1B(1:0) = 11 set oc1b on compare match
  TCCR1A = B00110011; 
  TCCR1B = B00011001;
  
  //TCNT counts from O to OCR1A. 
  //if TCNT > OCR1B, output = High; else output = low;
  OCR1B = 100;
  OCR1A = 400;

  //enable ISR(timer1) when TCNT1 reaches top
  TIMSK1 |= B10;
  
  sei();
 
}

ISR(TIMER1_COMPA_vect) //iterate through sequence of values 
{
  
   //read data from program memory 
   OCR1B = pgm_read_word_near((i%len) + sig);
   i++;
}

void loop()
{
}
