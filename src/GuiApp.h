#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

class GuiApp: public ofBaseApp {
    public:
        ofxKinect kinectGlobal;
        int anguloKinect;
        ofVec2f aceleracao;

        void setup();
        void update();
        void draw();
        void mousePressed(int x, int y, int iButton) ;

        ofxImGui::Gui gui;
        float dt;
};
