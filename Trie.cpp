#include "Trie.h"
#include <iostream>
using namespace std;

Trie::Trie() { raiz = new NoTrie(); }
Trie::~Trie() { destruir(raiz); }

void Trie::destruir(NoTrie* no) {
    if (!no) return;
    NoFilho* f = no->filhos;
    while (f) {
        NoFilho* prox = f->proximo;
        destruir(f->no);
        delete f;
        f = prox;
    }
    delete no;
}

// Procura um filho percorrendo a lista encadeada - O(numero de filhos)
NoTrie* Trie::acharFilho(NoTrie* no, char c) {
    for (NoFilho* f = no->filhos; f; f = f->proximo)
        if (f->c == c) return f->no;
    return nullptr;
}

void Trie::inserir(string palavra) {
    NoTrie* atual = raiz;
    for (char c : palavra) {
        NoTrie* filho = acharFilho(atual, c);
        if (!filho) {
            NoFilho* novo = new NoFilho(c);
            novo->proximo = atual->filhos;
            atual->filhos = novo;
            filho = novo->no;
        }
        atual = filho;
    }
    atual->fim = true;
}

bool Trie::buscar(string palavra) {
    NoTrie* atual = raiz;
    for (char c : palavra) {
        atual = acharFilho(atual, c);
        if (!atual) return false;
    }
    return atual->fim;
}

void Trie::buscarPrefixo(string prefixo) {
    NoTrie* atual = raiz;
    for (char c : prefixo) {
        atual = acharFilho(atual, c);
        if (!atual) { cout << "Nenhum resultado.\n"; return; }
    }
    cout << "O prefixo '" << prefixo << "' existe no sistema.\n";
}
