/**
 * @file Konfiguracja.h
 * @brief Configuration class for the control loop simulation
 * @details Stores and manages the simulation loop, signal generator, number of steps, and loop mode
 */
#pragma once
#include "PetlaUAR.h"
#include "Sygnal.h"
#include <memory>
#include <string>

 /**
  * @brief Holds configuration settings for the control system simulation
  */
class Konfiguracja {
private:
    std::unique_ptr<PetlaUAR> petla; /**< Control loop instance */
    std::unique_ptr<Sygnal> generator; /**< Signal generator */
    int liczbaKrokow; /**< Number of simulation steps */
    bool zamknieta; /**< Closed-loop mode flag */

public:

    /**
    * @brief Default constructor
    */
    Konfiguracja();

    /**
     * @brief Load configuration from a file
     * @param nazwaPliku Name of the file to load
     */
    void wczytaj(const std::string& nazwaPliku);

     /**
     * @brief Save configuration to a file
     * @param nazwaPliku Name of the file to save to
     */
    void zapisz(const std::string& nazwaPliku) const;


    /** @name Setters
     *  Methods used to configure the simulation parameters
     */
     ///@{
    void ustawPetle(std::unique_ptr<PetlaUAR> nowaPetla);
    void ustawGenerator(std::unique_ptr<Sygnal> nowyGenerator);
    void ustawLiczbeKrokow(int kroki);
    void ustawZamknieta(bool stan);
    ///@}

     /** @name Getters
     *  Methods used to retrieve the current configuration state
     */
     ///@{
    PetlaUAR* pobierzPetle() const;
    Sygnal* pobierzGenerator() const;
    int pobierzLiczbeKrokow() const;
    bool czyZamknieta() const;
    ///@}
};