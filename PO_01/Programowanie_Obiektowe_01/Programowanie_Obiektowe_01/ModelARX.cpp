#include "ModelARX.h"
#include <numeric>

ModelARX::ModelARX(std::vector<double> a, std::vector<double> b, unsigned k, double zmienna) : a(a), b(b), k(k)
{
	// Inicjalizacja buforów
	this->u.resize(b.size() + this->k, 0.0);
	this->y.resize(a.size(), 0.0);
}

double ModelARX::symuluj(double u)
{
	this->u.push_front(u); // dodaj nowe pobudzenie do bufora wejœciowego

	double ay = -std::inner_product(this->a.begin(), this->a.end(), this->y.begin(), 0.0);
	double bu = std::inner_product(this->b.begin(), this->b.end(), this->u.begin() + this->k, 0.0);
	double y0 = ay + bu + this->szumTymczasowy();

	this->y.push_front(y0); // dodaj nowe wyjœcie do bufora wyjœciowego

	this->u.pop_back(); // usuñ najstarsze pobudzenie z bufora wejœciowego
	this->y.pop_back(); // usuñ najstarsze wyjœcie z bufora wyjœciowego

	return y0; // zwróæ nowe wyjœcie
}
