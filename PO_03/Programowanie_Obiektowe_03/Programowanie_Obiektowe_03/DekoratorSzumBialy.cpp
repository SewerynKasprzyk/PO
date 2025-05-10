#include "DekoratorSzumBialy.h"

DekoratorSzumBialy::DekoratorSzumBialy(std::unique_ptr<Sygnal> k, double odch)
    : Dekorator(std::move(k)), odchylenie(odch), rozklad(0.0, odch) {
}

double DekoratorSzumBialy::symuluj(int t) {
    return komponent->symuluj(t) + rozklad(generator);
}

void DekoratorSzumBialy::serializuj(std::ostream& out) const {
    Dekorator::serializuj(out);
    out << "DekoratorSzumBialy " << odchylenie << " ";
}

std::unique_ptr<Sygnal> DekoratorSzumBialy::deserializuj(std::istream& in) {
    double odch;
    in >> odch;
    return std::make_unique<DekoratorSzumBialy>(std::move(komponent), odch);
}