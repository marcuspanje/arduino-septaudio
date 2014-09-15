const int T = 400;

volatile int thigh = 0;
volatile int tlow = 0;

volatile int state = 0;
volatile unsigned int pwmcount = 0;
volatile unsigned int pwmcount0 = 0;

const int nvals = 2;
int vals[nvals] = {200, 300}; //limit is 145

void setup()
{
  cli();
  DDRB = B100000; //set pin 13(6TH BIT) as output
  PORTB = B000000; //write 0
  //set timer 1 registers
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 200; // 200 gives int freq of 40kHz
  //TCCR1B |= (1 << WGM12); // WGM12 = 3 turn on CTC mode
  TCCR1B |= (1 << CS10); // CS10 = 0 no prescaling
  TIMSK1 |= (1 << OCIE1A); // OCIE1A = 1 interrupt mask for compare match register?
  TCNT1 = 0;
  thigh = 200;
  tlow = 200;
  sei();
  Serial.begin(9600);
}

ISR(TIMER1_COMPA_vect) { 

  if (state) {     
    PORTB &= B000000; //pin13 = LOW
    OCR1A += tlow;
    state = 0;
    
    /*
    if (tlow < 100) {
      while (TCNT < OCR1A) ;
      PORTB |= B100000;
      OCR1A += thigh;
    }
    else {
      state = 0;
    }
    */

    pwmcount++;
  }
  
  else {  
    PORTB |= B100000; // pin13 = HiGH     
    OCR1A += thigh;
    state = 1; 
  }
  
}

void loop()
{

  if (pwmcount0 != pwmcount)  {
    pwmcount0 = pwmcount;
    thigh = vals[pwmcount0 % nvals];
    tlow = T - thigh;
  }
   
}
