#include <Arduino.h>
#include <HardwareSerial.h>
//#include <PacketSerial.h>
//#include <ASLUAV/mavlink.h>



HardwareSerial lora(1);

//PacketSerial myPacketSerial;
String message;
//double contents;
/*
void onPacketReceived(const uint8_t* buffer, size_t size)
{
  memcpy(&message, &buffer[0], 8);
  contents = message;
  Serial.println("Message Recieved");
}
*/
void setup() {
  Serial.begin(9600);
  //pinMode(2, OUTPUT);
  lora.begin(9600, SERIAL_8N1, 17, 16);
  //myPacketSerial.setStream(&lora);
  //myPacketSerial.setPacketHandler(&onPacketReceived);
  Serial.println("setup loop complete");
  
}

void loop() {
  //myPacketSerial.update();
  if(lora.available()){
    message = lora.readString();
    Serial.println(message);
  }
}