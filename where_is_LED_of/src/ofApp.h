#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxCsv.h"

#define _USE_LIVE_VIDEO

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //camera
    ofVideoGrabber vidGrabber;
    ofxCvColorImage capturedImage;
    //ofxCvColorImage maskedImage;
    ofImage maskedImage;
    ofImage maskedImage_mono;
    int widthImage=1280;
    int heightImage=720;
    //
    FILE *fp;
    ofFile exportFile;
    int average_x=0;
    int average_y=0;
    
    
    //serial
    ofSerial serial;
    
    //gui
    ofxPanel gui;
    ofxIntSlider number_LED;
    ofxIntSlider hue_s;
    ofxIntSlider hue_e;
    ofxIntSlider sat_s;
    ofxIntSlider sat_e;
    ofxIntSlider val_s;
    ofxIntSlider val_e;
    
    
    int ledCount=0;
    ofTrueTypeFont ledCountText;
    
    int IsSendData=0;
    
    //mode
    int autoModeFlag=0;
    
    
    int loopCount=0;
};
