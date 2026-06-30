#ifndef BENCHMARK_H
#define BENCHMARK_H
#include <string>
#include "AVL.h"
#include "Hash.h"
#include "Lista.h"
#include "SkipList.h"
#include "Trie.h"
#include "TrieOptimizada.h"
#include "Gerador.h"

// Modulo de medicao empirica padronizada (criterios 8 e 9).
// Todos os tempos sao medidos com chrono em nanossegundos. Diferente da versao
// anterior, NAO usa sleep cosmetico: cada restricao produz uma medicao real.
class Benchmark {
public:
    // Benchmark completo: insercao, busca, remocao, memoria, colisoes (criterio 9)
    static void completo(Aluno* dados, int n, int* rasBusca, int qtdBusca);

    // Comparacao da estrutura otimizada vs original (criterio 7)
    static void compararTries(Aluno* dados, int n, string* nomesBusca, int qtdBusca);

    // Escalabilidade: tempos com N crescente (criterio 9)
    static void escalabilidade(Gerador& ger);

    // Cinco testes em condicoes restritivas, todos medidos (criterio 8)
    static void testesRestritivos(Aluno* dados, int n);
};
#endif
