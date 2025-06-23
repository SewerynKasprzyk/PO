#pragma once
#include "ObiektSISO.h"
#include <vector>
#include <deque>
#include <random>

/**
 * @class ModelARX
 * @brief ARX (AutoRegressive with eXogenous input) model implementation
 *
 * This class implements a discrete-time ARX model with optional noise disturbance.
 * The model follows the equation:
 * y(k) + a1*y(k-1) + ... + an*y(k-n) = b0*u(k-d) + ... + bm*u(k-d-m) + e(k)
 * where e(k) is optional Gaussian noise.
 */
class ModelARX : 
    public ObiektSISO
{
public:
    /**
     * @brief Constructor with parameters
     * @param a Vector of autoregressive coefficients (a1 to an)
     * @param b Vector of input coefficients (b0 to bm)
     * @param k Input delay (discrete time steps)
     * @param zmienna Noise standard deviation (set to 0 for no noise)
     */
    ModelARX(std::vector<double> a, std::vector<double> b, unsigned k, double zmienna);

    /**
     * @brief Constructor from configuration file
     * @param nazwaPliku Path to configuration file containing model parameters
     * @throws std::runtime_error if file cannot be read or is malformed
     */
    ModelARX(const std::string& nazwaPliku);

    double symuluj(double u) override;

    /**
     * @brief Serialize model parameters to file
     * @param nazwaPliku Output file path
     * @throws std::runtime_error if file cannot be written
     */
    void serializuj(const std::string& nazwaPliku) const;

private:
    std::vector<double> a; /**< Autoregressive coefficients (a1 to an) */
    std::vector<double> b; /**< Input coefficients (b0 to bm) */

    std::deque<double> u; /**< Input buffer (u(k-1), u(k-2)...) */
    std::deque<double> y; /**< Output buffer (y(k-1), y(k-2)...) */

    unsigned k; /**< Input delay (discrete time steps) */

    // Noise-related members
    double mocZaklocenia; /**< Noise standard deviation (0 means no noise) */
    std::default_random_engine generator; /**< Random number generator */
    std::normal_distribution<double> rozklad{ 0.0, 1.0 }; /**< Normal distribution N(0,1) */

    // Serialization helpers
    std::vector<double> wspolczynnikiA; /**< Temporary storage for serialization */
    std::vector<double> wspolczynnikiB; /**< Temporary storage for serialization */

    /**
     * @brief Generate noise sample
     * @return Noise value from N(0, mocZaklocenia) distribution
     */
    double generujZaklocenie() {
        return rozklad(generator) * mocZaklocenia;
    }

    /**
     * @brief Parse coefficient list from string
     * @param linia String containing comma-separated coefficients
     * @return Vector of parsed coefficients
     * @throws std::invalid_argument if parsing fails
     */
    std::vector<double> parsujListe(const std::string& linia);

    /**
     * @brief Temporary noise generation (currently disabled)
     * @return Always returns 0.0
     * @note Placeholder for future noise implementation
     */
    double zaklocenieTymczasowe()
    {
        return 0.0;
    }
};