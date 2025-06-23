/**
 * @file DekoratorSinus.h
 * @brief Decorator that applies sinusoidal modulation
 */
#pragma once
#include "Dekorator.h"
#include <cmath>

 /**
  * @brief Sinusoidal wave signal decorator
  */
class DekoratorSinus : 
    public Dekorator
{
    double amplituda, czestotliwosc; /**< Amplitude and frequency */
    double y_prev1, y_prev2;         /**< Previous signal values for recursion */
    int t_prev;                      /**< Previous time step */
public:
    /**
     * @brief Construct a new sinusoidal decorator
     * @param k Signal to decorate
     * @param amp Amplitude
     * @param czest Frequency
     */
    DekoratorSinus(std::unique_ptr<Sygnal> k, double amp, double czest);

    double symuluj(int t) override;
    void serializuj(std::ostream& out) const override;
    std::unique_ptr<Sygnal> klonuj() const override;
};