#include <SPI.h>
#include <LoRa.h>


#define SS      18
#define RST     14
#define DI0     26


int counter = 0;
int value = 0;

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}

#endif
uint8_t temprature_sens_read();



void setup() {

  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);
  
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  value = hallRead();

  //Far to Cel
  float tempss = (temprature_sens_read() - 32) / 1.8;
  delay(1000);

  
  Serial.println("Temp: " + String(tempss));
  Serial.println("Hall sensor: " + String(value));
  
  Serial.print("Sending packet: ");
  Serial.println(counter);
  

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print("hall is" + String(value));
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
