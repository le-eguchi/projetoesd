#include "Aluno.h"
#include <iostream>
#include <iomanip>

Aluno::Aluno() : ra(0), nome(""), media(0.0), frequencia(0.0) {}
Aluno::Aluno(int ra, string nome, float media)
    : ra(ra), nome(nome), media(media), frequencia(100.0) {}
Aluno::Aluno(int ra, string nome, float media, float frequencia)
    : ra(ra), nome(nome), media(media), frequencia(frequencia) {}

int Aluno::getRA() const { return ra; }
string Aluno::getNome() const { return nome; }
float Aluno::getMedia() const { return media; }
float Aluno::getFrequencia() const { return frequencia; }
void Aluno::setMedia(float m) { media = m; }
void Aluno::setFrequencia(float f) { frequencia = f; }

void Aluno::mostrar() const {
    std::cout << "RA: " << ra << " | Nome: " << nome
              << " | Media: " << std::fixed << std::setprecision(2) << media
              << " | Freq: " << std::fixed << std::setprecision(1) << frequencia << "%"
              << std::endl;
}
