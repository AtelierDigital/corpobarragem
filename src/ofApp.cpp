#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0, 0, 0); 
    shaderAgua.load("../data/shaders/vertexdummy.c","../data/shaders/reflexosAgua.c");
    grayImage.allocate(WKINECT,HKINECT);
    fboColisao.allocate(WKINECT, HKINECT);
    if( !gui->kinectGlobal.isConnected() ) {
    gui->kinectGlobal.setRegistration(true);
        gui->kinectGlobal.init();
        gui->kinectGlobal.open();
    gui->kinectGlobal.setCameraTiltAngle(0);
    }
    fboParticulas.allocate(WSCREEN,HSCREEN);
    imgColisao.allocate(WKINECT, HKINECT, OF_IMAGE_COLOR);
    grayColisao.allocate(WKINECT, HKINECT);
    t1 = ofGetElapsedTimef();
    t0 = t1;

    emissores.push_back( new EmissorParticulas(0, 200, ofColor(200,250,255), 0, 20) );
    emissores.push_back( new EmissorParticulas(0, 210, ofColor(180,200,255), 1, 20) );
    emissores.push_back( new EmissorParticulas(0, 215, ofColor(150,200,255), 1.5, 20) );
    emissores.push_back( new EmissorParticulas(0, 180, ofColor(190,255,255), 2, 20) );
    emissores.push_back( new EmissorParticulas(0, 185, ofColor(100,185,255), 2.7, 20) );
    emissores.push_back( new EmissorParticulas(0, 190, ofColor(50,90,155), 3, 20) );
    emissores.push_back( new EmissorParticulas(0, 220, ofColor(90,205,255), 1, 25) );
    
    emissores.push_back( new EmissorParticulas(0, 200, ofColor(255,250,160), 19, 30) );
    emissores.push_back( new EmissorParticulas(0, 50, ofColor(195,190,255), 19, 30) );
    emissores.push_back( new EmissorParticulas(0, 100, ofColor(195,195,255), 19.9, 30) );
    emissores.push_back( new EmissorParticulas(0, 150, ofColor(195,190,255), 20, 30) );
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(255,220,150), 18, 30) );
    emissores.push_back( new EmissorParticulas(0, 350, ofColor(255,220,150), 19, 30) );
    emissores.push_back( new EmissorParticulas(0, 430, ofColor(255,250,250), 19, 30) );
    
    emissores.push_back( new EmissorParticulas(0, 150, ofColor(255,250,250), 42, 30) );
    emissores.push_back( new EmissorParticulas(0, 200, ofColor(255,250,255), 43, 30) );
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(235,250,250), 44, 30) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(255,220,255), 45, 30) );
    emissores.push_back( new EmissorParticulas(0, 350, ofColor(255,250,220), 46, 30) );
    emissores.push_back( new EmissorParticulas(0, 450, ofColor(255,250,255), 47, 30) );
    
    emissores.push_back( new EmissorParticulas(0, 150, ofColor(255,240,255), 62, 30) );
    emissores.push_back( new EmissorParticulas(0, 160, ofColor(255,240,255), 63, 30) );
    emissores.push_back( new EmissorParticulas(0, 170, ofColor(240,240,255), 64, 30) );
    emissores.push_back( new EmissorParticulas(0, 200, ofColor(255,250,255), 66, 30) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(250,255,255), 68, 30) );
    emissores.push_back( new EmissorParticulas(0, 400, ofColor(250,255,255), 72, 30) );
    emissores.push_back( new EmissorParticulas(0, 100, ofColor(255,255,200), 72, 30) );
    emissores.push_back( new EmissorParticulas(0, 120, ofColor(255,235,200), 73, 30) );
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(255,255,200), 75, 30) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(255,255,200), 76, 30) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(255,255,250), 76, 30) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(255,255,250), 76, 30) );
    
    emissores.push_back( new EmissorParticulas(0, 200, ofColor(200,250,255), 84, 20) );
    emissores.push_back( new EmissorParticulas(0, 210, ofColor(180,200,255), 84.5, 20) );
    emissores.push_back( new EmissorParticulas(0, 215, ofColor(150,200,255), 85, 20) );
    emissores.push_back( new EmissorParticulas(0, 180, ofColor(190,255,255), 85.2, 20) );
    emissores.push_back( new EmissorParticulas(0, 185, ofColor(100,185,255), 85.4, 20) );
    emissores.push_back( new EmissorParticulas(0, 190, ofColor(50,90,155), 86, 20) );

    emissores.push_back( new EmissorParticulas(0, 230, ofColor(150,190,255), 98, 20) );
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(255,190,155), 98, 20) );

    emissores.push_back( new EmissorParticulas(0, 190, ofColor(250,190,115), 116, 20) );
    emissores.push_back( new EmissorParticulas(0, 230, ofColor(250,250,255), 116, 20) );
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(255,190,155), 116, 20) );
    emissores.push_back( new EmissorParticulas(0, 290, ofColor(255,10,20), 116, 20) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(255,190,110), 116, 20) );

    emissores.push_back( new EmissorParticulas(0, 380, ofColor(200,230,255), 132, 20) );
    emissores.push_back( new EmissorParticulas(0, 180, ofColor(250,230,155), 132, 20) );
    emissores.push_back( new EmissorParticulas(0, 220, ofColor(250,230,155), 134, 20) );
    emissores.push_back( new EmissorParticulas(0, 100, ofColor(200,230,255), 136, 20) );
    emissores.push_back( new EmissorParticulas(0, 400, ofColor(255,250,255), 138, 20) );

    emissores.push_back( new EmissorParticulas(0, 200, ofColor(255,255,255), 166, 20) );
    emissores.push_back( new EmissorParticulas(0, 210, ofColor(250,250,250), 166, 20) );
    emissores.push_back( new EmissorParticulas(0, 205, ofColor(255,255,255), 166, 20) );
    emissores.push_back( new EmissorParticulas(0, 220, ofColor(252,252,252), 166, 20) );
    emissores.push_back( new EmissorParticulas(0, 300, ofColor(255,255,255), 166, 20) );
    emissores.push_back( new EmissorParticulas(0, 250, ofColor(255,255,255), 173, 20) );


    emissores.push_back( new EmissorParticulas(0, 30, ofColor(255,255,255), 220, 20) );
    emissores.push_back( new EmissorParticulas(0, 80, ofColor(190,250,255), 220, 20) );
    emissores.push_back( new EmissorParticulas(0, 255, ofColor(255,245,185), 220, 20) );
    emissores.push_back( new EmissorParticulas(0, 290, ofColor(255,245,185), 220, 20) );
    emissores.push_back( new EmissorParticulas(0, 310, ofColor(252,252,252), 220, 20) );
    emissores.push_back( new EmissorParticulas(0, 350, ofColor(200,245,255), 220, 20) );

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
        ofFill();
    }
        
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        fboColisao.begin();
        ofClear(0,0,0);
        ofSetColor(255,255,255,255);
        ofFill();
        grayImage.mirror(true, true);
        grayImage.rotate(270, 320, 240);
        grayImage.draw(-170,0,900, 500);
        fboParticulas.draw(0,0,WKINECT,HKINECT); 
        fboColisao.end();
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        
        fboColisao.readToPixels(pixelsTemp);
        imgColisao = pixelsTemp;
        imgColisao.setImageType(OF_IMAGE_GRAYSCALE);
        grayColisao = imgColisao;
        pixelsColisao = grayColisao.getPixels();
        
        
    if( gui->kinectGlobal.isConnected() ) {
        gui->kinectGlobal.setDepthClipping(gui->nearThreshold_Kinect, gui->farThreshold_Kinect);
        
        this->kinDepthAnalysis.centroid.set(-1.0f, -1.0f, -1.0f);
        this->kinDepthAnalysis.rectCoverage.set(-1.0f, -1.0f, -1.0f, -1.0f);
        this->kinDepthAnalysis.totalBlobsArea = 0.0f;
       
        if(gui->kinectGlobal.isFrameNew()) {
           sendOSC();
        }
         
    }

    fboParticulas.begin();
    /*ofSetColor(0,0,0,50);
    ofFill();
    ofDrawRectangle(0,0, WSCREEN, HSCREEN);*/
    ofClear(0,0,0);
    float tVideo = video->videoPlayer.getPosition()*video->videoPlayer.getDuration();
    
    for( int i = 0; i < emissores.size(); i++ ) {
        // Limpa as particulas e reseta o emissor quando 
        // ja tiver passado mais de 2 minutos
        if(tVideo > emissores[i]->tInicio+120 && emissores[i]->particulas.size() > 0) {
            cout << "limpa o ["<<i<<"]\n";
            emissores[i]->particulas.clear();
            emissores[i]->qtdSegundos = 0;
        }

        if(tVideo > emissores[i]->tInicio && emissores[i]->tInicio+120 > tVideo) {
            emissores[i]->update(pixelsColisao,dt);
            emissores[i]->draw();
        }
    }
    fboParticulas.end();

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

//    ofFill();
//    ofDrawRectangle(120,HSCREEN/2-100, 200, 200);
//    ofDrawRectangle(620,HSCREEN/2-100, 200, 200);
    shaderAgua.begin();
    shaderAgua.setUniform1f("time", t1);
    

        ofSetColor(255,255,255,255);
    fboParticulas.draw(0,0);
    shaderAgua.end();	
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
