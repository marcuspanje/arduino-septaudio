const int ledpin = 13;
const int T = 400;

volatile int thigh = 280;
volatile int state = 0;
volatile int a = 0;
/*
volatile int finishT = 0;
volatile int count = 0;
int vals[2] = {100, 300};
const int sz = sizeof(vals)/sizeof(int);
const int sz_1 = sz - 1;
*/
void setup()
{
 
  cli();
  DDRB = B100000;//set pin 13(6TH BIT) as output
  PORTB = B000000;//write 0
  //set timer 1 registers
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 200; // 200 gives int freq of 40kHz
  //TCCR1B |= (1 << WGM12); // WGM12 = 3 turn on CTC mode
  TCCR1B |= (1 << CS10); // CS10 = 0 no prescaling
  TIMSK1 |= (1 << OCIE1A); // OCIE1A = 1 interrupt mask for compare match register?
  TCNT1 = 0;
  sei();
}

ISR(TIMER1_COMPA_vect) 
{

 
  if (state) {     
    OCR1A += T - thigh;
    PORTB &= B000000; //pin13 = LOW
    state = 0;
  }
  
  else {  
    //TCNT1 = 0;
    OCR1A += thigh; 
    PORTB |= B100000; // pin13 = HiGH     
    state = 1; 
  }
  
}

void loop()
{
  //Serial.println(finish-start);
 // Serial.println(a);
  //change thigh
  /*
  if (false) {
 // if (finishT) {
    thigh = 300;
    if (count == sz_1) count = 0;
    else count++;
    finishT = 0
  }  
    */    
}
