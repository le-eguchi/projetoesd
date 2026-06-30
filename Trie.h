#ifndef TRIE_H
#define TRIE_H
#include <string>
using namespace std;

// No da Trie com filhos em LISTA ENCADEADA manual (sem std::map).
// Cada no guarda apenas os filhos que existem, encadeados. A busca de um
// caractere percorre a lista -> O(k) por caractere, onde k = filhos do no.
struct NoFilho;
struct NoTrie {
    NoFilho* filhos;  // lista encadeada de filhos
    bool fim;
    NoTrie() : filhos(nullptr), fim(false) {}
};
struct NoFilho {
    char c;
    NoTrie* no;
    NoFilho* proximo;
    NoFilho(char ch) : c(ch), no(new NoTrie()), proximo(nullptr) {}
};

// Trie (arvore de prefixos) com filhos encadeados - versao NAO otimizada.
// Usada para comparar com a TrieOptimizada (criterio 7).
class Trie {
private:
    NoTrie* raiz;
    void destruir(NoTrie* no);
    NoTrie* acharFilho(NoTrie* no, char c);

public:
    Trie();
    ~Trie();
    void inserir(string palavra);
    bool buscar(string palavra);
    void buscarPrefixo(string prefixo);
};
#endif
