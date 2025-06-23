/**
 * @file RegulatorPID.h
 * @brief PID controller implementation
 */
#pragma once
#include "ObiektSISO.h"
#include <stdexcept>

 /**
  * @brief PID controller with configurable modes (P/PI/PID)
  */
class RegulatorPID : 
    public ObiektSISO 
{
public:
    /**
     * @brief P-only controller
     * @param k Proportional gain
     */
    explicit RegulatorPID(double k);

    /**
     * @brief PI controller
     * @param k Proportional gain
     * @param Ti Integral time
     */
    RegulatorPID(double k, double Ti);

    /**
     * @brief Full PID controller
     * @param k Proportional gain
     * @param Ti Integral time
     * @param Td Derivative time
     */
    RegulatorPID(double k, double Ti, double Td);

    double symuluj(double uchyb) override;

    RegulatorPID(const std::string& plik);         ///< Konstruktor z pliku
    void serializuj(const std::string& plik) const; ///< Zapis do pliku

private:
    double k;               /**< Proportional gain */
    double Ti;              /**< Integral time */
    double Td;              /**< Derivative time */
    double suma_uchybow;    /**< Error accumulator */
    double uchyb_poprzedni; /**< Previous error */

    void sprawdzNastawy() const; /**< Validate controller settings */
};