#include "RegulatorPID.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

// Konstruktor tylko dla regulatora P
RegulatorPID::RegulatorPID(double k)
    : k(k), Ti(0.0), Td(0.0), suma_uchybow(0.0), uchyb_poprzedni(0.0)
{
    sprawdzNastawy();
}

// Konstruktor dla regulatora PI
RegulatorPID::RegulatorPID(double k, double Ti)
    : k(k), Ti(Ti), Td(0.0), suma_uchybow(0.0), uchyb_poprzedni(0.0)
{
    sprawdzNastawy();
}

// Konstruktor dla regulatora PID
RegulatorPID::RegulatorPID(double k, double Ti, double Td)
    : k(k), Ti(Ti), Td(Td), suma_uchybow(0.0), uchyb_poprzedni(0.0)
{
    sprawdzNastawy();
}

// Funkcja symulacji (przeci¹¿enie)
double RegulatorPID::symuluj(double uchyb)
{
    // czêœæ proporcjonalna
    double wyjscie = this->k * uchyb;

    // czêœæ ca³kuj¹ca
    if (this->Ti > 0.0)
    {
        this->suma_uchybow += uchyb;
        wyjscie += 1.0 / this->Ti * (this->suma_uchybow);
    }

    // czêœæ ró¿niczkuj¹ca (opcjonalnie)
    if (this->Td > 0.0)
    {
        wyjscie += this->Td * (uchyb - this->uchyb_poprzedni);
    }

    this->uchyb_poprzedni = uchyb; // aktualizacja uchybu poprzedniego
    return wyjscie;
}

// Prywatna metoda sprawdzaj¹ca poprawnoœæ nastaw
void RegulatorPID::sprawdzNastawy() const
{
    if (this->k < 0.0 || this->Ti < 0.0 || this->Td < 0.0)
        throw std::invalid_argument("Wszystkie nastawy musz¹ byæ nieujemne (>= 0)!");
}

RegulatorPID::RegulatorPID(const std::string& plik)
    : k(0.0), Ti(0.0), Td(0.0), suma_uchybow(0.0), uchyb_poprzedni(0.0)
{
    std::ifstream in(plik);
    if (!in)
        throw std::runtime_error("Nie mozna otworzyc pliku: " + plik);

    std::string line;
    while (std::getline(in, line)) {
        std::istringstream ss(line);
        std::string key;
        if (std::getline(ss, key, '=')) {
            std::string value;
            if (std::getline(ss, value)) {
                if (key == "k") k = std::stod(value);
                else if (key == "Ti") Ti = std::stod(value);
                else if (key == "Td") Td = std::stod(value);
            }
        }
    }
    sprawdzNastawy();
}

void RegulatorPID::serializuj(const std::string& plik) const {
    std::ofstream out(plik);
    if (!out)
        throw std::runtime_error("Nie mozna otworzyc pliku do zapisu: " + plik);

    out << "k=" << k << "\n";
    out << "Ti=" << Ti << "\n";
    out << "Td=" << Td << "\n";
}