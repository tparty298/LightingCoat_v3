#include "ofApp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//#define WIDTH 830
//#define HEIGHT 1260

#define WIDTH 450
#define HEIGHT 650

#define CLOTH_IMAGE_WIDTH 415
#define CLOTH_IMAGE_HEIGHT 630
//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
    serial.listDevices();
    if(!serial.setup(1, 9600)) {
        // log and error and leave
        ofLogError() << "could not open serial port - listing serial devices";
        serial.listDevices();
        OF_EXIT_APP(0);
    }
    cloth_image.load("cloth.png");
    ledCountText.load("Impact.ttf", 50);
    
    exportFile.open("export.txt",ofFile::WriteOnly);//ReadWrite //WriteOnly
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    cloth_image.resize(415,630);
    cloth_image.draw(20,10);
    
    ledCountText.drawString("ledCount: " + ofToString(ledCount), 50, 100);
    ofSetColor(255,0,0);
    for(int i=0;i<pos.size();i++){
        ofCircle(pos[i].x,pos[i].y,radius);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'e'){
        OF_EXIT_APP(0);
    }else if(key=='s'){
        ledCount++;
        serial.writeByte(Byte(1));
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
    exportFile<<x<<","<<y<<"\n";
    std::cout<<x<<","<<y<<std::endl;
    ofVec2f p;
    p.set(x,y);
    pos.push_back(p);
    ledCount++;
    serial.writeByte(Byte(1));
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
