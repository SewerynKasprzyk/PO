#pragma once
#include "Konfiguracja.h"
#include "TestyKonfiguracji.h"
#include "Sygnal.h"
#include "SygnalStaly.h"
#include "DekoratorSinus.h"
#include "DekoratorProstokat.h"
#include "DekoratorTrojkat.h"
#include "DekoratorSzumBialy.h"
#include "DekoratorNasycenie.h"
#include "ModelARX.h"
#include "RegulatorPID.h"
#include "PetlaUAR.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <memory>
#include <filesystem>  // For directory management

namespace fs = std::filesystem;

void wyswietlMenu() {
    std::cout << "\n=== MENU GLOWNE ===\n";
    std::cout << "1. Wczytaj konfiguracje z pliku\n";
    std::cout << "2. Zapisz konfiguracje do pliku\n";
    std::cout << "3. Modyfikuj parametry symulacji\n";
    std::cout << "4. Konfiguruj generator\n";
    std::cout << "5. Uruchom symulacje generatora (zapis do pliku)\n";
    std::cout << "6. Uruchom symulacje petli UAR (tryb kompozytowy)\n";
    std::cout << "7. Uruchom pelna symulacje (tryb MAIN)\n";
    std::cout << "8. Wyjscie\n";
    std::cout << "Wybierz opcje: ";
}

void modyfikujParametry(Konfiguracja& config) {
    int wybor;
    do {
        std::cout << "\n=== MODYFIKACJA PARAMETROW ===\n";
        std::cout << "1. Liczba krokow symulacji: " << config.pobierzLiczbeKrokow() << "\n";
        std::cout << "2. Typ petli: " << (config.czyZamknieta() ? "Zamknieta" : "Otwarta") << "\n";
        std::cout << "3. Powrot\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> wybor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (wybor) {
        case 1: {
            int kroki;
            std::cout << "Podaj nowa liczbe krokow: ";
            std::cin >> kroki;
            config.ustawLiczbeKrokow(kroki);
            break;
        }
        case 2: {
            bool stan;
            std::cout << "Podaj stan (0 - otwarta, 1 - zamknieta): ";
            std::cin >> stan;
            config.ustawZamknieta(stan);
            break;
        }
        case 3:
            return;
        default:
            std::cout << "Nieprawidlowy wybor.\n";
        }
    } while (true);
}

void konfigurujGenerator(Konfiguracja& config) {
    int wybor;
    do {
        std::cout << "\n=== KONFIGURACJA GENERATORA ===\n";
        std::cout << "1. Ustaw wartosc stala\n";
        std::cout << "2. Dodaj dekorator sinusoidalny\n";
        std::cout << "3. Dodaj dekorator prostokatny\n";
        std::cout << "4. Dodaj dekorator trojkatny\n";
        std::cout << "5. Dodaj szum bialy\n";
        std::cout << "6. Dodaj nasycenie\n";
        std::cout << "7. Wyczysc generator\n";
        std::cout << "8. Powrot\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> wybor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Get current generator as unique_ptr
        std::unique_ptr<Sygnal> current = config.pobierzGenerator()
            ? config.pobierzGenerator()->klonuj()
            : nullptr;

        switch (wybor) {
        case 1: {
            double wartosc;
            std::cout << "Podaj wartosc stala: ";
            std::cin >> wartosc;
            config.ustawGenerator(std::make_unique<SygnalStaly>(wartosc));
            break;
        }
        case 2: {
            double amplituda, czestotliwosc;
            std::cout << "Podaj amplitude: ";
            std::cin >> amplituda;
            std::cout << "Podaj czestotliwosc: ";
            std::cin >> czestotliwosc;
            config.ustawGenerator(
                std::make_unique<DekoratorSinus>(
                    current ? std::move(current) : std::make_unique<SygnalStaly>(0.0),
                    amplituda,
                    czestotliwosc)
            );
            break;
        }
        case 3: {
            double amplituda, wypelnienie;
            int okres;
            std::cout << "Podaj amplitude: ";
            std::cin >> amplituda;
            std::cout << "Podaj okres: ";
            std::cin >> okres;
            std::cout << "Podaj wypelnienie (0-1): ";
            std::cin >> wypelnienie;
            config.ustawGenerator(
                std::make_unique<DekoratorProstokat>(
                    current ? std::move(current) : std::make_unique<SygnalStaly>(0.0),
                    amplituda,
                    okres,
                    wypelnienie)
            );
            break;
        }
        case 4: {
            double amplituda, wypelnienie;
            int okres;
            std::cout << "Podaj amplitude: ";
            std::cin >> amplituda;
            std::cout << "Podaj okres: ";
            std::cin >> okres;
            std::cout << "Podaj wypelnienie (0-1): ";
            std::cin >> wypelnienie;
            config.ustawGenerator(
                std::make_unique<DekoratorTrojkat>(
                    current ? std::move(current) : std::make_unique<SygnalStaly>(0.0),
                    amplituda,
                    okres,
                    wypelnienie)
            );
            break;
        }
        case 5: {
            double odchylenie;
            std::cout << "Podaj odchylenie standardowe: ";
            std::cin >> odchylenie;
            config.ustawGenerator(
                std::make_unique<DekoratorSzumBialy>(
                    current ? std::move(current) : std::make_unique<SygnalStaly>(0.0),
                    odchylenie)
            );
            break;
        }
        case 6: {
            double max_wartosc;
            std::cout << "Podaj maksymalna wartosc: ";
            std::cin >> max_wartosc;
            config.ustawGenerator(
                std::make_unique<DekoratorNasycenie>(
                    current ? std::move(current) : std::make_unique<SygnalStaly>(0.0),
                    max_wartosc)
            );
            break;
        }
        case 7: {
            config.ustawGenerator(nullptr);
            break;
        }
        case 8:
            return;
        default:
            std::cout << "Nieprawidlowy wybor.\n";
        }
    } while (true);
}

