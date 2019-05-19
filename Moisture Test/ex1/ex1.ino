int sensor_pin = 36;
int value ;
int valueCalibr;
 
void setup()
{
  Serial.begin(9600);
  Serial.println("Reading");
  delay(2000);
}
 
void loop()
{
 
  value= analogRead(sensor_pin);
  valueCalibr = map(value,3671,1264,0,100);


  Serial.print("Reading is ");
  Serial.println(value);
  
  Serial.print("Moisture : ");
  Serial.print(valueCalibr);
  Serial.println("%");
  delay(1000);
}
