#ifndef AVL_H
#define AVL_H
#include "Aluno.h"

struct NoAVL {
    Aluno aluno;
    NoAVL *esquerda, *direita;
    int altura;
    NoAVL(Aluno a) : aluno(a), esquerda(nullptr), direita(nullptr), altura(1) {}
};

// Arvore AVL - estrutura classica auto-balanceada (sem STL na colecao).
// Chave de ordenacao: RA do aluno. Garante busca/insercao/remocao em O(log n).
class AVL {
private:
    NoAVL* raiz;
    int qtd;              // contador de nos para benchmark
    int limiteMax;        // -1 = ilimitado; usado na restricao R2

    int h(NoAVL* n) { return n ? n->altura : 0; }
    int fator(NoAVL* n) { return n ? h(n->esquerda) - h(n->direita) : 0; }
    int maxInt(int a, int b) { return (a > b) ? a : b; }

    NoAVL* rotD(NoAVL* y);
    NoAVL* rotE(NoAVL* x);
    NoAVL* balancear(NoAVL* no);
    NoAVL* inserir(NoAVL* no, Aluno a, bool& inseriu);
    NoAVL* menorNo(NoAVL* no);
    NoAVL* remover(NoAVL* no, int ra, bool& removeu);
    NoAVL* buscar(NoAVL* no, int ra);
    void destruir(NoAVL* no);
    int contar(NoAVL* no);

public:
    AVL();
    ~AVL();
    void inserir(Aluno a);
    bool remover(int ra);          // [CRUD] remocao - criterio 1
    Aluno* buscar(int ra);
    int quantidade();              // tamanho atual
    int altura();                  // altura da arvore (para analise)
    void setLimite(int max);       // restricao R2 (limite de memoria)
    long long memoriaUsada();      // bytes estimados - benchmark
};
#endif
