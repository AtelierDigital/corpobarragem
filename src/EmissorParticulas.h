#pragma once

#include "Particula.h"

class EmissorParticulas {
    public:
        EmissorParticulas(float x,float y, ofColor corEmissor, float tInicio, float tempoVidaMax);
        int qtdPorSegundo;
        int qtdMaxParticulas;
        vector<Particula*> particulas;
        ofVec2f pos;
        ofVec2f aceleracao;
        ofColor cor;
    
        float tempoVidaMax;
        float tInicio;
        float qtdSegundos;
        void update(ofPixels &pixelsColisao, float dt);
        void draw();
};
