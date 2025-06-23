#include "ModelARX.h"
#include <numeric>
#include <fstream>
#include <sstream>
#include <iostream>

ModelARX::ModelARX(std::vector<double> a, std::vector<double> b, unsigned k, double mocZaklocenia)
    : a(a), b(b), k(k), wspolczynnikiA(a), wspolczynnikiB(b), mocZaklocenia(mocZaklocenia) {
    this->u.resize(b.size() + this->k, 0.0);
    this->y.resize(a.size(), 0.0);
}

ModelARX::ModelARX(const std::string& nazwaPliku)
{
    std::ifstream in(nazwaPliku);
    if (!in) {
        std::cerr << "Blad otwierania pliku do odczytu: " << nazwaPliku << "\n";
        return;
    }

    std::string linia;
    bool mocZakloceniaZaladowana = false;
    bool wspolczynnikiAZaladowane = false;
    bool wspolczynnikiBZaladowane = false;

    try {
        while (std::getline(in, linia)) {
            auto pos = linia.find('=');
            if (pos == std::string::npos) {
                std::cerr << "Blad formatu w linii: " << linia << "\n";
                continue;
            }

            std::string klucz = linia.substr(0, pos);
            std::string wartosc = linia.substr(pos + 1);

            if (klucz == "mocZaklocenia") {
                try {
                    this->mocZaklocenia = std::stod(wartosc);
                    mocZakloceniaZaladowana = true;
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Blad konwersji wartosci mocZaklocenia: " << wartosc << "\n";
                }
            }
            else if (klucz == "A") {
                this->wspolczynnikiA = this->parsujListe(wartosc);
                wspolczynnikiAZaladowane = true;
            }
            else if (klucz == "B") {
                this->wspolczynnikiB = this->parsujListe(wartosc);
                wspolczynnikiBZaladowane = true;
            }
        }

        // SprawdŸ, czy wszystkie wymagane dane zosta³y za³adowane
        if (!mocZakloceniaZaladowana) {
            std::cerr << "Blad: Brak wartosci dla 'mocZaklocenia' w pliku.\n";
        }
        if (!wspolczynnikiAZaladowane) {
            std::cerr << "Blad: Brak wartosci dla wspolczynnikow A w pliku.\n";
        }
        if (!wspolczynnikiBZaladowane) {
            std::cerr << "Blad: Brak wartosci dla wspolczynnikow B w pliku.\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Blad podczas deserializacji: " << e.what() << "\n";
    }
}


double ModelARX::symuluj(double u)
{
	this->u.push_front(u); // dodaj nowe pobudzenie do bufora wejœciowego

	double ay = -std::inner_product(this->a.begin(), this->a.end(), this->y.begin(), 0.0);
	double bu = std::inner_product(this->b.begin(), this->b.end(), this->u.begin() + this->k, 0.0);
    double y0 = ay + bu + this->generujZaklocenie();

	this->y.push_front(y0); // dodaj nowe wyjœcie do bufora wyjœciowego

	this->u.pop_back(); // usuñ najstarsze pobudzenie z bufora wejœciowego
	this->y.pop_back(); // usuñ najstarsze wyjœcie z bufora wyjœciowego

	return y0; // zwróæ nowe wyjœcie
}

void ModelARX::serializuj(const std::string& nazwaPliku) const
{
    std::ofstream out(nazwaPliku);
    if (!out) {
        std::cerr << "Blad otwierania pliku do zapisu: " << nazwaPliku << "\n";
        return;
    }

    try {
        // Zapisz moc zak³ócenia
        out << "mocZaklocenia=" << this->mocZaklocenia << "\n";

        // Zapisz wspó³czynniki A
        if (this->wspolczynnikiA.empty()) {
            std::cerr << "Blad: Wspolczynniki A sa puste.\n";
            return;
        }
        out << "A=";
        for (size_t i = 0; i < this->wspolczynnikiA.size(); ++i) {
            out << this->wspolczynnikiA[i];
            if (i < this->wspolczynnikiA.size() - 1) out << ",";
        }
        out << "\n";

        // Zapisz wspó³czynniki B
        if (this->wspolczynnikiB.empty()) {
            std::cerr << "Blad: Wspolczynniki B sa puste.\n";
            return;
        }
        out << "B=";
        for (size_t i = 0; i < this->wspolczynnikiB.size(); ++i) {
            out << this->wspolczynnikiB[i];
            if (i < this->wspolczynnikiB.size() - 1) out << ",";
        }
        out << "\n";

        std::cout << "Dane zostaly pomyslnie zapisane do pliku: " << nazwaPliku << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Blad podczas zapisywania danych: " << e.what() << "\n";
    }
}



std::vector<double> ModelARX::parsujListe(const std::string& linia)
{
    std::vector<double> wyniki;
    std::stringstream ss(linia);
    std::string liczba;
    while (std::getline(ss, liczba, ',')) {
        wyniki.push_back(std::stod(liczba));
    }
    return wyniki;
}
