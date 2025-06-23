#include "DekoratorProstokat.h"

DekoratorProstokat::DekoratorProstokat(std::unique_ptr<Sygnal> k, double amp, int okr, double wyp)
    : Dekorator(std::move(k)), amplituda(amp), okres(okr), wypelnienie(wyp) {
}

double DekoratorProstokat::symuluj(int t) {
    int pozycja = t % this->okres;
    double wartosc = (pozycja < (this->okres * this->wypelnienie)) ? this->amplituda : 0.0;
    return this->komponent->symuluj(t) + wartosc;
}

void DekoratorProstokat::serializuj(std::ostream& out) const {
    out << "DekoratorProstokat " << amplituda << " " << okres << " " << wypelnienie << " ";
    komponent->serializuj(out);
}

std::unique_ptr<Sygnal> DekoratorProstokat::klonuj() const {
    return std::make_unique<DekoratorProstokat>(
        komponent->klonuj(),
        amplituda,
        okres,
        wypelnienie
    );
}