/**
 * @file Sygnal.h
 * @brief Abstract base class for all signal types
 */
#pragma once
#include <iostream>
#include <memory>
#include <random>

 /**
  * @brief Interface for signal generators
  */
class Sygnal {
public:
    virtual ~Sygnal() = default;

    /**
     * @brief Simulate signal value at time t
     * @param t Time step
     * @return double Signal value
     */
    virtual double symuluj(int t) = 0;

    /**
     * @brief Serialize signal to output stream
     * @param out Output stream
     */
    virtual void serializuj(std::ostream& out) const = 0;

    /**
     * @brief Deserialize signal from input stream
     * @param in Input stream
     * @return std::unique_ptr<Sygnal> Deserialized signal
     */
    virtual std::unique_ptr<Sygnal> deserializuj(std::istream& in) = 0;
};