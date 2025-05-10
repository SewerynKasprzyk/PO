#include "Dekorator.h"

Dekorator::Dekorator(std::unique_ptr<Sygnal> k) : komponent(std::move(k)) {}

void Dekorator::serializuj(std::ostream& out) const {
    komponent->serializuj(out);
}

std::unique_ptr<Sygnal> Dekorator::deserializuj(std::istream& in) {
    komponent = komponent->deserializuj(in);
    return std::move(komponent);
}