#include <U8x8lib.h>
#include <LoRa.h>

String receivedText;
String receivedRssi;
String moisty;


// WIFI_LoRa_32 ports
// GPIO5  -- SX1278's SCK
// GPIO19 -- SX1278's MISO
// GPIO27 -- SX1278's MOSI
// GPIO18 -- SX1278's CS
// GPIO14 -- SX1278's RESET
// GPIO26 -- SX1278's IRQ(Interrupt Request)

#define SS      18
#define RST     14
#define DI0     26
#define BAND    868E6

// the OLED used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

void setup() {

  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(SS, RST, DI0);

  Serial.begin(115200);
  while (!Serial); //if just the the basic function, must connect to a computer
  delay(1000);

  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);

  Serial.println("LoRa Receiver");
  u8x8.drawString(5, 7, "Receiver");

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    u8x8.drawString(0, 1, "Starting LoRa failed!");
    while (1);
  }
}

void loop() {

  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    u8x8.drawString(0, 4, "PacketID");

    // read packet
    while (LoRa.available()) {
      receivedText = (char)LoRa.read();
      moisty=LoRa.read();
      
      
      Serial.print(receivedText);

      u8x8.print(receivedText);
      
      
      char currentid[64];
      receivedText.toCharArray(currentid, 64);
      u8x8.drawString(9, 4, currentid);
      
      
      
      
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println("Moisty is" + moisty);
    Serial.println(LoRa.packetRssi());
    
    
    u8x8.drawString(0, 5, "PacketRS");
    receivedRssi = LoRa.packetRssi();
    
    char currentrs[64];
    receivedRssi.toCharArray(currentrs, 64);
    u8x8.drawString(9, 5, currentrs);

    //char currenttx[32];
    //receivedText.toCharArray(currenttx, 32);
    //u8x8.drawString(0, 6, moisty);
  }

}
