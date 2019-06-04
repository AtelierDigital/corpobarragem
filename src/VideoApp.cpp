#include "VideoApp.h"
using namespace std;


void VideoApp::setup(){
   
    videoPlayer.load("frente.mp4");
    videoPlayer.play();
}

void VideoApp::update(){
    videoPlayer.update();
}

void VideoApp::draw() {
    ofBackground(250, 60, 60);
   
    videoPlayer.draw(0,0,WSCREENVIDEO, HSCREENVIDEO);
    
}

void VideoApp::mousePressed(int x, int y, int iButton) {
}
