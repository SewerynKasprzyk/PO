#pragma once
#include "Sygnal.h"

class Prostokat : public Sygnal {
    double amplituda;
    int okres;
    double wypelnienie;
public:
    Prostokat(double a, int o, double w);
    double generuj(int t) override;
    void serializuj(std::ostream& out) const override;
};