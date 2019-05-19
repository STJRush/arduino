#include <SPI.h>
#include <LoRa.h>


#define SS      18
#define RST     14
#define DI0     26


int counter = 0;

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
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(5000);
}
