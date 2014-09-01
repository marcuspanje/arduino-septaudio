int ledpin = 13;
int T_counter = 400;
int state = 0;
//int vals[11] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400};
int vals[5] = {50, 100, 150, 200, 250};
volatile int count = 0;
int sz = sizeof(vals)/sizeof(int);

void setup()
{
  cli();
  DDRB = B100000;//set pin 13(6TH BIT) as output
  //set timer 1 registers
   
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 200; // 200 gives int freq of 40kHz
 
  TCCR1B |= (1 << WGM12); // WGM12 = 3 turn on CTC mode
  TCCR1B |= (1 << CS10); // CS10 = 0 no prescaling
  TIMSK1 |= (1 << OCIE1A); // OCIE1A = 1 interrupt mask for compare match register?
   
  sei();
  Serial.begin(9600);
  Serial.print(sz);
  Serial.println();
}

ISR(TIMER1_COMPA_vect) 
{
  if (state) {  
    OCR1A = T_counter - OCR1A;  
    PORTB = B000000; //pin13 = LOW
 // digitalWrite(13, LOW);
    state = 0;
   
  }
  else {
    OCR1A = vals[count];
    if (count == sz-1) 
      count = 0;
    else 
      count++;
      
    PORTB = B100000; // pin13 = HiGH
    state = 1; 
  }
}

void loop()
{ 

}
