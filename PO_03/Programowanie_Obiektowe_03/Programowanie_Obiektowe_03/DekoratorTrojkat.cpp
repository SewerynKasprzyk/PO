#include "DekoratorTrojkat.h"

DekoratorTrojkat::DekoratorTrojkat(std::unique_ptr<Sygnal> k, double amp, int okr, double wyp)
    : Dekorator(std::move(k)), amplituda(amp), okres(okr), wypelnienie(wyp) {
}

double DekoratorTrojkat::symuluj(int t) {
    int pozycja = t % okres;
    double phase = static_cast<double>(pozycja) / okres;
    double wartosc = (phase < wypelnienie)
        ? (2 * amplituda / wypelnienie) * phase - amplituda
        : (-2 * amplituda / (1 - wypelnienie)) * (phase - wypelnienie) + amplituda;
    return komponent->symuluj(t) + wartosc;
}

void DekoratorTrojkat::serializuj(std::ostream& out) const {
    Dekorator::serializuj(out);
    out << "DekoratorTrojkat " << amplituda << " " << okres << " " << wypelnienie << " ";
}

std::unique_ptr<Sygnal> DekoratorTrojkat::deserializuj(std::istream& in) {
    double amp, wyp;
    int okr;
    in >> amp >> okr >> wyp;
    return std::make_unique<DekoratorTrojkat>(std::move(komponent), amp, okr, wyp);
}