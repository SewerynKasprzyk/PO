#include "Trojkat.h"
#include <algorithm>

Trojkat::Trojkat(double a, int o, double w)
    : amplituda(a), okres(o), wypelnienie(std::clamp(w, 0.0, 1.0)) {
}

double Trojkat::generuj(int t) {
    int pozycja = t % okres;
    double phase = static_cast<double>(pozycja) / okres;

    if (phase < wypelnienie) {
        return amplituda * (phase / wypelnienie);  // faza narastania
    }
    else {
        return amplituda * (1 - (phase - wypelnienie) / (1 - wypelnienie));  // faza opadania
    }
}

void Trojkat::serializuj(std::ostream& out) const {
    out << "Trojkat " << amplituda << " " << okres << " " << wypelnienie << "\n";
}