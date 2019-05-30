#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0); 
    grayImage.allocate(640,480);
    t1 = ofGetElapsedTimef();
    t0 = t1;

    emissores.push_back( new EmissorParticulas(0, 100, ofColor(255,0,0)) );
    emissores.push_back( new EmissorParticulas(0, 200, ofColor(255,0,255)) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(0,0,255)) );
    emissores.push_back( new EmissorParticulas(0, 400, ofColor(0,255,255)) );
}

//--------------------------------------------------------------
void ofApp::update(){

    t0 = t1;
    t1 = ofGetElapsedTimef();
    dt = t1 - t0; //tempo desde o ultimo update
    // Carrega os pixels do kinect
    if( gui->kinectGlobal.isConnected() ) {
        gui->kinectGlobal.update();
        grayImage.setFromPixels(gui->kinectGlobal.getDepthPixels());
        grayImage.brightnessContrast(gui->brilhoKinect, gui->contrasteKinect);
        grayImage.blur(gui->blurKinect*2+1);
        pixelsColisao = grayImage.getPixels();
    }

    for( int i = 0; i < emissores.size(); i++ ) {
        emissores[i]->update(pixelsColisao,dt);
    }

}

//--------------------------------------------------------------
void ofApp::draw(){

    // Desenha img do kinect para debug
    if( gui->kinectGlobal.isConnected() ) {
        grayImage.draw( 20, 20, 400, 300);
    }

    // Desenha particulas
    for( int i = 0; i < emissores.size(); i++ ) {
        emissores[i]->draw();
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
