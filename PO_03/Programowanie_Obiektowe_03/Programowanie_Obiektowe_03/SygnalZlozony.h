#pragma once
#include "Sygnal.h"
#include <vector>

class SygnalZlozony : public Sygnal {
    std::vector<std::unique_ptr<Sygnal>> sygnaly;
public:
    SygnalZlozony(std::vector<std::unique_ptr<Sygnal>> s);
    double generuj(int t) override;
    void serializuj(std::ostream& out) const override;
};