/**
 * @file PetlaUAR.h
 * @brief Control loop for automatic regulation system (UAR)
 */
#pragma once
#include "ObiektSISO.h"
#include <vector>
#include <memory>
#include <string>

/**
* @brief Represents a control loop composed of multiple SISO components
* @details Supports both open-loop and closed-loop operation, and allows dynamic composition of components
*/
class PetlaUAR : 
    public ObiektSISO 
{
    std::vector<std::unique_ptr<ObiektSISO>> obiekty; /**< List of components in the loop */
    std::vector<std::string> typy; /**< Corresponding types of components */
	bool zamknieta = true; /**< Closed-loop flag */
	double poprzednieWyjscie = 0.0; /**< Previous output value for closed-loop feedback */

public:

     /**
     * @brief Simulate the loop response for given input
     * @param x Input value
     * @return double Output value
     */
    double symuluj(double x) override;

     /**
     * @brief Set loop mode to open or closed
     * @param stan True for closed-loop, false for open-loop
     */
    void ustawZamknieta(bool stan);

     /**
     * @brief Add a new component to the loop
     * @param obiekt Component to add
     * @param typ Type identifier of the component
     */
    void dodajKomponent(std::unique_ptr<ObiektSISO> obiekt, const std::string& typ);

     /**
     * @brief Insert a component at a specific position
     * @param obiekt Component to add
     * @param index Position in the loop
     * @param typ Type identifier of the component
     */
    void dodajKomponentNaPozycji(std::unique_ptr<ObiektSISO> obiekt, size_t index, const std::string& typ);

     /**
     * @brief Remove a component from the loop
     * @param index Index of the component to remove
     */
    void usunKomponent(size_t index);

    /**
     * @brief Serialize the loop to a file
     * @param nazwaPliku Target file path
     */
    void serializuj(const std::string& nazwaPliku) const;

     /**
     * @brief Deserialize the loop from a file
     * @param nazwaPliku Source file path
     */
    void deserializuj(const std::string& nazwaPliku);

     /**
     * @brief Get list of component types
     * @return std::vector<std::string> Vector of type names
     */
    std::vector<std::string> pobierzTypyKomponentow() const;
};