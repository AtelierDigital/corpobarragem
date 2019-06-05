#include "EmissorParticulas.h"


EmissorParticulas::EmissorParticulas(float x, float y, ofColor corEmissor, float inicio, float vidaMax) {
    pos.set(x, y);
    
    tInicio = inicio;
    tempoVidaMax = vidaMax;
    qtdPorSegundo = 9;
    qtdMaxParticulas = 150;
    aceleracao = ofVec2f(2,0);
    qtdSegundos = 0;
    
    cor.set(corEmissor);
}

void EmissorParticulas::update(ofPixels &pixelsColisao, float dt) {
    if(dt < 0) {
        return;
    }
    aceleracao.y = sin(qtdSegundos) * ofRandom(0.8, 1.2);
    qtdSegundos += dt;
    // Adiciona partículas conforme o tempo passa
    int qtdParticulas = particulas.size();
    if(qtdParticulas < qtdPorSegundo*qtdSegundos && qtdParticulas < qtdMaxParticulas) {
        particulas.push_back( new Particula(pos.x, ofRandom(pos.y-30, pos.y+30), cor ));
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
