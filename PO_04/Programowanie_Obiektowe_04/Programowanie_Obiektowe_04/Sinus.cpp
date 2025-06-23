#include "Sinus.h"

#define M_PI 3.14159265358979323846

Sinus::Sinus(double a, double f) 
    : amplituda(a), czestotliwosc(f), y_prev(0), y_prev_prev(0), last_t(-1) {
    y_prev_prev = 0; // t=0
    y_prev = amplituda * std::sin(2 * M_PI * czestotliwosc * 1); // t=1
    last_t = 1;
}

double Sinus::generuj(int t) {
    if (t < 0) return 0;
    if (t == 0) return y_prev_prev;
    if (t == 1) return y_prev;

    if (t != last_t + 1) 
        throw std::runtime_error("Niesekwencyjne wywo³anie Sinus::generuj");

    double theta = 2 * M_PI * czestotliwosc;
    double y_next = 2 * std::cos(theta) * y_prev - y_prev_prev;
    y_prev_prev = y_prev;
    y_prev = y_next;
    last_t = t;
    return y_next;
}

void Sinus::serializuj(std::ostream& out) const {
    out << "Sinus " << amplituda << " " << czestotliwosc << "\n";
}