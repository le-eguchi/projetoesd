#include "Hash.h"
#include <iostream>
using namespace std;

Hash::Hash() : colisoes(0), qtd(0) {
    for (int i = 0; i < TAM; i++) tabela[i] = nullptr;
}

Hash::~Hash() {
    for (int i = 0; i < TAM; i++) {
        NoHash* atual = tabela[i];
        while (atual) { NoHash* prox = atual->proximo; delete atual; atual = prox; }
    }
}

int Hash::funcaoHash(int ra) {
    int r = ra % TAM;
    if (r < 0) r += TAM;
    return r;
}

// Insere no inicio da lista encadeada do bucket. Conta colisao se bucket ocupado.
void Hash::inserir(Aluno aluno) {
    int pos = funcaoHash(aluno.getRA());
    if (tabela[pos] != nullptr) colisoes++;
    NoHash* novo = new NoHash(aluno);
    novo->proximo = tabela[pos];
    tabela[pos] = novo;
    qtd++;
}

Aluno* Hash::buscar(int ra) {
    int pos = funcaoHash(ra);
    NoHash* atual = tabela[pos];
    while (atual) {
        if (atual->aluno.getRA() == ra) return &atual->aluno;
        atual = atual->proximo;
    }
    return nullptr;
}

// [CRUD] Remove o no do bucket reencadeando os ponteiros manualmente
bool Hash::remover(int ra) {
    int pos = funcaoHash(ra);
    NoHash* atual = tabela[pos];
    NoHash* ant = nullptr;
    while (atual) {
        if (atual->aluno.getRA() == ra) {
            if (ant) ant->proximo = atual->proximo;
            else tabela[pos] = atual->proximo;
            delete atual;
            qtd--;
            return true;
        }
        ant = atual;
        atual = atual->proximo;
    }
    return false;
}

void Hash::mostrar() {
    for (int i = 0; i < TAM; i++)
        for (NoHash* n = tabela[i]; n; n = n->proximo) n->aluno.mostrar();
}

long long Hash::memoriaUsada() {
    return (long long)TAM * sizeof(NoHash*) + (long long)qtd * sizeof(NoHash);
}
