#include "DekoratorNasycenie.h"

DekoratorNasycenie::DekoratorNasycenie(std::unique_ptr<Sygnal> k, double max)
    : Dekorator(std::move(k)), max_wartosc(max) {
}

double DekoratorNasycenie::symuluj(int t) {
    double wartosc = this->komponent->symuluj(t);
    if (wartosc > this->max_wartosc) return this->max_wartosc;
    if (wartosc < -this->max_wartosc) return -this->max_wartosc;
    return wartosc;
}

void DekoratorNasycenie::serializuj(std::ostream& out) const {
    Dekorator::serializuj(out);
    out << "DekoratorNasycenie " << this->max_wartosc << " ";
}

std::unique_ptr<Sygnal> DekoratorNasycenie::deserializuj(std::istream& in) {
    double max;
    in >> max;
    return std::make_unique<DekoratorNasycenie>(std::move(this->komponent), max);
}