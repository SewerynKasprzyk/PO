#include "DekoratorNasycenie.h"

DekoratorNasycenie::DekoratorNasycenie(std::unique_ptr<Sygnal> k, double max)
    : Dekorator(std::move(k)), max_wartosc(max) {
}

double DekoratorNasycenie::symuluj(int t) {
    double wartosc = komponent->symuluj(t);
    if (wartosc > max_wartosc) return max_wartosc;
    if (wartosc < -max_wartosc) return -max_wartosc;
    return wartosc;
}

void DekoratorNasycenie::serializuj(std::ostream& out) const {
    Dekorator::serializuj(out);
    out << "DekoratorNasycenie " << max_wartosc << " ";
}

std::unique_ptr<Sygnal> DekoratorNasycenie::deserializuj(std::istream& in) {
    double max;
    in >> max;
    return std::make_unique<DekoratorNasycenie>(std::move(komponent), max);
}