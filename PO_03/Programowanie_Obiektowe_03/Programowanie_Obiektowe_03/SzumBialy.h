#pragma once
#include "Sygnal.h"
#include <random>

class SzumBialy : public Sygnal {
    mutable std::default_random_engine generator;
    std::normal_distribution<double> rozklad;
public:
    SzumBialy(double srednia, double odchylenie);
    double generuj(int t) override;
    void serializuj(std::ostream& out) const override;
};