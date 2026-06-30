#include "TratamentoDados.h"

Aluno TratamentoDados::normalizar(Aluno a) {
    float m = a.getMedia();
    if (m < 0.0f) m = 0.0f;
    if (m > 10.0f) m = 10.0f;
    a.setMedia(m);

    float f = a.getFrequencia();
    if (f < 0.0f) f = 0.0f;
    if (f > 100.0f) f = 100.0f;
    a.setFrequencia(f);

    return a;
}

bool TratamentoDados::valido(const Aluno& a) {
    if (a.getMedia() < 0.0f || a.getMedia() > 10.0f) return false;
    if (a.getFrequencia() < 0.0f || a.getFrequencia() > 100.0f) return false;
    return true;
}
