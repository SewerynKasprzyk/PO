/**
 * @file DekoratorNasycenie.h
 * @brief Decorator that applies saturation (clipping) to a signal
 */
#pragma once
#include "Dekorator.h"

 /**
  * @brief Saturation decorator limits signal amplitude to a maximum value
  */
class DekoratorNasycenie : 
    public Dekorator
{
    double max_wartosc; /**< Maximum allowed signal value (saturation threshold) */
public:
    /**
     * @brief Construct a new saturation decorator
     * @param k Signal to decorate
     * @param max Maximum allowed value
     */
    DekoratorNasycenie(std::unique_ptr<Sygnal> k, double max);

    double symuluj(int t) override;
    void serializuj(std::ostream& out) const override;
    std::unique_ptr<Sygnal> deserializuj(std::istream& in) override;
};