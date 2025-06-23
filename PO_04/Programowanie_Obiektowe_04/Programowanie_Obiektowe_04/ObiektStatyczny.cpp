#include "ObiektStatyczny.h"
#include <fstream>
#include <sstream>

ObiektStatyczny::ObiektStatyczny(double d, double g) : dolny(d), gorny(g) {}

ObiektStatyczny::ObiektStatyczny(const std::string& plik) {
    std::ifstream in(plik);
    std::string line;
    while (std::getline(in, line)) {
        if (line.find("dolny=") == 0) dolny = std::stod(line.substr(6));
        if (line.find("gorny=") == 0) gorny = std::stod(line.substr(6));
    }
}

double ObiektStatyczny::symuluj(double x) {
    if (x < dolny) return dolny;
    if (x > gorny) return gorny;
    return x;
}

void ObiektStatyczny::serializuj(const std::string& plik) const {
    std::ofstream out(plik);
    out << "typ=ObiektStatyczny\n";
    out << "dolny=" << dolny << "\n";
    out << "gorny=" << gorny << "\n";
}