#include "VideoApp.h"
using namespace std;


void VideoApp::setup(){
    videoPlayer.load("frente.mp4");
    videoPlayer.play();
    ofBackground(0, 0, 0);
}

void VideoApp::update(){
    if(videoPlayer.isLoaded()) {
        videoPlayer.update();
    }
}

void VideoApp::draw() {
    if(videoPlayer.isLoaded()) {
        videoPlayer.draw(0,0,WSCREENVIDEO, HSCREENVIDEO);
    }
}

void VideoApp::mousePressed(int x, int y, int iButton) {
}
