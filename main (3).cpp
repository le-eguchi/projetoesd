#include <iostream>
#include <string>
#include "Aluno.h"
#include "AVL.h"
#include "SkipList.h"
#include "Lista.h"
#include "Hash.h"
#include "Trie.h"
#include "TrieOptimizada.h"
#include "Gerador.h"
#include "TratamentoDados.h"
#include "Benchmark.h"
using namespace std;

// Estruturas globais do sistema
AVL avl;
SkipList skipList;
Lista lista;
Hash tabelaHash;
Trie trieOriginal;
TrieOptimizada trieOpt;

const int TOTAL = 10000;
const unsigned int SEED = 42;

// Buffers de dados e chaves para os benchmarks
Aluno* dados = nullptr;
int totalValidos = 0;
int* rasBusca = nullptr;
string* nomesBusca = nullptr;
const int QTD_BUSCA = 1000;

void exibirMenu() {
    cout << "\n=========================================" << endl;
    cout << " SISTEMA DE GESTAO ACADEMICA (SIMULADOR)" << endl;
    cout << "=========================================" << endl;
    cout << "1. Ver Estatisticas e Operacoes Adicionais" << endl;
    cout << "2. Executar Benchmark Completo (Criterio 9)" << endl;
    cout << "3. Buscar Aluno por RA (testar estruturas)" << endl;
    cout << "4. Remover Aluno por RA (CRUD completo)" << endl;
    cout << "5. Executar Testes Restritivos (Criterio 8)" << endl;
    cout << "6. Comparar Trie Original vs Otimizada (Criterio 7)" << endl;
    cout << "7. Escalabilidade com N crescente (Criterio 9)" << endl;
    cout << "8. Visualizar estrutura interna (Skip List)" << endl;
    cout << "0. Sair" << endl;
    cout << "Escolha uma opcao: ";
}

// Carrega o dataset: gera com ruido gaussiano + aplica tratamento de dados
void carregarDados() {
    cout << "Inicializando o sistema..." << endl;
    cout << "Gerando " << TOTAL << " amostras com RUIDO GAUSSIANO (seed " << SEED << ")..." << endl;

    Gerador gerador(SEED);
    TratamentoDados tratamento;
    dados = new Aluno[TOTAL];

    int gerados = 0, normalizados = 0, descartados = 0;

    for (int i = 0; i < TOTAL; i++) {
        Aluno bruto = gerador.gerarAluno(1000 + i);
        gerados++;
        // CRITERIO 4: normaliza (corrige outliers do ruido gaussiano)
        Aluno tratado = tratamento.normalizar(bruto);
        normalizados++;
        if (tratamento.valido(tratado)) {
            dados[totalValidos++] = tratado;
            // Insere em TODAS as estruturas (CRUD insercao)
            avl.inserir(tratado);
            tabelaHash.inserir(tratado);
            skipList.inserir(tratado);
            lista.inserir(tratado);
            trieOriginal.inserir(tratado.getNome());
            trieOpt.inserir(tratado.getNome());
        } else {
            descartados++;
        }
    }

    // Prepara chaves de busca para os benchmarks
    rasBusca = new int[QTD_BUSCA];
    nomesBusca = new string[QTD_BUSCA];
    for (int i = 0; i < QTD_BUSCA; i++) {
        rasBusca[i] = dados[(i * 7) % totalValidos].getRA();
        nomesBusca[i] = dados[(i * 7) % totalValidos].getNome();
    }

    cout << "\n[GERACAO E TRATAMENTO DE DADOS]\n";
    cout << "Registros gerados     : " << gerados << "\n";
    cout << "Registros normalizados: " << normalizados << "\n";
    cout << "Registros validos     : " << totalValidos << "\n";
    cout << "Registros descartados : " << descartados << "\n";
    cout << "Dados carregados em todas as 6 estruturas!\n";
}

int main() {
    carregarDados();

    int opcao;
    do {
        exibirMenu();
        if (!(cin >> opcao)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Entrada invalida.\n"; continue; }

        switch (opcao) {
            case 1: {
                cout << "\n--- ESTATISTICAS (OPERACOES ADICIONAIS - CRITERIO 2) ---" << endl;
                cout << "Media Geral   : " << lista.calcularMediaGeral() << endl;
                cout << "Desvio Padrao : " << lista.calcularDesvioPadrao() << endl;
                cout << "Filtragem     : ";
                lista.filtrarAprovados(6.0f);
                cout << "Melhor Aluno  : ";
                lista.encontrarMaiorNota().mostrar();
                lista.imprimirHistograma();
                break;
            }
            case 2:
                Benchmark::completo(dados, totalValidos, rasBusca, QTD_BUSCA);
                break;
            case 3: {
                int raBusc;
                cout << "\nDigite o RA (ex: 1000 a " << (1000 + totalValidos - 1) << "): ";
                cin >> raBusc;
                cout << "\nBuscando RA " << raBusc << " nas estruturas:\n";
                Aluno* rAvl = avl.buscar(raBusc);
                Aluno* rHash = tabelaHash.buscar(raBusc);
                Aluno* rSkip = skipList.buscar(raBusc);
                cout << "  AVL       : " << (rAvl ? "ENCONTRADO" : "nao encontrado") << "\n";
                cout << "  Hash      : " << (rHash ? "ENCONTRADO" : "nao encontrado") << "\n";
                cout << "  Skip List : " << (rSkip ? "ENCONTRADO" : "nao encontrado") << "\n";
                if (rAvl) { cout << "  Dados: "; rAvl->mostrar(); }
                break;
            }
            case 4: {
                int raRem;
                cout << "\nDigite o RA para remover: ";
                cin >> raRem;
                bool a = avl.remover(raRem);
                bool h = tabelaHash.remover(raRem);
                bool s = skipList.remover(raRem);
                bool l = lista.remover(raRem);
                cout << "Remocao (CRUD completo):\n";
                cout << "  AVL       : " << (a ? "removido" : "nao encontrado") << "\n";
                cout << "  Hash      : " << (h ? "removido" : "nao encontrado") << "\n";
                cout << "  Skip List : " << (s ? "removido" : "nao encontrado") << "\n";
                cout << "  Lista     : " << (l ? "removido" : "nao encontrado") << "\n";
                break;
            }
            case 5:
                Benchmark::testesRestritivos(dados, totalValidos);
                break;
            case 6:
                Benchmark::compararTries(dados, totalValidos, nomesBusca, QTD_BUSCA);
                break;
            case 7: {
                Gerador g(SEED);
                Benchmark::escalabilidade(g);
                break;
            }
            case 8:
                skipList.mostrarNiveis();
                break;
            case 0:
                cout << "\nEncerrando o sistema... Obrigado!" << endl;
                break;
            default:
                cout << "\nOpcao invalida. Tente novamente." << endl;
        }
    } while (opcao != 0);

    delete[] dados;
    delete[] rasBusca;
    delete[] nomesBusca;
    return 0;
}
