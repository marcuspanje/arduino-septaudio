int a = 1;
void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  a++;
  if (a%100 == 0)
    Serial.println(a);
  
}
