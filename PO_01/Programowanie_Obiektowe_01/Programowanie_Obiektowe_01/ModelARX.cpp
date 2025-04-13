#include "ModelARX.h"
#include <numeric>

ModelARX::ModelARX(std::vector<double> a, std::vector<double> b, unsigned k, double zmienna)
{
	this->a = a;
	this->b = b;
	this->k = k;

	// Inicjalizacja buforów
	this->x.resize(b.size() + this->k, 0.0);
	this->y.resize(a.size(), 0.0);

}

double ModelARX::symuluj(double u)
{
	this->x.push_front(u); // dodaj nowe pobudzenie do bufora wejœciowego

	double ay = std::inner_product(this->a.begin(), this->a.end(), this->y.begin(), 0.0);
	double bx = std::inner_product(this->b.begin(), this->b.end(), this->x.begin() + this->k, 0.0);
	double y0 = ay + bx + this->szumTymczasowy();

	this->y.push_front(y0); // dodaj nowe wyjœcie do bufora wyjœciowego

	this->x.pop_back(); // usuñ najstarsze pobudzenie z bufora wejœciowego
	this->y.pop_back(); // usuñ najstarsze wyjœcie z bufora wyjœciowego

	return y0; // zwróæ nowe wyjœcie
}
