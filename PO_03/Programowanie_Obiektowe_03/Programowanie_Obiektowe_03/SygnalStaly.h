/**
 * @file SygnalStaly.h
 * @brief Constant (DC) signal implementation
 */
#pragma once
#include "Sygnal.h"

 /**
  * @brief Constant value signal
  */
class SygnalStaly : 
    public Sygnal 
{
    double wartosc; /**< Constant signal value */
public:
    /**
     * @brief Construct a new constant signal
     * @param w Signal value (default 0.0)
     */
    explicit SygnalStaly(double w = 0.0);

    double symuluj(int t) override;
    void serializuj(std::ostream& out) const override;
    std::unique_ptr<Sygnal> deserializuj(std::istream& in) override;
};