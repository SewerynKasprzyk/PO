#pragma once
#include "ObiektSISO.h"
#include <vector>
#include <deque>
class ModelARX :
    public ObiektSISO
{
public:
	ModelARX(std::vector<double> a, std::vector<double> b, unsigned k, double zmienna);

	double symuluj(double u) override;

private:
	//Zmienne
	std::vector<double> a; // wspó³czynniki a
	std::vector<double> b; // wspó³czynniki b

	std::deque<double> u; // bufor wejœciowy
	std::deque<double> y; // bufor wyjœciowy

	unsigned k; // rz¹d opóŸnienia

	//Metoda pomocnicza
	double szumTymczasowy() 
	{
		return 0.0;
	}
};

