#include <TimerOne.h>

volatile int counter = 0;
const int N = 13;
volatile int increment = 1;

void setup() {
  // output pins
  //PB[3:0] = pins[11:8]
  DDRB = 0x0F;
  
  //setup timer
  Timer1.initialize(333333);
  Timer1.attachInterrupt(isr);
  Timer1.start();
}

void isr() {
  PORTB = counter & 0x000F;
  if (counter == N-1) {
      increment = -1;
  } else if (counter == 0) {
      increment = 1;
  }
  counter = counter + increment;
}
void loop() {
    
}
