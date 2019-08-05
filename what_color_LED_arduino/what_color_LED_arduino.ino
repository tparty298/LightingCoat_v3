#include <SD.h>
#include <Adafruit_NeoPixel.h>
#define PININIT        2
#define NUMPIXELS      300
#define BRIGHTNESS     255
Adafruit_NeoPixel p1=Adafruit_NeoPixel(NUMPIXELS, PININIT, NEO_GRB + NEO_KHZ800);//2
const int chipSelect = 4;
char buf;
int ret=0;
File dataFile;
int in_color[3];
int frameEndFlag=0;
int loopCount_inFrame=0;
void setup() {
  //---Serialポートを開く
  Serial.begin(9600);
  
  pinMode(SS, OUTPUT);
  SD.begin(chipSelect);

  dataFile=SD.open("output.txt");
  //buf=dataFile.read();
  //Serial.write(buf);

  //LED setup
  p1.begin();
  for(int i=0;i<NUMPIXELS;i++){
    p1.setPixelColor(i, p1.Color(0,0,0));
  }
  p1.show();
  p1.setBrightness(BRIGHTNESS);
}

void loop() {
  for(int i_color=0;i_color<3;i_color++){
    while(1){//数字が読み込まれるまで
      buf=dataFile.read();
      if ( !isspace(buf) && buf != ',' ){
        //空白でも改行でも','でもないので数字
        ret = ret*10 + (buf - '0'); //数字->数値変換
      }else{
        //数字でない時
        break;
      }
    }
    in_color[i_color]=ret;
    ret=0;
  }
  String print_string=String(in_color[0])+" "+String(in_color[1])+" "+String(in_color[2]);
  //Serial.println(print_string);
  if(in_color[0]>=0){//1フレーム中
    //ここでLEDを光らせる
    if(loopCount_inFrame<=NUMPIXELS){
      p1.setPixelColor(loopCount_inFrame,p1.Color(in_color[0],in_color[1],in_color[2]));
      p1.show();/////
    }else{
      Serial.println("Error: The number of input LED from openframeworks is over the number of LED in this program");
    }
    //LEDここまで
    loopCount_inFrame++;
  }else{//1フレームが終わる
    //LED
    //p1.show();/////
    //LEDここまで
    loopCount_inFrame=0;
  }
}

