#ifndef TRIE_OPTIMIZADA_H
#define TRIE_OPTIMIZADA_H
#include <string>

using namespace std;

struct NoTrieOptimizada {
    NoTrieOptimizada* filhos[128]; // Mapeamento direto da tabela ASCII para acesso O(1)
    bool fim;
    
    NoTrieOptimizada() {
        fim = false;
        for (int i = 0; i < 128; i++) {
            filhos[i] = nullptr;
        }
    }
};

class TrieOptimizada {
private:
    NoTrieOptimizada* raiz;
    void destruir(NoTrieOptimizada* no);
public:
    TrieOptimizada();
    ~TrieOptimizada();
    void inserir(string palavra);
    bool buscar(string palavra);
    void buscarPrefixo(string prefixo);
};
#endif