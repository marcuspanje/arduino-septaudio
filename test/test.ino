#include <EEPROM.h>
void setup()
{
  for (int i = 0; i < 512; i++)
   EEPROM.write(i, 0);   
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
  
}
