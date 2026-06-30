#include "SkipList.h"
#include <cstdlib>
#include <iostream>
using namespace std;

SkipList::SkipList() : nivelAtual(0), qtd(0) {
    Aluno d;
    cabeca = new NoSkip(d, SKIP_MAX_NIVEL - 1);
}

SkipList::~SkipList() {
    NoSkip* atual = cabeca;
    while (atual) {
        NoSkip* prox = atual->prox[0];
        delete atual;
        atual = prox;
    }
}

// Sorteia nivel: cada nivel extra tem 50% de chance (distribuicao geometrica)
int SkipList::gerarNivelAleatorio() {
    int niv = 0;
    while ((rand() % 2) == 0 && niv < SKIP_MAX_NIVEL - 1) niv++;
    return niv;
}

void SkipList::inserir(Aluno a) {
    NoSkip* atualizar[SKIP_MAX_NIVEL];
    for (int i = 0; i < SKIP_MAX_NIVEL; i++) atualizar[i] = cabeca;

    NoSkip* atual = cabeca;
    for (int i = nivelAtual; i >= 0; i--) {
        while (atual->prox[i] && atual->prox[i]->aluno.getRA() < a.getRA())
            atual = atual->prox[i];
        atualizar[i] = atual;
    }

    int niv = gerarNivelAleatorio();
    if (niv > nivelAtual) {
        for (int i = nivelAtual + 1; i <= niv; i++) atualizar[i] = cabeca;
        nivelAtual = niv;
    }

    NoSkip* novo = new NoSkip(a, niv);
    for (int i = 0; i <= niv; i++) {
        novo->prox[i] = atualizar[i]->prox[i];
        atualizar[i]->prox[i] = novo;
    }
    qtd++;
}

Aluno* SkipList::buscar(int ra) {
    NoSkip* atual = cabeca;
    for (int i = nivelAtual; i >= 0; i--)
        while (atual->prox[i] && atual->prox[i]->aluno.getRA() < ra)
            atual = atual->prox[i];
    atual = atual->prox[0];
    if (atual && atual->aluno.getRA() == ra) return &atual->aluno;
    return nullptr;
}

// [CRUD] Remove reencadeando todos os niveis em que o no aparece
bool SkipList::remover(int ra) {
    NoSkip* atualizar[SKIP_MAX_NIVEL];
    for (int i = 0; i < SKIP_MAX_NIVEL; i++) atualizar[i] = cabeca;

    NoSkip* atual = cabeca;
    for (int i = nivelAtual; i >= 0; i--) {
        while (atual->prox[i] && atual->prox[i]->aluno.getRA() < ra)
            atual = atual->prox[i];
        atualizar[i] = atual;
    }
    atual = atual->prox[0];
    if (!atual || atual->aluno.getRA() != ra) return false;

    for (int i = 0; i <= nivelAtual; i++) {
        if (atualizar[i]->prox[i] != atual) break;
        atualizar[i]->prox[i] = atual->prox[i];
    }
    delete atual;
    while (nivelAtual > 0 && cabeca->prox[nivelAtual] == nullptr) nivelAtual--;
    qtd--;
    return true;
}

// Visualizacao: mostra quantos nos existem em cada nivel
void SkipList::mostrarNiveis() {
    cout << "\n--- Estrutura interna da Skip List ---\n";
    for (int i = nivelAtual; i >= 0; i--) {
        int cont = 0;
        for (NoSkip* n = cabeca->prox[i]; n; n = n->prox[i]) cont++;
        cout << "Nivel " << i << ": " << cont << " nos\n";
    }
    cout << "Nivel maximo atingido: " << nivelAtual << " | Total de nos: " << qtd << "\n";
}

long long SkipList::memoriaUsada() {
    return (long long)qtd * sizeof(NoSkip);
}
