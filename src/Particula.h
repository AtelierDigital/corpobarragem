#include "ofxImGui.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "Constants.h"

class Particula {
    public:
        Particula(float x,float y);
        ofVec2f pos;
        ofVec2f velocidade;
        ofColor cor;

        void update(float dt, ofVec2f aceleracao, ofPixels pixelsKinect);
        void draw();
};
