#include "ofApp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#define WIDTH 1280
#define HEIGHT 720
//動画の変換は以下のようなコマンド
//ffmpeg -i motion.mov -pix_fmt yuv420p motion.mp4
//連番画像の生成
//ffmpeg -i motion.mp4 -vcodec png -r 60 ../image/image_%04d.png
//エクスポートした~.txtを~.csvに手動で変換してから使う

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    //ofSetFrameRate(30);
    
    //txt
    outputFile.open("output.txt",ofFile::WriteOnly);
    
    //csv
    ofSetLogLevel("ofxCsv",OF_LOG_VERBOSE);
    //CSVファイルの読み込み
    if(inputCsv.load("cloth_export.csv")){
        std::cout<<"csvファイルをエクスポートします"<<std::endl;
        for(int i=0;i<inputCsv.getNumRows();i++){
            ofxCsvRow row=inputCsv[i];
            LED_pos.push_back({row.getInt(0),row.getInt(1)});
            //std::cout<<row.getInt(0)<<","<<row.getInt(1)<<std::endl;
        }
    }
    LED_NUM=inputCsv.getNumRows();
    
    inputMovie.load("movies/motion.mp4");
    inputMovie.setLoopState(OF_LOOP_NORMAL);
    inputMovie.play();
    
    nowScreen.allocate(1280,720,OF_IMAGE_COLOR);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    std::cout<<"loopCount: "<<loopCount<<std::endl;
    //inputMovie.update();
    
    //画像連番の名前を取得
    std::ostringstream ss;
    ss << std::setw(4) << std::setfill('0') << loopCount+1; //4桁の時
    std::string file_name_digit(ss.str());
    file_name="image/image_"+file_name_digit+".png";
    std::cout<<"import: "<<file_name<<std::endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    //動画の再生
    //inputMovie.draw(0,0,1280,720);
    //inputMovie.draw(0,0);
    //nowScreen.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    //画像連番の時は以下
    if(!nowScreen.load(file_name)){
        std::cout<<"連番画像の読み込みに失敗したか、計算が終了したのでウィンドウを閉じます"<<std::endl;
        OF_EXIT_APP(0);
        
    }
    nowScreen.draw(0,0);
    
    unsigned char *nowScreen_data = nowScreen.getPixels().getData();
    //全ピクセル探索
    for(int i=0;i<LED_NUM;i++){
        for(int y=0;y<HEIGHT;y++){
            for(int x=0;x<WIDTH;x++){
                int index=y*WIDTH+x;
                int valR_index=nowScreen.getPixels().getData()[index*3];
                int valG_index=nowScreen.getPixels().getData()[index*3+1];
                int valB_index=nowScreen.getPixels().getData()[index*3+2];
                ofColor pixelColorRGB_index(valR_index,valG_index,valB_index);
                int valH_index=pixelColorRGB_index.getHue();
                int valS_index=pixelColorRGB_index.getSaturation();
                int valV_index=pixelColorRGB_index.getBrightness();
                if((x==LED_pos[i][0])&&(y==LED_pos[i][1])){
                    //std::cout<<valR_index<<","<<valG_index<<","<<valB_index<<std::endl;
                    //std::cout<<x<<","<<y<<"\n";
                    outputFile<<valR_index<<","<<valG_index<<","<<valB_index<<"\n";
                }
            }
        }
    }
    outputFile<<-1<<","<<-1<<","<<-1<<"\n";
    
    //最後に以下の処理をする
    ofSetColor(255);
    ofNoFill();
    for(int i=0;i<LED_NUM;i++){
        ofCircle(LED_pos[i][0],LED_pos[i][1],5);
    }
    
    loopCount++;
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
