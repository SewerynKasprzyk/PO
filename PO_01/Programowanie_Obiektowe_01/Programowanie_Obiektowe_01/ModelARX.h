#pragma once
#include "ObiektSISO.h"
#include <vector>
#include <deque>
#include <random>
class ModelARX :
    public ObiektSISO
{
public:
	//Konstruktory
	ModelARX(std::vector<double> a, std::vector<double> b, unsigned k, double zmienna);
	ModelARX(const std::string& nazwaPliku);

	//Metody modelu
	double symuluj(double u) override;

	//Metody serializacji
	void serializuj(const std::string& nazwaPliku) const;


private:
	//Zmienne modelu
	std::vector<double> a; // wspó³czynniki a
	std::vector<double> b; // wspó³czynniki b

	std::deque<double> u; // bufor wejœciowy
	std::deque<double> y; // bufor wyjœciowy

	unsigned k; // rz¹d opóŸnienia

	//Zmienne zak³ócenia
	double mocZaklocenia; // Odchylenie standardowe zak³ócenia
	std::default_random_engine generator;
	std::normal_distribution<double> rozklad{ 0.0, 1.0 };

	//Zmienne serializacji
	std::vector<double> wspolczynnikiA;
	std::vector<double> wspolczynnikiB;

	//Metody zaklocenia
	double generujZaklocenie() {
		return rozklad(generator) * mocZaklocenia;
	}

	//Metody serializacji
	std::vector<double> parsujListe(const std::string& linia);

	double zaklocenieTymczasowe() 
	{
		return 0.0;
	}
};

