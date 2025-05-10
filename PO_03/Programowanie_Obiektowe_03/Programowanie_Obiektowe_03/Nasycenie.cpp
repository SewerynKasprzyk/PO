#include "Nasycenie.h"

Nasycenie::Nasycenie(std::unique_ptr<Sygnal> s, double max)
    : component(std::move(s)), max_amplitude(max) {
}

double Nasycenie::generuj(int t) {
    double value = component->generuj(t);
    return std::clamp(value, -max_amplitude, max_amplitude);
}

void Nasycenie::serializuj(std::ostream& out) const {
    out << "Nasycenie " << max_amplitude << "\n";
    component->serializuj(out);
}