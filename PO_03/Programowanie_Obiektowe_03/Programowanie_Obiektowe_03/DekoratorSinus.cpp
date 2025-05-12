#include "DekoratorSinus.h"

constexpr auto M_PI = 3.14159265358979323846;

DekoratorSinus::DekoratorSinus(std::unique_ptr<Sygnal> k, double amp, double czest)
    : Dekorator(std::move(k)), amplituda(amp), czestotliwosc(czest),
    y_prev1(0), y_prev2(0), t_prev(-1) {
    // Poprawiona inicjalizacja: generuj próbkê dla t=0 i t=1
    this->y_prev1 = this->amplituda * std::sin(2 * M_PI * this->czestotliwosc * 1); // t=1
    this->y_prev2 = 0; // t=0
}

double DekoratorSinus::symuluj(int t) {
    if (t < 0) return 0;

    // Aktualizuj t_prev dla wszystkich przypadków
    if (t == this->t_prev + 1) {
        double omega = 2 * M_PI * this->czestotliwosc;
        double y_new = 2 * std::cos(omega) * this->y_prev1 - this->y_prev2;
        this->y_prev2 = this->y_prev1;
        this->y_prev1 = y_new;
        this->t_prev = t;
        return this->komponent->symuluj(t) + y_new;
    }
    else if (t == 0) {
        this->t_prev = t;
        return this->komponent->symuluj(t) + this->y_prev2; // y_prev2 odpowiada t=0
    }
    else if (t == 1) {
        this->t_prev = t;
        return this->komponent->symuluj(t) + this->y_prev1; // y_prev1 odpowiada t=1
    }

    throw std::runtime_error("Nieci¹g³e t dla sygna³u sinusoidalnego.");
}

void DekoratorSinus::serializuj(std::ostream& out) const {
    Dekorator::serializuj(out);
    out << "DekoratorSinus " << this->amplituda << " " << this->czestotliwosc << " ";
}

std::unique_ptr<Sygnal> DekoratorSinus::deserializuj(std::istream& in) {
    double amp, czest;
    in >> amp >> czest;
    return std::make_unique<DekoratorSinus>(std::move(this->komponent), amp, czest);
}