#include "ofApp.h"
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
    gui.add(number_LED.setup("number_LED",170,0,1000));
    
    ofTrueTypeFont::setGlobalDpi(144);
    ledCountText.load("Impact.ttf", 50);
    
    //camera
#ifdef _USE_LIVE_VIDEO
    //vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(widthImage, heightImage);
#endif
    capturedImage.allocate(widthImage,heightImage);
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
        capturedImage.setFromPixels(vidGrabber.getPixels().getData(),widthImage,heightImage);//~0.8.4 : getPixels(), 0.9.x~ : getPixels().getData()
        capturedImage.mirror(false, true);//画像を反転
#endif
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    capturedImage.draw(0,0);
    ledCountText.drawString("ledCount: " + ofToString(ledCount), 300, 100);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
        ledCount++;
        IsSendData=1;
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
