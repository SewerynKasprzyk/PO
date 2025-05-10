/**
 * @file DekoratorSzumBialy.h
 * @brief Decorator that adds white noise to a signal
 */
#pragma once
#include "Dekorator.h"
#include <random>

 /**
  * @brief White noise signal decorator
  */
class DekoratorSzumBialy : 
    public Dekorator
{
    double odchylenie; /**< Noise standard deviation */
    std::default_random_engine generator; /**< Random number generator */
    std::normal_distribution<double> rozklad; /**< Normal distribution for noise */
public:
    /**
     * @brief Construct a new white noise decorator
     * @param k Signal to decorate
     * @param odch Noise standard deviation
     */
    DekoratorSzumBialy(std::unique_ptr<Sygnal> k, double odch);

    double symuluj(int t) override;
    void serializuj(std::ostream& out) const override;
    std::unique_ptr<Sygnal> deserializuj(std::istream& in) override;
};