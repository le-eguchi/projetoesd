#ifndef TRATAMENTODADOS_H
#define TRATAMENTODADOS_H
#include "Aluno.h"

// Rotinas de higienizacao e estruturacao dos dados (criterio 4).
// O gerador com ruido gaussiano pode produzir valores fora da faixa valida
// (nota < 0, nota > 10, frequencia negativa, etc.). Estas rotinas corrigem
// (normalize) ou rejeitam (valido) esses registros antes da insercao.
class TratamentoDados {
public:
    // Corrige valores fora da faixa: nota para [0,10], frequencia para [0,100]
    Aluno normalizar(Aluno a);
    // Indica se o registro esta dentro das faixas validas (pos-normalizacao)
    bool valido(const Aluno& a);
};
#endif
