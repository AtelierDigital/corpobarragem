#include "EmissorParticulas.h"


EmissorParticulas::EmissorParticulas(float x, float y, ofColor corEmissor) {
    pos.set(x, y);
    qtdPorSegundo = 7;
    qtdMaxParticulas = 200;
    aceleracao = ofVec2f(1,0);
    qtdSegundos = 0;

    cor.set(corEmissor);
}

void EmissorParticulas::update(ofPixels &pixelsColisao, float dt) {
    if(dt < 0) {
        return;
    }
    aceleracao.y = sin(qtdSegundos);
    qtdSegundos += dt;
    // Adiciona partículas conforme o tempo passa
    int qtdParticulas = particulas.size();
    if(qtdParticulas < qtdPorSegundo*qtdSegundos && qtdParticulas < qtdMaxParticulas) {
        particulas.push_back( new Particula(pos.x, ofRandom(pos.y-10, pos.y+10), cor )); 
    }

    // Atualiza as partículas
    for( int i = 0; i < particulas.size(); i++ ) {
        particulas[i]->update(dt, aceleracao, pixelsColisao);
    }
}

void EmissorParticulas::draw() {
    for( int i = 0; i < particulas.size(); i++ ) {
        particulas[i]->draw();
    }
 }
