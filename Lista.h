#ifndef LISTA_H
#define LISTA_H
#include "Aluno.h"

struct No {
    Aluno aluno;
    No* proximo;
    No(Aluno a) : aluno(a), proximo(nullptr) {}
};

// Lista encadeada simples (estrutura classica). Serve de baseline nos
// benchmarks (busca O(n)) e hospeda as operacoes adicionais do criterio 2.
class Lista {
private:
    No* cabeca;
    int tam;
public:
    Lista();
    ~Lista();
    void inserir(Aluno aluno);
    Aluno* buscar(int ra);
    bool remover(int ra);
    bool vazia();
    void mostrar();
    int quantidade();
    long long memoriaUsada();

    // --- TRES OPERACOES ADICIONAIS (criterio 2) ---
    float calcularMediaGeral();              // estatistica: media
    float calcularDesvioPadrao();            // estatistica: desvio padrao
    void filtrarAprovados(float notaMinima); // filtragem
    Aluno encontrarMaiorNota();              // classificacao
    void imprimirHistograma();               // distribuicao das notas
};
#endif
