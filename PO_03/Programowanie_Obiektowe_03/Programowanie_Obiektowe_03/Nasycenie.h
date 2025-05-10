#pragma once
#include "Sygnal.h"

#include <algorithm>

class Nasycenie : public Sygnal {
    std::unique_ptr<Sygnal> component;
    double max_amplitude;
public:
    Nasycenie(std::unique_ptr<Sygnal> s, double max);
    double generuj(int t) override;
    void serializuj(std::ostream& out) const override;
};