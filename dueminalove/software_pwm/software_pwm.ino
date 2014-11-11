const int T = 400;

volatile int thigh = 0;
volatile int tlow = 0;

volatile int state = 0;
volatile unsigned int pwmcount = 0;
volatile unsigned int pwmcount0 = 0;

volatile int a = 99;
volatile unsigned int count = 0;
volatile int getnewT = 0;

const int nvals = 2;
int vals[nvals] = {200}; //limit is 145

void setup()
{
  Serial.begin(9600);
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
  
}

ISR(TIMER1_COMPA_vect) { 

  if (state) {     
    PORTB &= B000000; //pin13 = LOW
    OCR1A += tlow;

    if (tlow < 145) {
      while (TCNT1 < OCR1A){}
      getnewT = 1;
      PORTB |= B100000;
      OCR1A += thigh;

    }

    else {
      state = 0;
      getnewT = 1;
    }
    //pwmcount++;
  }

  else {  
    PORTB |= B100000; // pin13 = HiGH     
    OCR1A += thigh;
    
    if (thigh < 145) {
      while (TCNT1 < OCR1A) {}
      PORTB |=B000000;
      OCR1A += tlow;
      //pwmcount++;
      getnewT = 1;
    }
    else state = 1; 
  }

}

void loop()
{

  if (getnewT) {
    count++;
    thigh = vals[count % nvals];
    tlow = T - thigh;
    Serial.println(thigh);
    Serial.println(tlow);
    getnewT = 0;
    //a = pwmcount - pwmcount0;
    //Serial.println(a);
  }
  

}

