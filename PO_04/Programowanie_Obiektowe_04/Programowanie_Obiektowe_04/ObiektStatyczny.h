/**
 * @file ObiektStatyczny.h
 * @brief Static object model for control system simulation
 */
#pragma once
#include "ObiektSISO.h"
#include <string>

/**
* @brief Represents a static SISO object with output range limits
*/
class ObiektStatyczny : 
    public ObiektSISO 
{
    double dolny, gorny; /**< Lower and upper bounds for the output */
public:

     /**
     * @brief Construct static object with given limits
     * @param d Lower bound
     * @param g Upper bound
     */
    ObiektStatyczny(double d, double g);

     /**
     * @brief Construct static object from file
     * @param plik File containing object data
     */
    ObiektStatyczny(const std::string& plik);

    double symuluj(double x) override;

     /**
     * @brief Serialize the object to a file
     * @param plik Target file path
     */
    void serializuj(const std::string& plik) const;
};