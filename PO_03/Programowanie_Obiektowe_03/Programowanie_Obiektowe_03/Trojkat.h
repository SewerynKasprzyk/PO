#pragma once
#include "Sygnal.h"

class Trojkat : public Sygnal {
    double amplituda;
    int okres;
    double wypelnienie;  // stosunek czasu narastania do ca³ego okresu (0-1)
public:
    Trojkat(double a, int o, double w);
    double generuj(int t) override;
    void serializuj(std::ostream& out) const override;
};