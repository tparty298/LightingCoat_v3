#include "ofApp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
    serial.listDevices();
    if(!serial.setup(1, 9600)) {
        // log and error and leave
        ofLogError() << "could not open serial port - listing serial devices";
        serial.listDevices();
        OF_EXIT_APP(0);
    }
    
    ofBackground(0,0,0);
    gui.setup();
    gui.add(number_LED.setup("number_LED",300,0,1000));/////
    gui.add(hue_s.setup("hue_s",0,0,255));
    gui.add(hue_e.setup("hue_e",10,0,255));
    gui.add(sat_s.setup("sat_s",180,0,255));
    gui.add(sat_e.setup("sat_e",255,0,255));
    gui.add(val_s.setup("val_s",240,0,255));
    gui.add(val_e.setup("val_e",255,0,255));
    ofTrueTypeFont::setGlobalDpi(144);
    ledCountText.load("Impact.ttf", 50);
    
    //camera
#ifdef _USE_LIVE_VIDEO
    //vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(widthImage, heightImage);
#endif
    capturedImage.allocate(widthImage,heightImage);
    maskedImage.allocate(widthImage,heightImage,OF_IMAGE_COLOR);
    maskedImage_mono.allocate(widthImage,heightImage,OF_IMAGE_GRAYSCALE);
    
    //export file
    /*
    fp=fopen("export1.txt","w+");
    if(fp==NULL){
        std::cout<<"there is no file to export\n";
    }else{
        std::cout<<"file ok\n";
    }
    */
    exportFile.open("export.txt",ofFile::ReadWrite);//ReadWrite //WriteOnly
}

//--------------------------------------------------------------
void ofApp::update(){
    if(IsSendData){
        serial.writeByte(Byte(1));
    }
    IsSendData=0;
    
    //camera
#ifdef _USE_LIVE_VIDEO
    bool bNewFrame=false;
    vidGrabber.update();//vidGrabber.grabFrame();はエラー
    bNewFrame=vidGrabber.isFrameNew();
#endif
    
    if(bNewFrame){
    #ifdef _USE_LIVE_VIDEO
            int masked_x=0;
            average_x=0;
            int masked_y=0;
            average_y=0;
            int masked_num=0;
                capturedImage.setFromPixels(vidGrabber.getPixels().getData(),widthImage,heightImage);//~0.8.4 : getPixels(), 0.9.x~ : getPixels().getData()
            capturedImage.mirror(false, true);//画像を反転
            unsigned char *maskedImage_data = maskedImage.getPixels().getData();
            unsigned char *maskedImage_mono_data = maskedImage_mono.getPixels().getData();
            //全ピクセル探索
           //
            for(int y=0;y<heightImage;y++){//なんでここに3を掛けないといけないは分からない
                for(int x=0;x<widthImage;x++){
                    int index=y*widthImage+x;
                    int valR_index=capturedImage.getPixels().getData()[index*3];
                    int valG_index=capturedImage.getPixels().getData()[index*3+1];
                    int valB_index=capturedImage.getPixels().getData()[index*3+2];
                    
                    ofColor pixelColorRGB_index(valR_index,valG_index,valB_index);
                    int valH_index=pixelColorRGB_index.getHue();
                    int valS_index=pixelColorRGB_index.getSaturation();
                    int valV_index=pixelColorRGB_index.getBrightness();
                    
                    ofColor pixelColorHSV_index(valH_index,valS_index,valV_index);
                    if(hue_s<=valH_index&&valH_index<=hue_e&&sat_s<=valS_index&&valS_index<=sat_e&&val_s<=valV_index&&valV_index<=val_e){
                        maskedImage_data[index*3+0]=valR_index;
                        maskedImage_data[index*3+1]=valG_index;
                        maskedImage_data[index*3+2]=valB_index;
                        //計算処理
                        masked_x+=x;
                        masked_y+=y;
                        masked_num++;
                    }else{
                        maskedImage_data[index*3+0]=0;
                        maskedImage_data[index*3+1]=0;
                        maskedImage_data[index*3+2]=0;
                    }
                }
            }
            //平均計算処理
            if(masked_num==0){
                average_x=0;
                average_y=0;
            }else{
                average_x=masked_x/masked_num;
                average_y=masked_y/masked_num;
            }
            //
            maskedImage.update();
    #endif
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    //capturedImage.draw(0,0);
    maskedImage.draw(0,0);
    ledCountText.drawString("ledCount: " + ofToString(ledCount), 300, 100);
    gui.draw();
    ofSetColor(255);
    ofCircle(average_x,average_y,10);
    
    if(autoModeFlag==1&&(ledCount<=number_LED)){
        if((loopCount%6)==0){
            ledCount++;
            IsSendData=1;
        }else if((loopCount%6)==3){
            exportFile<<average_x<<","<<average_y<<"\n";
            std::cout<<average_x<<","<<average_y<<std::endl;
        }
    }
    loopCount++;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        ledCount++;
        IsSendData=1;
    }
    if(key == 'a'){
        /*
        fprintf(fp,"%d %d\n",average_x,average_y);
        */
        //exportFile<<average_x<<","<<average_y<<"\n";
        //std::cout<<average_x<<","<<average_y<<std::endl;
    }
    if(key == 'e'){
        OF_EXIT_APP(0);
    }
    if(key =='o'){//オートモード
        autoModeFlag=1;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
