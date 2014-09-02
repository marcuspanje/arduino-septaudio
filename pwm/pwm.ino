const int ledpin = 13;
const int T = 400;
volatile int state = 0;
const int sz  = 2;
const int sz_1 = sz - 1;
int vals[sz] = {50, 350};
volatile int count = 0;
volatile int a = 0;
volatile int b = 0;
volatile int c = 0;
volatile int thigh = 100;

void setup()
{
  cli();
  DDRB = B100000;//set pin 13(6TH BIT) as output
  PORTB = B000000;//write 0
  
  //set timer 1 registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 200; // 200 gives int freq of 40kHz
  //TCCR1B |= (1 << WGM12); // WGM12 = 3 turn on CTC mode
  TCCR1B |= (1 << CS10); // CS10 = 0 no prescaling
  TIMSK1 |= (1 << OCIE1A); // OCIE1A = 1 interrupt mask for compare match register?
  sei();
  Serial.begin(9600);
  Serial.println(WGM12);
  Serial.println(CS10);
  Serial.println(OCIE1A); 
  
}

ISR(TIMER1_COMPA_vect) 
{
  if (state) {  
    OCR1A = TCNT1 + T - thigh;
    //Serial.println(TCNT1);
    //TCNT1 = 0; // reset timer
    PORTB &= B000000; //pin13 = LOW
    state = 0;
  }
  else {
    OCR1A = TCNT1 + thigh;
    a = OCR1A - TCNT1;
    /*
    if (count == sz - 1)
      count = 0;
    else
      count ++;
      */
     // pin13 = HiGH
    PORTB |= B100000;
    state = 1; 
  }
}

void loop()
{ 
  Serial.println(a);
}
