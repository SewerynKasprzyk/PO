/**
 * @file DekoratorProstokat.h
 * @brief Decorator that applies rectangular wave modulation
 */
#pragma once
#include "Dekorator.h"

 /**
  * @brief Rectangular wave signal decorator
  */
class DekoratorProstokat : 
    public Dekorator
{
    double amplituda; /**< Wave amplitude */
    int okres;       /**< Wave period in samples */
    double wypelnienie; /**< Duty cycle (0-1) */
public:
    /**
     * @brief Construct a new rectangular wave decorator
     * @param k Signal to decorate
     * @param amp Amplitude
     * @param okr Period
     * @param wyp Duty cycle
     */
    DekoratorProstokat(std::unique_ptr<Sygnal> k, double amp, int okr, double wyp);

    double symuluj(int t) override;
    void serializuj(std::ostream& out) const override;
    std::unique_ptr<Sygnal> klonuj() const override;
};