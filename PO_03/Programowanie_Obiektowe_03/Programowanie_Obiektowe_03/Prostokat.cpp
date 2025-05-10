#include "Prostokat.h"

Prostokat::Prostokat(double a, int o, double w)
    : amplituda(a), okres(o), wypelnienie(w) {
}

double Prostokat::generuj(int t) {
    int pozycja = t % okres;
    return (pozycja < okres * wypelnienie) ? amplituda : -amplituda;
}

void Prostokat::serializuj(std::ostream& out) const {
    out << "Prostokat " << amplituda << " " << okres << " " << wypelnienie << "\n";
}