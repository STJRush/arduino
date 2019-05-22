
#include <ESP32Servo.h>

// Include library to connect the ESP32 to the internet
 
#include <WiFi.h>

#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

//const char* ssid     = "dnet"; // Your SSID (Name of your WiFi)
//const char* password = "48151623"; //Your Wifi password

const char* ssid     = "Free WiFi Hodson Bay Hotel 3"; // Your SSID (Name of your WiFi)
const char* password = ""; //Your Wifi password


const char* host = "api.thingspeak.com";
String api_key = "K3Y5WNN2D6BI72J1"; // Your API Key provied by thingspeak

const int hygrometer = 33;  
int value;

Servo myservo; // atach the servo

int temp = 0; // setup a int to simulate a temp

const int ledGreen = 32;
const int ledRed = 25;

void setup(){
  
  Serial.begin(9600);
  pinMode(ledGreen, OUTPUT);
  digitalWrite(ledGreen, LOW);  
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledRed, LOW);  

  myservo.attach(26);
   myservo.write(0);

     Connect_to_Wifi();
}

void loop(){

  
  value = analogRead(hygrometer);   
  value = value;
  
  Serial.print("Soil humidity: ");
  Serial.print(value);
  Serial.println("%");
  delay(2000); 

  if (value < 2000){

  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledRed, LOW);

}

 if (value > 2000){

  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, HIGH);

  
}

temp = temp + 10;   // Every two seconds the temperature rises by 10.

if (temp < 120){
  
   myservo.write(180);  // the lid is closed under the 120.
}

if (temp > 120){
  
   myservo.write(0); // the lid is open after the 120.
}

if (temp > 150){
  
  temp = 0; // the temperature drops after the lid is open for some seconds.
}

// now we will also print the temperature in the serial monitor.

Serial.print("temperature: ");
  Serial.print(temp);
  Serial.println("'C");

  
 // call function to send data to Thingspeak
  Send_Data();

  delay(55000);
 

}

void Connect_to_Wifi()
{

  // We start by connecting to a WiFi network
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void Send_Data()
{

  // map the moist to 0 and 100% for a nice overview in thingspeak.
  
  value = constrain(value,0,5000);
  value = map(value,0,5000,100,0);

  Serial.println("Prepare to send data");

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(value);
    //data_to_send += "&field2=";
    //data_to_send += String(temp);
    // data_to_send += "&field3=";
    // data_to_send += String(pressure);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    delay(1000);
  }

  client.stop();

}
