#include <SPI.h>
#include <LoRa.h>
#include <U8x8lib.h>


#define SS      18
#define RST     14
#define DI0     26


int counter = 0;
int sensor_pin = 36;
int value ;
int valueCalibr;


// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);


void setup() {

  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);
  
  Serial.begin(115200);
  while (!Serial);
  delay(2000);

  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  Serial.println("LoRa Sender");
  u8x8.drawString(5, 1, "LoRa_SEND");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  //records moisture value
  value= analogRead(sensor_pin);
  valueCalibr = map(value,3671,1264,0,100);
  valueCalibr=int(valueCalibr);
  u8x8.println(valueCalibr);

  //prints moisture value to serial locally
  Serial.print("Reading is ");
  Serial.println(value);
  
  Serial.print("Moisture : ");
  Serial.print(valueCalibr);
  Serial.println("%");
  delay(1000);

  //prints packet send to serial locally
  Serial.print("Sending packet: ");
  Serial.println(counter);
  

  // send packet via LoRa
  LoRa.beginPacket();
  LoRa.print("Moisture:" + String(valueCalibr));
  //LoRa.print(valueCalibr);
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(15000);
}
