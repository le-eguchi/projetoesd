#ifndef SKIPLIST_H
#define SKIPLIST_H
#include "Aluno.h"

static const int SKIP_MAX_NIVEL = 16;

// No da Skip List com array C de ponteiros (substitui std::vector - sem STL)
struct NoSkip {
    Aluno aluno;
    NoSkip* prox[SKIP_MAX_NIVEL]; // ponteiros para cada nivel
    int nivel;
    NoSkip(Aluno a, int niv) : aluno(a), nivel(niv) {
        for (int i = 0; i < SKIP_MAX_NIVEL; i++) prox[i] = nullptr;
    }
};

// Skip List probabilistica (estrutura fora da ementa). Busca O(log n) esperada,
// sem rotacoes. Niveis sorteados por probabilidade. Chave: RA do aluno.
class SkipList {
private:
    NoSkip* cabeca;
    int nivelAtual;
    int qtd;
    int gerarNivelAleatorio();

public:
    SkipList();
    ~SkipList();
    void inserir(Aluno a);
    Aluno* buscar(int ra);
    bool remover(int ra);          // [CRUD] remocao - criterio 1
    int quantidade() { return qtd; }
    int nivel() { return nivelAtual; }
    void mostrarNiveis();          // visualizacao da estrutura interna
    long long memoriaUsada();      // benchmark
};
#endif
