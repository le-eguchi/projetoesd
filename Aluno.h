#ifndef ALUNO_H
#define ALUNO_H
#include <string>
using namespace std;

// Representa um aluno no sistema de gestao academica.
// Campos: RA (chave), nome, media (nota), e frequencia (% presenca).
// A media e a frequencia sao alvos de tratamento de dados (criterio 4).
class Aluno {
private:
    int ra;
    string nome;
    float media;
    float frequencia;   // percentual de presenca (0-100)
public:
    Aluno();
    Aluno(int ra, string nome, float media);
    Aluno(int ra, string nome, float media, float frequencia);
    int getRA() const;
    string getNome() const;
    float getMedia() const;
    float getFrequencia() const;
    void setMedia(float m);
    void setFrequencia(float f);
    void mostrar() const;
};
#endif
