#include "TrieOptimizada.h"
#include <iostream>

using namespace std;

TrieOptimizada::TrieOptimizada() { 
    raiz = new NoTrieOptimizada(); 
}

TrieOptimizada::~TrieOptimizada() { 
    destruir(raiz); 
}

void TrieOptimizada::destruir(NoTrieOptimizada* no) {
    if (!no) return;
    for (int i = 0; i < 128; i++) {
        if (no->filhos[i] != nullptr) {
            destruir(no->filhos[i]);
        }
    }
    delete no;
}

void TrieOptimizada::inserir(string palavra) {
    NoTrieOptimizada* atual = raiz;
    for (char c : palavra) {
        int indice = (int)c;
        // Ignora caracteres fora do padrão ASCII básico
        if (indice < 0 || indice >= 128) continue; 
        
        if (atual->filhos[indice] == nullptr) {
            atual->filhos[indice] = new NoTrieOptimizada();
        }
        atual = atual->filhos[indice];
    }
    atual->fim = true;
}

bool TrieOptimizada::buscar(string palavra) {
    NoTrieOptimizada* atual = raiz;
    for (char c : palavra) {
        int indice = (int)c;
        if (indice < 0 || indice >= 128 || atual->filhos[indice] == nullptr) {
            return false;
        }
        atual = atual->filhos[indice];
    }
    return atual->fim;
}

void TrieOptimizada::buscarPrefixo(string prefixo) {
    NoTrieOptimizada* atual = raiz;
    for (char c : prefixo) {
        int indice = (int)c;
        if (indice < 0 || indice >= 128 || atual->filhos[indice] == nullptr) {
            cout << "Nenhum resultado para o prefixo.\n"; 
            return;
        }
        atual = atual->filhos[indice];
    }
    cout << "O prefixo '" << prefixo << "' existe no sistema (Trie Optimizada).\n";
}