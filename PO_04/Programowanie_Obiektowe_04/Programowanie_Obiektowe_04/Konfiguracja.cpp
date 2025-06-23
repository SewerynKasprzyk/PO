#include "Konfiguracja.h"
#include "Deserializacja.h"
#include <fstream>
#include <sstream>
#include <iostream>

Konfiguracja::Konfiguracja()
    : petla(std::make_unique<PetlaUAR>()), generator(nullptr), liczbaKrokow(100), zamknieta(true) {
}

void Konfiguracja::wczytaj(const std::string& nazwaPliku) {
    std::ifstream in(nazwaPliku);
    if (!in) throw std::runtime_error("Nie mo¿na otworzyæ pliku konfiguracyjnego: " + nazwaPliku);

    std::string linia;
    while (std::getline(in, linia)) {
        std::istringstream iss(linia);
        std::string klucz;
        if (std::getline(iss, klucz, '=')) {
            std::string wartosc;
            std::getline(iss, wartosc);

            if (klucz == "LiczbaKrokow") {
                liczbaKrokow = std::stoi(wartosc);
            }
            else if (klucz == "Zamknieta") {
                zamknieta = (wartosc == "true");
            }
            else if (klucz == "PetlaPlik") {
                // Fixed: Pass filename directly
                petla = std::make_unique<PetlaUAR>();
                petla->deserializuj(wartosc);
            }
            else if (klucz == "GeneratorPlik") {
                std::ifstream genIn(wartosc);
                if (genIn) {
                    generator = deserializujSygnal(genIn);
                }
            }
        }
    }
}

void Konfiguracja::zapisz(const std::string& nazwaPliku) const {
    std::ofstream out(nazwaPliku);
    if (!out) throw std::runtime_error("Nie mo¿na zapisaæ pliku konfiguracyjnego: " + nazwaPliku);

    out << "LiczbaKrokow=" << liczbaKrokow << "\n";
    out << "Zamknieta=" << (zamknieta ? "true" : "false") << "\n";

    if (petla) {
        const std::string petlaPlik = nazwaPliku + "_petla.txt";
        out << "PetlaPlik=" << petlaPlik << "\n";
        // Fixed: Pass filename instead of stream
        petla->serializuj(petlaPlik);
    }

    if (generator) {
        const std::string generatorPlik = nazwaPliku + "_generator.txt";
        out << "GeneratorPlik=" << generatorPlik << "\n";
        std::ofstream genOut(generatorPlik);
        if (genOut) {
            generator->serializuj(genOut);
        }
    }
}

void Konfiguracja::ustawPetle(std::unique_ptr<PetlaUAR> nowaPetla) {
    petla = std::move(nowaPetla);
}

void Konfiguracja::ustawGenerator(std::unique_ptr<Sygnal> nowyGenerator) {
    generator = std::move(nowyGenerator);
}

void Konfiguracja::ustawLiczbeKrokow(int kroki) {
    liczbaKrokow = kroki;
}

void Konfiguracja::ustawZamknieta(bool stan) {
    zamknieta = stan;
}

PetlaUAR* Konfiguracja::pobierzPetle() const {
    return petla.get();
}

Sygnal* Konfiguracja::pobierzGenerator() const {
    return generator.get();
}

int Konfiguracja::pobierzLiczbeKrokow() const {
    return liczbaKrokow;
}

bool Konfiguracja::czyZamknieta() const {
    return zamknieta;
}