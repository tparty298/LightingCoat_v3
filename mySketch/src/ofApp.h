#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"

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
    int widthImage=1280;
    int heightImage=720;
    
    //serial
    ofSerial serial;
    
    ofxPanel gui;
    ofxIntSlider number_LED;
    int ledCount=0;
    ofTrueTypeFont ledCountText;
    
    int IsSendData=0;
};
