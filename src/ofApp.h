#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxOSC.h"
#include "GuiApp.h"
#include "EmissorParticulas.h"

class ofApp : public ofBaseApp{

    protected:
        ofxOscSender sender;
        std::string OSCRemoteAddress;
        int OSCRemotePort;
    
	public:
    
		void setup();
		void update();
		void draw();

        void sendOSC();
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

        shared_ptr<GuiApp> gui;
        shared_ptr<ofAppBaseWindow> window;
        shared_ptr<ofBaseGLRenderer> gl;

        ofFbo fboColisao;
        ofImage imgColisao;
        ofPixels pixelsTemp;
        ofxCvGrayscaleImage grayImage, grayColisao; // grayscale depth image
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
        ofImage mask;
        ofPixels pixelsColisao;

        ofxCvContourFinder contourFinder;
    
        vector<EmissorParticulas*> emissores;
        float t0, t1, dt;

    
        //  Analise da depth image
        struct {
            ofPoint centroid;
            ofRectangle rectCoverage;
            float totalBlobsArea;
        } kinDepthAnalysis;
};
