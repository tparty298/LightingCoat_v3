#include "ofApp.h"

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
    gui.add(number_LED.setup("number_LED",1,0,1000));
}

//--------------------------------------------------------------
void ofApp::update(){
    if(IsSendData){
        serial.writeByte(Byte(1));
    }
    IsSendData=0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 's'){
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
