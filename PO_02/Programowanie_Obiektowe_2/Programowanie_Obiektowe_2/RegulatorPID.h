#pragma once
#include "ObiektSISO.h"
#include <stdexcept>

class RegulatorPID : 
    public ObiektSISO
{
public:
    // Konstruktor tylko dla regulatora P
    RegulatorPID(double k);

    // Konstruktor dla regulatora PI
    RegulatorPID(double k, double Ti);

    // Konstruktor dla regulatora PID
    RegulatorPID(double k, double Ti, double Td);

    // Funkcja symulacji
    double symuluj(double uchyb) override;

private:
    double k;                // wzmocnienie
    double Ti;               // czas ca³kowania
    double Td;               // czas ró¿niczkowania
    double suma_uchybow;     // suma uchybów dla ca³ki
    double uchyb_poprzedni;  // poprzednia wartoœæ uchybu dla ró¿niczki

    // Prywatna metoda sprawdzaj¹ca poprawnoœæ nastaw
    void sprawdzNastawy();
};
