#include "DekoratorTrojkat.h"

DekoratorTrojkat::DekoratorTrojkat(std::unique_ptr<Sygnal> k, double amp, int okr, double wyp)
    : Dekorator(std::move(k)), amplituda(amp), okres(okr), wypelnienie(wyp) {
}

double DekoratorTrojkat::symuluj(int t) {
    int pozycja = t % this->okres;
    double faza = static_cast<double>(pozycja) / this->okres;
    double wartosc = (faza < this->wypelnienie)
        ? (2 * this->amplituda / this->wypelnienie) * faza - this->amplituda
        : (-2 * this->amplituda / (1 - this->wypelnienie)) * (faza - this->wypelnienie) + this->amplituda;
    return this->komponent->symuluj(t) + wartosc;
}

void DekoratorTrojkat::serializuj(std::ostream& out) const {
    Dekorator::serializuj(out);
    out << "DekoratorTrojkat " << this->amplituda << " " << this->okres << " " << this->wypelnienie << " ";
}

std::unique_ptr<Sygnal> DekoratorTrojkat::deserializuj(std::istream& in) {
    double amp, wyp;
    int okr;
    in >> amp >> okr >> wyp;
    return std::make_unique<DekoratorTrojkat>(std::move(this->komponent), amp, okr, wyp);
}