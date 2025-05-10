#include "DekoratorProstokat.h"

DekoratorProstokat::DekoratorProstokat(std::unique_ptr<Sygnal> k, double amp, int okr, double wyp)
    : Dekorator(std::move(k)), amplituda(amp), okres(okr), wypelnienie(wyp) {
}

double DekoratorProstokat::symuluj(int t) {
    int pozycja = t % okres;
    double wartosc = (pozycja < (okres * wypelnienie)) ? amplituda : 0.0;
    return komponent->symuluj(t) + wartosc;
}

void DekoratorProstokat::serializuj(std::ostream& out) const {
    Dekorator::serializuj(out);
    out << "DekoratorProstokat " << amplituda << " " << okres << " " << wypelnienie << " ";
}

std::unique_ptr<Sygnal> DekoratorProstokat::deserializuj(std::istream& in) {
    double amp, wyp;
    int okr;
    in >> amp >> okr >> wyp;
    return std::make_unique<DekoratorProstokat>(std::move(komponent), amp, okr, wyp);
}