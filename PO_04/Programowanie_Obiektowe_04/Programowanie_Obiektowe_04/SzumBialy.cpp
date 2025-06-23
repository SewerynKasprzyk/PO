#include "SzumBialy.h"
#include <chrono>

SzumBialy::SzumBialy(double srednia, double odchylenie)
    : rozklad(srednia, odchylenie) {
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

double SzumBialy::generuj(int t) {
    return rozklad(generator);
}

void SzumBialy::serializuj(std::ostream& out) const {
    out << "SzumBialy " << rozklad.mean() << " " << rozklad.stddev() << "\n";
}