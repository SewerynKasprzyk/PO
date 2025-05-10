/**
 * @file DekoratorTrojkat.h
 * @brief Decorator that applies triangular wave modulation
 */
#pragma once
#include "Dekorator.h"

 /**
  * @brief Triangular wave signal decorator
  */
class DekoratorTrojkat : 
    public Dekorator
{
    double amplituda; /**< Wave amplitude */
    int okres;       /**< Wave period in samples */
    double wypelnienie; /**< Symmetry ratio (0-1) */
public:
    /**
     * @brief Construct a new triangular wave decorator
     * @param k Signal to decorate
     * @param amp Amplitude
     * @param okr Period
     * @param wyp Symmetry ratio
     */
    DekoratorTrojkat(std::unique_ptr<Sygnal> k, double amp, int okr, double wyp);

    double symuluj(int t) override;
    void serializuj(std::ostream& out) const override;
    std::unique_ptr<Sygnal> deserializuj(std::istream& in) override;
};