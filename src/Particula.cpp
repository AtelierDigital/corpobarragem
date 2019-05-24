#include "Particula.h"

Particula::Particula(float x, float y) {
    pos.set(x, y);
    velocidade.set(0, 0);
    cor.set(255,220,255,255);
    cor.setBrightness(100);
}

void Particula::update(float dt, ofVec2f aceleracao,ofPixels pixelsKinect) {
    velocidade+= aceleracao * dt;
    pos += velocidade * dt;
    if ( pos.x > HKINECT ) {
        pos.x = HKINECT;
        // mata
    }
    cor.setHue( cor.getHue() + dt*100 );

    if(!pixelsKinect.isAllocated()) {
        return;
    }

    // Colisão simple com 8 pontos
    int raioColisao = 5;
    for(float rad = 0; rad < TWO_PI; rad += TWO_PI/8) {
        ofVec2f vetorColisao(cos(rad), sin(rad));
        ofVec2f pontoColisao = vetorColisao * raioColisao;
        pontoColisao += pos;
        float pixelValue = 0;
        int xk = int(pontoColisao.x);
        int yk = int(pontoColisao.y);
        if(xk < WKINECT && yk < HKINECT && xk>0 && yk>0 ) {
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