void uruchomGenerator(Konfiguracja& config) {
    auto generator = config.pobierzGenerator();
    if (!generator) {
        std::cout << "Brak skonfigurowanego generatora!\n";
        return;
    }

    // Create output directory
    fs::create_directory("generator_files");

    int kroki = config.pobierzLiczbeKrokow();
    std::string filename = "generator_files/generator.csv";
    std::ofstream log(filename);

    if (!log) {
        std::cerr << "Blad: Nie mozna otworzyc pliku " << filename << "\n";
        return;
    }

    log << "t;wartosc\n";

    for (int t = 0; t < kroki; ++t) {
        double wartosc = generator->symuluj(t);
        log << t << ";" << wartosc << "\n";
    }
    std::cout << "Dane generatora zapisano do " << filename << "\n";
}

void uruchomSymulacjePetli(Konfiguracja& config) {
    auto petla = config.pobierzPetle();
    auto generator = config.pobierzGenerator();
    if (!petla || !generator) {
        std::cout << "Brak petli lub generatora!\n";
        return;
    }

    // Create output directory
    fs::create_directory("petla_symulacja_files");

    int kroki = config.pobierzLiczbeKrokow();
    std::string filename = "petla_symulacja_files/symulacja_petli.csv";
    std::ofstream log(filename);

    if (!log) {
        std::cerr << "Blad: Nie mozna otworzyc pliku " << filename << "\n";
        return;
    }

    log << "t;zadana;wyjscie\n";

    for (int t = 0; t < kroki; ++t) {
        double zadana = generator->symuluj(t);
        double wyjscie = petla->symuluj(zadana);
        log << t << ";" << zadana << ";" << wyjscie << "\n";
    }
    std::cout << "Symulacja petli zakonczona. Dane w " << filename << "\n";
}

void uruchomPelnaSymulacje(Konfiguracja& config) {
    auto generator = config.pobierzGenerator();
    if (!generator) {
        std::cout << "Brak generatora!\n";
        return;
    }


    // Create output directory
    fs::create_directory("pelna_symulacja_files");

    // Ustawienia domyœlne dla modelu i regulatora
    std::vector<double> a = { 0.4, -0.25 };
    std::vector<double> b = { 0.8, 0.1 };
	unsigned k = 1; // Delay in discrete time steps
	double kreg = 1.2, Ti = 8.0, Td = 0.4; // Default gain for PID regulator

    std::cout << "Konfiguracja modelu\n";
    std::cout << "Podaj wartosc a[0]\n";
    std::cin >> a[0];

    std::cout << "\nPodaj wartosc a[1]\n";
    std::cin >> a[1];

    std::cout << "\nPodaj wartosc b[0]\n";
    std::cin >> b[0];

    std::cout << "\nPodaj wartosc b[1]\n";
    std::cin >> b[1];

    std::cout << "Podaj wartosc opoznienia\n";
 std::cin >> k;

    std::cout << "Konfiguracja regulatora\n";
    std::cout << "Podaj wartosc k\n";
    std::cin >> kreg;
    std::cout << "\nPodaj wartosc Ti\n";
    std::cin >> Ti;
    std::cout << "\nPodaj wartosc Td\n";
    std::cin >> Td;

    ModelARX model(a, b, k, 0.0);
    RegulatorPID regulator(kreg, Ti, Td);


    int kroki = config.pobierzLiczbeKrokow();
    double wyjscie = 0.0;

    std::string filename = "pelna_symulacja_files/pelna_symulacja.csv";
    std::ofstream log(filename);

    if (!log) {
        std::cerr << "Blad: Nie mozna otworzyc pliku " << filename << "\n";
        return;
    }

    log << "t;wartosc_zadana;wyjscie;sterowanie\n";

    for (int t = 0; t < kroki; ++t) {
        double wartosc_zadana = generator->symuluj(t);
        double uchyb = wartosc_zadana - wyjscie;
        double sterowanie = regulator.symuluj(uchyb);
        wyjscie = model.symuluj(sterowanie);

        log << t << ";" << wartosc_zadana << ";" << wyjscie << ";" << sterowanie << "\n";
    }
    std::cout << "Pelna symulacja zakonczona. Dane w " << filename << "\n";
}

int main(int argc, char* argv[]) {
    if (argc > 1 && std::string(argv[1]) == "test") {
        std::cout << "=== TRYB TESTOWY ===\n";
        uruchomTesty();
        return 0;
    }

    // Create main output directory
    fs::create_directory("wyniki_symulacji");

    Konfiguracja config;
    int wybor;

    do {
        wyswietlMenu();
        std::cin >> wybor;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (wybor) {
            case 1: {
                std::string plik;
                std::cout << "Podaj nazwe pliku: ";
                std::getline(std::cin, plik);
                config.wczytaj(plik);
                break;
            }
            case 2: {
                std::string plik;
                std::cout << "Podaj nazwe pliku: ";
                std::getline(std::cin, plik);
                config.zapisz(plik);
                break;
            }
            case 3:
                modyfikujParametry(config);
                break;
            case 4:
                konfigurujGenerator(config);
                break;
            case 5:
                uruchomGenerator(config);
                break;
            case 6:
                uruchomSymulacjePetli(config);
                break;
            case 7:
                uruchomPelnaSymulacje(config);
                break;
            case 8:
                std::cout << "Koniec programu.\n";
                break;
            default:
                std::cout << "Nieprawidlowa opcja.\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Blad: " << e.what() << "\n";
        }
    } while (wybor != 8);

    return 0;
}