#include "Lista.h"
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

Lista::Lista() : cabeca(nullptr), tam(0) {}

Lista::~Lista() {
    No* atual = cabeca;
    while (atual) { No* prox = atual->proximo; delete atual; atual = prox; }
}

void Lista::inserir(Aluno aluno) {
    No* novo = new No(aluno);
    novo->proximo = cabeca;
    cabeca = novo;
    tam++;
}

Aluno* Lista::buscar(int ra) {
    for (No* n = cabeca; n; n = n->proximo)
        if (n->aluno.getRA() == ra) return &n->aluno;
    return nullptr;
}

bool Lista::remover(int ra) {
    No *atual = cabeca, *ant = nullptr;
    while (atual && atual->aluno.getRA() != ra) { ant = atual; atual = atual->proximo; }
    if (!atual) return false;
    if (!ant) cabeca = atual->proximo;
    else ant->proximo = atual->proximo;
    delete atual;
    tam--;
    return true;
}

bool Lista::vazia() { return cabeca == nullptr; }

void Lista::mostrar() {
    for (No* n = cabeca; n; n = n->proximo) n->aluno.mostrar();
}

int Lista::quantidade() { return tam; }
long long Lista::memoriaUsada() { return (long long)tam * sizeof(No); }

// Operacao 1: media geral das notas
float Lista::calcularMediaGeral() {
    if (!cabeca) return 0.0;
    float soma = 0.0;
    for (No* n = cabeca; n; n = n->proximo) soma += n->aluno.getMedia();
    return soma / tam;
}

// Operacao 1b: desvio padrao das notas (estatistica completa - criterio 2)
float Lista::calcularDesvioPadrao() {
    if (tam <= 0) return 0.0;
    float media = calcularMediaGeral();
    float somaQuad = 0.0;
    for (No* n = cabeca; n; n = n->proximo) {
        float d = n->aluno.getMedia() - media;
        somaQuad += d * d;
    }
    return sqrt(somaQuad / tam);
}

// Operacao 2: filtragem por nota minima
void Lista::filtrarAprovados(float notaMinima) {
    int aprovados = 0;
    for (No* n = cabeca; n; n = n->proximo)
        if (n->aluno.getMedia() >= notaMinima) aprovados++;
    cout << "Alunos aprovados (Nota >= " << notaMinima << "): "
         << aprovados << " de " << tam << " alunos." << endl;
}

// Operacao 3: classificacao - encontra o aluno de maior nota
Aluno Lista::encontrarMaiorNota() {
    if (!cabeca) return Aluno(-1, "Vazio", 0.0);
    Aluno melhor = cabeca->aluno;
    for (No* n = cabeca->proximo; n; n = n->proximo)
        if (n->aluno.getMedia() > melhor.getMedia()) melhor = n->aluno;
    return melhor;
}

// Operacao extra: histograma da distribuicao de notas (10 faixas de 0 a 10)
void Lista::imprimirHistograma() {
    const int FAIXAS = 10;
    int hist[FAIXAS] = {0};
    for (No* n = cabeca; n; n = n->proximo) {
        int f = (int)(n->aluno.getMedia());
        if (f < 0) f = 0;
        if (f >= FAIXAS) f = FAIXAS - 1;
        hist[f]++;
    }
    int maxC = 0;
    for (int i = 0; i < FAIXAS; i++) if (hist[i] > maxC) maxC = hist[i];

    cout << "\nDistribuicao das notas (histograma):\n";
    for (int i = 0; i < FAIXAS; i++) {
        cout << "[" << setw(2) << i << "-" << setw(2) << (i+1) << "] |";
        int barra = (maxC > 0) ? (hist[i] * 30 / maxC) : 0;
        for (int j = 0; j < barra; j++) cout << "#";
        for (int j = barra; j < 30; j++) cout << " ";
        cout << "| " << hist[i] << "\n";
    }
}
