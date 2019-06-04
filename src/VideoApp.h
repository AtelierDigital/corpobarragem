#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Particula.h"

class VideoApp: public ofBaseApp {
public:
    
    ofVideoPlayer videoPlayer;
    
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int iButton) ;
    
};
