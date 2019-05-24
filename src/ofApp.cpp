#include "ofApp.h"


int qtdPorSegundo = 7;

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0); 
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float qtdSegundos = ofGetElapsedTimef()/1;
    
    // Adiciona partículas conforme o tempo passa
    if(gui->particulas.size() < qtdPorSegundo*qtdSegundos) {
        gui->particulas.push_back( new Particula(-30 , ofRandom(0, 475) )); 
    }

    // Carrega os pixels do kinect
    if( gui->kinectGlobal.isConnected() ) {
        gui->kinectGlobal.update();
        pixelsKinect = gui->kinectGlobal.getDepthPixels();
    }

    // Atualiza as partículas
    for( int i = 0; i < gui->particulas.size(); i++ ) {
        gui->particulas[i]->update(gui->dt, gui->aceleracao, pixelsKinect);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Desenha img do kinect para debug
    if( gui->kinectGlobal.isConnected() ) {
        gui->kinectGlobal.drawDepth( 20, 20, 400, 300);
    }

    // Desenha particulas
    for( int i = 0; i < gui->particulas.size(); i++ ) {
        gui->particulas[i]->draw();
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
