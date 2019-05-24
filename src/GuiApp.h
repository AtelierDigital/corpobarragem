#pragma once

#include "ofxImGui.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Particula.h"

class GuiApp: public ofBaseApp {
    public:
        vector<Particula*> particulas;
        
        ofxKinect kinectGlobal;
        int anguloKinect;
        int brilhoKinect;
        int contrasteKinect;
        int blurKinect;
        bool mirrorKinect;
        bool mirrorTela;

        ofVec2f aceleracao;

        void setup();
        void update();
        void draw();
        void mousePressed(int x, int y, int iButton) ;

        ofxImGui::Gui gui;
        float dt;
};
