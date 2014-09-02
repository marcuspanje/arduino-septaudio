int arr[2] = {5, 6};
void setup()
{
  Serial.begin(9600);
  Serial.println(arr[0]);
  Serial.println(arr[1]);
  Serial.println(arr[2]);
  Serial.println(arr[10]);
  
  pinMode(13, OUTPUT);
}

void loop()
{
  
  
}
