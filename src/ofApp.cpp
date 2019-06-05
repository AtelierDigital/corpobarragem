#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0, 0, 0); 
    grayImage.allocate(WKINECT,HKINECT);
    fboColisao.allocate(WKINECT, HKINECT);
    imgColisao.allocate(WKINECT, HKINECT, OF_IMAGE_COLOR);
    grayColisao.allocate(WKINECT, HKINECT);
    t1 = ofGetElapsedTimef();
    t0 = t1;

    emissores.push_back( new EmissorParticulas(0, 200, ofColor(100,150,255), 0, 20) );
    emissores.push_back( new EmissorParticulas(0, 210, ofColor(100,160,255), 1, 20) );
    emissores.push_back( new EmissorParticulas(0, 215, ofColor(100,160,255), 1.5, 20) );
    emissores.push_back( new EmissorParticulas(0, 180, ofColor(100,55,205), 2, 20) );
    emissores.push_back( new EmissorParticulas(0, 185, ofColor(100,185,255), 2.7, 20) );
    emissores.push_back( new EmissorParticulas(0, 190, ofColor(50,90,155), 3, 20) );
    emissores.push_back( new EmissorParticulas(0, 220, ofColor(20,105,255), 1, 25) );
    
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(255,250,60), 19, 30) );
    emissores.push_back( new EmissorParticulas(0, 400, ofColor(155,150,255), 19, 30) );
    emissores.push_back( new EmissorParticulas(0, 350, ofColor(155,155,255), 19.9, 30) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(155,150,255), 20, 30) );
    emissores.push_back( new EmissorParticulas(0, 200, ofColor(255,190,50), 18, 30) );
    emissores.push_back( new EmissorParticulas(0, 100, ofColor(255,190,50), 19, 30) );
    
    emissores.push_back( new EmissorParticulas(0, 400, ofColor(255,250,250), 42, 30) );
    emissores.push_back( new EmissorParticulas(0, 350, ofColor(255,250,255), 43, 30) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(235,250,250), 44, 30) );
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(255,220,255), 45, 30) );
    emissores.push_back( new EmissorParticulas(0, 200, ofColor(255,250,220), 46, 30) );
    emissores.push_back( new EmissorParticulas(0, 150, ofColor(255,250,255), 47, 30) );
    
    OSCRemoteAddress = "localhost";
    OSCRemotePort = 8084;
    if(!sender.setup(OSCRemoteAddress, OSCRemotePort)) {
        ofLogError("Failed to initialize ofxOscSender sender");
    }
    
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
        //grayImage.blurHeavily();
        grayImage.blur(gui->blurKinect*2+1);
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        fboColisao.begin();
        ofClear(0,0,0);
        ofSetColor(255,255,255,255);
        grayImage.mirror(true, true);
        grayImage.rotate(270, 320, 240);
        grayImage.draw(-170,0,900, 500);
        fboColisao.end();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        fboColisao.readToPixels(pixelsTemp);
        imgColisao = pixelsTemp;
        imgColisao.setImageType(OF_IMAGE_GRAYSCALE);
        grayColisao = imgColisao;
        pixelsColisao = grayColisao.getPixels();
        
        
        gui->kinectGlobal.setDepthClipping(gui->nearThreshold_Kinect, gui->farThreshold_Kinect);
        
        this->kinDepthAnalysis.centroid.set(-1.0f, -1.0f, -1.0f);
        this->kinDepthAnalysis.rectCoverage.set(-1.0f, -1.0f, -1.0f, -1.0f);
        this->kinDepthAnalysis.totalBlobsArea = 0.0f;
       
        if(gui->kinectGlobal.isFrameNew()) {
           sendOSC();
        }
         
    }

    for( int i = 0; i < emissores.size(); i++ ) {
        if(t1 > emissores[i]->tInicio &&
           emissores[i]->tInicio+emissores[i]->tempoVidaMax+50 > t1) {
            emissores[i]->update(pixelsColisao,dt);
        }
    }

}

