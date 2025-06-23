#pragma once
#include "Sygnal.h"

class Stala : public Sygnal {
    double wartosc;
public:
    Stala(double w);
    double generuj(int t) override;
    void serializuj(std::ostream& out) const override;
};