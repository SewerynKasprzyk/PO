/**
 * @file Dekorator.h
 * @brief Base decorator class for signal processing (Decorator Pattern)
 */
#pragma once
#include "Sygnal.h"
#include <memory>

 /**
  * @brief Abstract base decorator for signal processing
  * @details Implements the Decorator Pattern to dynamically add behavior to Sygnal objects
  */
class Dekorator : 
    public Sygnal
{
protected:
    std::unique_ptr<Sygnal> komponent; /**< Wrapped signal component being decorated */
public:
    /**
     * @brief Construct a new Dekorator object
     * @param k Unique pointer to the Sygnal to be decorated
     */
    Dekorator(std::unique_ptr<Sygnal> k);

    double symuluj(int t) override = 0;
    void serializuj(std::ostream& out) const override = 0;
    std::unique_ptr<Sygnal> klonuj() const override = 0;
};