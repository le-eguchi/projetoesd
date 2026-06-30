#ifndef GERADOR_H
#define GERADOR_H
#include "Aluno.h"
#include <random>

// Gera dados sinteticos de alunos com variabilidade probabilistica real.
// Aplica RUIDO GAUSSIANO (distribuicao normal) sobre a media e a frequencia,
// simulando a flutuacao natural de notas - tecnica de data augmentation
// exigida pelo criterio 4 do projeto.
class Gerador {
private:
    std::mt19937 motor;
    std::normal_distribution<float> distMedia;      // notas ~ N(6.0, 2.0)
    std::normal_distribution<float> distFrequencia; // freq ~ N(85, 15)
public:
    Gerador(unsigned int seed);
    Aluno gerarAluno(int ra);
    float ruidoGaussiano(float valor, float desvio); // injeta ruido pontual
};
#endif
