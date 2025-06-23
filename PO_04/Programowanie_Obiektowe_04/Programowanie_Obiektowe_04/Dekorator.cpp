#include "Dekorator.h"

Dekorator::Dekorator(std::unique_ptr<Sygnal> k) : komponent(std::move(k)) {}

void Dekorator::serializuj(std::ostream& out) const {
    this->komponent->serializuj(out);
}