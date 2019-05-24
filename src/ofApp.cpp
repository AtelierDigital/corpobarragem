#include "ofApp.h"

const int HKINECT = 640;
const int WKINECT = 480;
const int HSCREEN = 1920;
const int WSCREEN = 1080;

ofPixels pixelsKinect;

Particula::Particula(float x, float y) {
    pos.set(x, y);
    velocidade.set(0, 0);
    cor.set(255,220,255,255);
    cor.setBrightness(100);
}

void Particula::update(float dt, ofVec2f aceleracao) {
    velocidade+= aceleracao * dt;
    pos += velocidade * dt;
    if ( pos.x > HKINECT ) {
        pos.x = HKINECT;
        // mata
    }
    cor.setHue( cor.getHue() + dt*100 );

    // Colisão simple com 8 pontos
    int raioColisao = 5;
    for(float rad = 0; rad < TWO_PI; rad += TWO_PI/8) {
        ofVec2f vetorColisao(cos(rad), sin(rad));
        ofVec2f pontoColisao = vetorColisao * raioColisao;
        pontoColisao += pos;
        float pixelValue = 0;
        int xk = int(pontoColisao.x);
        int yk = int(pontoColisao.y);
        if(xk < WKINECT && yk < HKINECT && xk>0 && yk>0) {
            pixelValue = pixelsKinect[ yk*HKINECT + xk];
        }
        if(pixelValue > 180) {
        cout << "\n" << pixelValue <<":"<< vetorColisao.x << "," << vetorColisao.y << " ";
            pos -= vetorColisao;
        }
    }
    
}

void Particula::draw() {
    ofSetColor(cor);
    
    // A particula vive no limite das medida do kinect
    // mas é desenha de acordo com o tamanho da tela
    ofDrawCircle( (pos.x/HKINECT)*HSCREEN, (pos.y/WKINECT)*WSCREEN, 2);
}



int qtdPorSegundo = 7;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0); 
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float qtdSegundos = ofGetElapsedTimef()/1;
    
    if(particulas.size() < qtdPorSegundo*qtdSegundos) {
        cout << particulas.size() << " < "<<qtdPorSegundo << "*" << qtdSegundos << "\n";
        particulas.push_back( new Particula(-30 , ofRandom(0, 475) )); 
    }

    if( gui->kinectGlobal.isConnected() ) {
        gui->kinectGlobal.update();
        pixelsKinect = gui->kinectGlobal.getDepthPixels();
    }

    for( int i = 0; i < particulas.size(); i++ ) {
        particulas[i]->update(gui->dt, gui->aceleracao);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if( gui->kinectGlobal.isConnected() ) {
        gui->kinectGlobal.drawDepth( 20, 20, 400, 300);
    }
    for( int i = 0; i < particulas.size(); i++ ) {
        particulas[i]->draw();
    }
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
