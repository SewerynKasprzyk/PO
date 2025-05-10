#include "Stala.h"

Stala::Stala(double w) : wartosc(w) {}

double Stala::generuj(int t) {
    return wartosc;
}

void Stala::serializuj(std::ostream& out) const {
    out << "Stala " << wartosc << "\n";
}