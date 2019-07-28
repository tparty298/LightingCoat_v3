#include <Adafruit_NeoPixel.h>
#define PININIT        2
#define NUMPIXELS      100
#define BRIGHTNESS     255
int readByte = 0;
int ledCount = 0;
Adafruit_NeoPixel p1=Adafruit_NeoPixel(NUMPIXELS, PININIT, NEO_GRB + NEO_KHZ800);//2

void setup(){
  Serial.begin(9600);
  p1.begin();
  p1.setBrightness(BRIGHTNESS);
  for(int i=0;i<NUMPIXELS;i++){
    p1.setPixelColor(i, p1.Color(0,0,0));
  }
  p1.show();
}

void loop(){
  if(ledCount<NUMPIXELS){
    Serial.println("end");
  }else if (Serial.available() > 0) {
    readByte = Serial.read();
    //Serial.println(readByte, DEC);
    if(readByte==1){
      Serial.print("now: ");
      Serial.println(ledCount);
      for(int i=0;i<NUMPIXELS;i++){
        p1.setPixelColor(i, p1.Color(0,0,0));
      }
      p1.setPixelColor(ledCount, p1.Color(0,0,0));
      p1.show();
      ledCount++;
    }
  }
}

//You should send data drom oF (ex:writeByte) 
//after you open your serial port
//(you should use push button 'a' to begin sendind data from oF)
