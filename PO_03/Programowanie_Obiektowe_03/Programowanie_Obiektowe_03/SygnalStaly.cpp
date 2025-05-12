#include "SygnalStaly.h"

SygnalStaly::SygnalStaly(double w) : wartosc(w) {}

double SygnalStaly::symuluj(int t) {
    return this->wartosc;
}

void SygnalStaly::serializuj(std::ostream& out) const {
    out << "SygnalStaly " << this->wartosc << " ";
}

std::unique_ptr<Sygnal> SygnalStaly::deserializuj(std::istream& in) {
    double w;
    in >> w;
    return std::make_unique<SygnalStaly>(w);
}