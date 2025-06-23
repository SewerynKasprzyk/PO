#include "DekoratorNasycenie.h"

DekoratorNasycenie::DekoratorNasycenie(std::unique_ptr<Sygnal> k, double max)
    : Dekorator(std::move(k)), max_wartosc(max) {}

double DekoratorNasycenie::symuluj(int t) {
    double wartosc = this->komponent->symuluj(t);
    if (wartosc > this->max_wartosc) return this->max_wartosc;
    if (wartosc < -this->max_wartosc) return -this->max_wartosc;
    return wartosc;
}

void DekoratorNasycenie::serializuj(std::ostream& out) const {
    out << "DekoratorNasycenie " << max_wartosc << " ";
    komponent->serializuj(out);
}

std::unique_ptr<Sygnal> DekoratorNasycenie::klonuj() const {
    // Use move on cloned component
    return std::make_unique<DekoratorNasycenie>(
        komponent->klonuj(),
        max_wartosc
    );
}