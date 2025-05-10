#include "SygnalZlozony.h"

SygnalZlozony::SygnalZlozony(std::vector<std::unique_ptr<Sygnal>> s)
    : sygnaly(std::move(s)) {
}

double SygnalZlozony::generuj(int t) {
    double suma = 0;
    for (const auto& s : sygnaly)
        suma += s->generuj(t);
    return suma;
}

void SygnalZlozony::serializuj(std::ostream& out) const {
    out << "SygnalZlozony " << sygnaly.size() << "\n";
    for (const auto& s : sygnaly)
        s->serializuj(out);
}