#pragma once
#include "Sygnal.h"
#include <cmath>

class Sinus : public Sygnal {
    double amplituda, czestotliwosc;
    double y_prev, y_prev_prev;
    int last_t;
public:
    Sinus(double a, double f);
    double generuj(int t) override;
    void serializuj(std::ostream& out) const override;
};