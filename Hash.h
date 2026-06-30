#ifndef HASH_H
#define HASH_H
#include "Aluno.h"

// No de encadeamento manual (substitui std::list - sem STL na colecao)
struct NoHash {
    Aluno aluno;
    NoHash* proximo;
    NoHash(Aluno a) : aluno(a), proximo(nullptr) {}
};

// Tabela Hash com encadeamento separado implementado do zero.
// Chave: RA do aluno. Trata colisoes encadeando nos manualmente.
class Hash {
private:
    static const int TAM = 1009;   // primo reduz colisoes
    NoHash* tabela[TAM];           // vetor de listas encadeadas manuais
    int colisoes;
    int qtd;

    int funcaoHash(int ra);

public:
    Hash();
    ~Hash();
    void inserir(Aluno a);
    Aluno* buscar(int ra);
    bool remover(int ra);          // [CRUD] remocao - criterio 1
    void mostrar();
    int getColisoes() { return colisoes; }
    int quantidade() { return qtd; }
    int capacidade() { return TAM; }
    long long memoriaUsada();      // benchmark
};
#endif