void ofApp::sendOSC() {
    // Lendo e espelhando a depth image do kinect
    //grayImage.setFromPixels(gui->kinectGlobal.getDepthPixels());
    //grayImage.mirror(false, true);
    
    grayImage.getCvImage();
    
    //ofLogNotice() << "count = " << grayImage.countNonZeroInRegion(0, 0, kinect.width, kinect.height);
    
    // Estou mantendo os valores intermediarios ao inves de satura-los (TODO - vamos saturar ou nao?)
    ofPixels & pix = grayImage.getPixels();
    int numPixels = pix.size();
    for(int i = 0; i < numPixels; i++) {
        if(pix[i] > gui->kinectGlobal.getFarClipping() || pix[i] < (gui->kinectGlobal.getNearClipping())) {
            //if(pix[i] > 230 || pix[i] < 70) {    //  hard-coding so para testes, usando o kinect bem perto de mim
            pix[i] = 0;
        }
        else
        {
            pix[i] *= 10.0f;
        }
    }
    
    //  Convertendo para ofImage
    mask.setFromPixels(grayImage.getPixels());
    mask.update();
    
    
    // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
    // also, find holes is set to true so we will get interior contours as well....
    float nblobs = (float)contourFinder.findContours(grayImage, 10, (gui->kinectGlobal.width*gui->kinectGlobal.height)/2, 10, false);
    
    if(nblobs > 0) {
        this->kinDepthAnalysis.rectCoverage   = contourFinder.blobs[0].boundingRect;
        this->kinDepthAnalysis.centroid       = contourFinder.blobs[0].centroid;
        this->kinDepthAnalysis.totalBlobsArea = contourFinder.blobs[0].area;
    }
    for(int i=0; i < nblobs; i++)
    {
        this->kinDepthAnalysis.centroid += contourFinder.blobs[i].centroid;
        this->kinDepthAnalysis.rectCoverage.growToInclude( contourFinder.blobs[i].boundingRect );
        this->kinDepthAnalysis.totalBlobsArea += contourFinder.blobs[i].area;
    }
    this->kinDepthAnalysis.centroid /= nblobs;
    
    //
    //  Convertando da escala das dimensoes da depth image do kinect para as dimensoes
    //da tela do nosso app
    
    this->kinDepthAnalysis.centroid.x = ofMap(this->kinDepthAnalysis.centroid.x, 0, gui->kinectGlobal.width, 0, ofGetWidth());
    this->kinDepthAnalysis.centroid.y = ofMap(this->kinDepthAnalysis.centroid.y, 0, gui->kinectGlobal.height, 0, ofGetHeight());
    this->kinDepthAnalysis.rectCoverage.x = ofMap(this->kinDepthAnalysis.rectCoverage.x, 0, gui->kinectGlobal.width, 0, ofGetWidth());
    this->kinDepthAnalysis.rectCoverage.y = ofMap(this->kinDepthAnalysis.rectCoverage.y, 0, gui->kinectGlobal.height, 0, ofGetHeight());
    this->kinDepthAnalysis.rectCoverage.width  = ofMap(this->kinDepthAnalysis.rectCoverage.width, 0, gui->kinectGlobal.width, 0, ofGetWidth());
    this->kinDepthAnalysis.rectCoverage.height = ofMap(this->kinDepthAnalysis.rectCoverage.height, 0, gui->kinectGlobal.height, 0, ofGetHeight());
    
    //ofLog() << "totalBlobsArea = " << this->kinDepthAnalysis.totalBlobsArea << std::endl;
    
    ofxOscMessage m;
    m.setAddress("/mix");
    m.addFloatArg(ofMap(this->kinDepthAnalysis.totalBlobsArea, 0, gui->kinectGlobal.width*gui->kinectGlobal.height/8., 0.f, 1.f, true));
    sender.sendMessage(m, false);
}

//--------------------------------------------------------------
void ofApp::draw(){

    // Desenha img do kinect para debug
    if( gui->kinectGlobal.isConnected() ) {
        ofSetColor(255,255,255,255);
        //imgColisao.draw( 0, 0, WSCREEN, HSCREEN);
    }

    // Desenha particulas
    for( int i = 0; i < emissores.size(); i++ ) {
        if(t1 > emissores[i]->tInicio) {
            	emissores[i]->draw();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    cout << "positon:" << video->videoPlayer.getPosition()*video->videoPlayer.getDuration() << " t1:"<<t1<<"\n";
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
