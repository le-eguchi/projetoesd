#include "AVL.h"

AVL::AVL() : raiz(nullptr), qtd(0), limiteMax(-1) {}
AVL::~AVL() { destruir(raiz); }

NoAVL* AVL::rotD(NoAVL* y) {
    NoAVL *x = y->esquerda; NoAVL *T2 = x->direita;
    x->direita = y; y->esquerda = T2;
    y->altura = maxInt(h(y->esquerda), h(y->direita)) + 1;
    x->altura = maxInt(h(x->esquerda), h(x->direita)) + 1;
    return x;
}

NoAVL* AVL::rotE(NoAVL* x) {
    NoAVL *y = x->direita; NoAVL *T2 = y->esquerda;
    y->esquerda = x; x->direita = T2;
    x->altura = maxInt(h(x->esquerda), h(x->direita)) + 1;
    y->altura = maxInt(h(y->esquerda), h(y->direita)) + 1;
    return y;
}

// Reequilibra um no apos insercao ou remocao, tratando os 4 casos (LL, RR, LR, RL)
NoAVL* AVL::balancear(NoAVL* no) {
    no->altura = 1 + maxInt(h(no->esquerda), h(no->direita));
    int b = fator(no);
    if (b > 1 && fator(no->esquerda) >= 0) return rotD(no);                 // LL
    if (b > 1 && fator(no->esquerda) < 0) { no->esquerda = rotE(no->esquerda); return rotD(no); } // LR
    if (b < -1 && fator(no->direita) <= 0) return rotE(no);                 // RR
    if (b < -1 && fator(no->direita) > 0) { no->direita = rotD(no->direita); return rotE(no); }   // RL
    return no;
}

NoAVL* AVL::inserir(NoAVL* no, Aluno a, bool& inseriu) {
    if (!no) { inseriu = true; return new NoAVL(a); }
    if (a.getRA() < no->aluno.getRA()) no->esquerda = inserir(no->esquerda, a, inseriu);
    else if (a.getRA() > no->aluno.getRA()) no->direita = inserir(no->direita, a, inseriu);
    else { inseriu = false; return no; } // RA duplicado: ignora
    return balancear(no);
}

void AVL::inserir(Aluno a) {
    // Restricao R2: se ha limite e ja foi atingido, rejeita a insercao
    if (limiteMax > 0 && qtd >= limiteMax) return;
    bool inseriu = false;
    raiz = inserir(raiz, a, inseriu);
    if (inseriu) qtd++;
}

NoAVL* AVL::menorNo(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda) atual = atual->esquerda;
    return atual;
}

// [CRUD] Remocao com os tres casos: folha, um filho, dois filhos (sucessor in-order)
NoAVL* AVL::remover(NoAVL* no, int ra, bool& removeu) {
    if (!no) { removeu = false; return nullptr; }
    if (ra < no->aluno.getRA()) no->esquerda = remover(no->esquerda, ra, removeu);
    else if (ra > no->aluno.getRA()) no->direita = remover(no->direita, ra, removeu);
    else {
        removeu = true;
        if (!no->esquerda || !no->direita) {
            NoAVL* filho = no->esquerda ? no->esquerda : no->direita;
            delete no;
            return filho; // pode ser nullptr (folha)
        }
        NoAVL* suc = menorNo(no->direita);
        no->aluno = suc->aluno;
        bool dummy = false;
        no->direita = remover(no->direita, suc->aluno.getRA(), dummy);
    }
    return balancear(no);
}

bool AVL::remover(int ra) {
    bool removeu = false;
    raiz = remover(raiz, ra, removeu);
    if (removeu) qtd--;
    return removeu;
}

NoAVL* AVL::buscar(NoAVL* no, int ra) {
    if (!no || no->aluno.getRA() == ra) return no;
    return (ra < no->aluno.getRA()) ? buscar(no->esquerda, ra) : buscar(no->direita, ra);
}

Aluno* AVL::buscar(int ra) {
    NoAVL* res = buscar(raiz, ra);
    return res ? &res->aluno : nullptr;
}

void AVL::destruir(NoAVL* no) {
    if (no) { destruir(no->esquerda); destruir(no->direita); delete no; }
}

int AVL::contar(NoAVL* no) {
    if (!no) return 0;
    return 1 + contar(no->esquerda) + contar(no->direita);
}

int AVL::quantidade() { return qtd; }
int AVL::altura() { return h(raiz); }
void AVL::setLimite(int max) { limiteMax = max; }
long long AVL::memoriaUsada() { return (long long)qtd * sizeof(NoAVL); }
