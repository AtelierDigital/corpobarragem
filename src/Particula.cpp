#include "Particula.h"

Particula::Particula(float x, float y, ofColor corEmissor) {
    pos.set(x, y);
    velocidade.set(0, 0);
    cor.set(corEmissor);
    corOriginal.set(corEmissor);
    cor.setBrightness(0);
    cor.setSaturation(100);
    tempoVida = 0;
}

void Particula::update(float dt, ofVec2f aceleracao,ofPixels &pixelsKinect) {
    ofColor tempColor = cor;
    tempoVida += dt;
    velocidade+= aceleracao * dt;
    float brilho = cor.getBrightness();
    if(brilho < 120) {
        tempColor.setBrightness(tempoVida*5);
    }
    tempColor.setSaturation(corOriginal.getSaturation());
    tempColor.setHue(corOriginal.getHue());
    cor = tempColor;

    pos += velocidade * dt;
    if ( pos.x > WKINECT + 10) {
        pos.x = -20;
    }
    if(!pixelsKinect.isAllocated()) {
        return;
    }

    // Colisão simples com 8 pontos
    int raioColisao = 5;
    for(float rad = 0; rad < TWO_PI; rad += TWO_PI/8) {
        ofVec2f vetorColisao(cos(rad), sin(rad));
        ofVec2f pontoColisao = vetorColisao * raioColisao;
        pontoColisao += pos;
        float pixelValue = 0;
        int xk = int(pontoColisao.x);
        int yk = int(pontoColisao.y);
        if(xk < WKINECT && yk < HKINECT && xk>0 && yk>0 ) {
            pixelValue = pixelsKinect[ yk*WKINECT + xk];
        }
        if(pixelValue > 180) {
            pos -= vetorColisao;
        }
    }
}

void Particula::draw() {
    ofSetColor(cor);
    
    // A particula vive no limite das medida do kinect
    // mas é desenhada de acordo com o tamanho da tela
    ofDrawCircle( (pos.x/HKINECT)*HSCREEN, (pos.y/WKINECT)*WSCREEN, 2);
}

