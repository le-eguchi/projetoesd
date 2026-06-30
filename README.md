# Simulador de Gestao Academica - Projeto de Estruturas de Dados

Sistema em C++ que simula a gestao academica de 10.000 alunos, comparando o
desempenho de seis estruturas de dados sob diferentes condicoes restritivas.

## Estruturas implementadas (todas SEM STL na colecao)

Classicas (ementa):
- Lista Encadeada
- Arvore AVL (auto-balanceada)
- Tabela Hash (encadeamento separado manual)

Fora da ementa:
- Skip List (probabilistica, niveis com array C)
- Trie (arvore de prefixos, filhos em lista encadeada)

Estrutura otimizada:
- Trie Otimizada (filhos em array indexado por ASCII - acesso O(1))

## Funcionalidades

- CRUD completo (inserir, buscar, remover) em todas as estruturas
- Geracao de dados com ruido gaussiano (distribuicao normal)
- Tratamento de dados (normalizacao + validacao de faixas)
- Operacoes adicionais: media, desvio padrao, filtragem, classificacao, histograma
- Benchmark completo: insercao, busca, remocao, memoria, colisoes
- Cinco testes em condicoes restritivas (R2, R7, R12, R16, R21), todos medidos
- Teste de escalabilidade com N crescente (1k a 50k)
- Comparacao da estrutura otimizada vs original

## Como compilar e executar

```bash
make
./simulador
```

Ou diretamente:
```bash
g++ -std=c++17 -Wall -Wextra -O2 *.cpp -o simulador
./simulador
```

## Uso de IA

Os trechos desenvolvidos com auxilio de IA estao documentados em `IA_USAGE.md`.
