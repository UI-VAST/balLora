#include <Arduino.h>
#include <TinyGPSPlus.h>
//#include <SoftwareSerial.h>
#include <HardwareSerial.h>


/*
   This sample code demonstrates just about every built-in operation of TinyGPSPlus (TinyGPSPlus).
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int gRXPin = 18, gTXPin = 19;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
HardwareSerial lora(1);
HardwareSerial ss(2);

//timekeeping
int last = 0;
int messageFreq = 2000;


//vars [year, month, day, hour, second, altitude, lat, long, heading, speed, numSatellites]
String contents;
char delim = ',';
String na = "x";
int year;
int month;
int day;
int hour;
int minute;
int second;
float alt;
double lat;
double lng;
int heading;
float speed;
int numSats;

bool hourGood = false;
bool minuteGood = false;
bool secondGood = false;
bool altGood = false;
bool latGood = false;
bool lngGood = false;
bool headingGood = false;
bool speedGood = false;
bool numSatsGood = false;

void checkForNans(){
  if(hourGood == true){
    contents = String(hour);
  }
  else{
    contents = na;
  }
  
  if(minuteGood){
    contents = contents + delim + String(minute);
  }
  else{
    contents = contents + delim + na;
  } 

  if(secondGood){
    contents = contents + delim + second;
  }
  else{
    contents = contents + delim + na;
  } 

  if(altGood){
    contents = contents + delim + alt;
  }
  else{
    contents = contents + delim + na;
  } 

  if(latGood){
    contents = contents + delim + String(lat,6);
  }
  else{
    contents = contents + delim + na;
  } 

  if(lngGood){
    contents = contents + delim + lng;
  }
  else{
    contents = contents + delim + na;
  } 
  if(headingGood){
    contents = contents + delim + heading;
  }
  else{
    contents = contents + delim + na;
  } 
  if(speedGood){
    contents = contents + delim + speed;
  }
  else{
    contents = contents + delim + na;
  } 
  if(numSatsGood){
    contents = contents + delim + numSats;
  }
  else{
    contents = contents + delim + na;
  } 
}

void setup()
{
  Serial.begin(9600);
  lora.begin(9600, SERIAL_8N1, 16, 17);
  ss.begin(GPSBaud, SERIAL_8N1, gRXPin, gTXPin);
  
  Serial.println(F("KitchenSink.ino"));
  Serial.println(F("Demonstrating nearly every feature of TinyGPSPlus"));
  Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  
}

void loop()
{
  
  // Dispatch incoming characters
  while (ss.available() > 0)
    gps.encode(ss.read());

  if (gps.location.isUpdated())
  {
    latGood = true;
    lngGood = true;
    lat = gps.location.lat();
    lng = gps.location.lng();
    Serial.print("true")
    
  }
  else{
    latGood = false;
    lngGood = false;
  }

  /*
  if (gps.date.isUpdated())
  {
    year = gps.date.year();
    month = gps.date.month();
    day = gps.date.day();
  }
  else{
    //year = na;
    //month = na;
    //day = na;
  }
  */

  if (gps.time.isUpdated())
  {
    hourGood = true;
    minuteGood = true;
    secondGood = true;
    hour = gps.time.hour();
    minute = gps.time.minute();
    second = gps.time.second();
    Serial.print(second);
  }
  else{
    hourGood = false;
    minuteGood = false;
    secondGood = false;
  }

  if (gps.speed.isUpdated())
  {
    speedGood = true;
    speed = gps.speed.mps();
  }
  else{
    speedGood = false;
  }

  if (gps.course.isUpdated())
  {
    headingGood = true;
    heading = gps.course.deg();
  }
  else{
    headingGood = false;
  }

  if (gps.altitude.isUpdated())
  {
    altGood = true;
    alt = gps.altitude.meters();
  }
  else{
    altGood = false;
  }

  if (gps.satellites.isUpdated())
  {
    numSatsGood = true;
    numSats = gps.satellites.value(); 
  }
  else{
    numSatsGood = false;
  }
  //vars [year, month, day, hour, minute, second, altitude, lat, long, heading, speed, numSatellites]
  //contents = String(hour) + delim + String(minute) + delim + String(second) + delim + String(alt) + delim + String(lat,6) + delim + String(lng,6) + delim +String(heading) + delim +String(speed) + delim +String(numSats);
  
  //Serial.println(contents);
  if(millis() - last > messageFreq){
    last = millis();
    checkForNans();
    Serial.println("Here: ");
    Serial.print(contents);
    lora.println(contents);
  }
}

/*
void onPacketReceived(const uint8_t* buffer, size_t size)
{
  //memcpy(&rxbuf, buffer, 1);
}

void setup() {
  
  //myPacketSerial.setStream(&lora);
  //myPacketSerial.setPacketHandler(&onPacketReceived);
}

void loop(){
  packet = String(random(100));
  
  delay(1000);
}
*/
