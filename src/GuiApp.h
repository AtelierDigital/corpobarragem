#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Particula.h"

class GuiApp: public ofBaseApp {
    public:
        
        ofxKinect kinectGlobal;
        int anguloKinect;
        float brilhoKinect;
        float contrasteKinect;
        int blurKinect;
        bool mirrorKinect;
        bool mirrorTela;

        void setup();
        void update();
        void draw();
        void mousePressed(int x, int y, int iButton) ;

        ofxImGui::Gui gui;
        float dt;
};
