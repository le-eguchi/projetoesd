#include "Gerador.h"

// Seed fixo permite reproduzir exatamente o mesmo experimento (reprodutibilidade)
Gerador::Gerador(unsigned int seed)
    : motor(seed),
      distMedia(6.0f, 2.0f),        // media 6.0, desvio 2.0
      distFrequencia(85.0f, 15.0f)  // media 85%, desvio 15%
{}

// Gera um aluno com nota e frequencia sorteadas de distribuicoes normais.
// A distribuicao normal concentra a maioria dos valores perto da media,
// mas produz outliers naturais - bem mais realista que valores uniformes.
Aluno Gerador::gerarAluno(int ra) {
    string nome = "Estudante_" + to_string(ra);
    float nota = distMedia(motor);
    float freq = distFrequencia(motor);
    return Aluno(ra, nome, nota, freq);
}

// Adiciona ruido gaussiano a um valor especifico (usado em testes de robustez)
float Gerador::ruidoGaussiano(float valor, float desvio) {
    std::normal_distribution<float> ruido(0.0f, desvio);
    return valor + ruido(motor);
}
