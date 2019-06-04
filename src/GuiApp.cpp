#include "GuiApp.h"
#include <vector>
using namespace std;

float t0, t1;

void GuiApp::setup(){
    gui.setup();
    ImGui::GetIO().MouseDrawCursor = false;
    anguloKinect = 14;
    contrasteKinect = 0.7;
    brilhoKinect = 0.8;
    blurKinect = 3;
    
    nearThreshold_Kinect = 100;	
    farThreshold_Kinect = 1100;
}

void GuiApp::update(){
    t0 = t1;
    t1 = ofGetElapsedTimef();
    dt = t1 - t0; //tempo desde o ultimo update
}

void GuiApp::draw() {
    ofBackground(60, 60, 60);

    gui.begin();

    ImGui::SetNextWindowSize(ofVec2f(20, 10), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Controles Gerais");

    // Botões de liga e desliga do kinect
    if ( kinectGlobal.isConnected() ) {
        kinectGlobal.setCameraTiltAngle(anguloKinect);
        ImGui::SliderInt("angulo", &anguloKinect, -30, 30);
        ImGui::SliderFloat("Brilho", &brilhoKinect, 0, 1);
        ImGui::SliderFloat("Contraste", &contrasteKinect, 0, 1);
        ImGui::SliderInt("Blur", &blurKinect, 0, 50);
        ImGui::SliderFloat("Near", &nearThreshold_Kinect, 100, 3000);
        ImGui::SliderFloat("Far", &farThreshold_Kinect, 200, 8000);
        if (ImGui::Button("Desliga Kinect")) { 
            kinectGlobal.close();
        } 
    } else {
        if (ImGui::Button("Ligar Kinect")) { 
            if( !kinectGlobal.isConnected() ) {
                kinectGlobal.setRegistration(true);
                kinectGlobal.init();
                kinectGlobal.open();
                kinectGlobal.setCameraTiltAngle(0);
            }
        }
    }
    ImGui::Text("%.1f FPS (%.3f ms/frame) ", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);

    ImGui::End();
    gui.end();
}

void GuiApp::mousePressed(int x, int y, int iButton) {
}
