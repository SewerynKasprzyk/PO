#include "DekoratorSzumBialy.h"

DekoratorSzumBialy::DekoratorSzumBialy(std::unique_ptr<Sygnal> k, double odch)
    : Dekorator(std::move(k)), odchylenie(odch), rozklad(0.0, odch) {
}

double DekoratorSzumBialy::symuluj(int t) {
    return this->komponent->symuluj(t) + this->rozklad(generator);
}

void DekoratorSzumBialy::serializuj(std::ostream& out) const {
    out << "DekoratorSzumBialy " << odchylenie << " ";
    komponent->serializuj(out);
}

std::unique_ptr<Sygnal> DekoratorSzumBialy::klonuj() const {
    return std::make_unique<DekoratorSzumBialy>(
        komponent->klonuj(),
        odchylenie
    );
}