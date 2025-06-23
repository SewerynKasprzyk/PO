#pragma once
#include "TestyKonfiguracji.h"
#include "Konfiguracja.h"
#include "RegulatorPID.h"
#include "ObiektStatyczny.h"
#include "SygnalStaly.h"  // Include concrete signal type
#include <cassert>
#include <fstream>
#include <iostream>


void testZapisuIOdczytu() {
    Konfiguracja config;
    config.ustawLiczbeKrokow(200);
    config.ustawZamknieta(false);

    auto petla = std::make_unique<PetlaUAR>();
    // Use "RegulatorPID" instead of "PID"
    petla->dodajKomponent(std::make_unique<RegulatorPID>(1.0), "RegulatorPID");
    config.ustawPetle(std::move(petla));

    config.ustawGenerator(std::make_unique<SygnalStaly>(5.0));

    config.zapisz("test_config.txt");

    Konfiguracja config2;
    config2.wczytaj("test_config.txt");

    assert(config2.pobierzLiczbeKrokow() == 200);
    assert(!config2.czyZamknieta());
    assert(config2.pobierzPetle()->pobierzTypyKomponentow().size() == 1);
    assert(config2.pobierzGenerator() != nullptr);

    // Additional check for signal value
    assert(config2.pobierzGenerator()->symuluj(0) == 5.0);

    std::cout << "testZapisuIOdczytu: OK\n";
}


void testZmianyParametrow() {
    Konfiguracja config;
    config.ustawLiczbeKrokow(50);
    config.ustawZamknieta(true);

    assert(config.pobierzLiczbeKrokow() == 50);
    assert(config.czyZamknieta());
    std::cout << "testZmianyParametrow: OK\n";
}

void testPelnejSymulacji() {
    Konfiguracja config;
    auto petla = std::make_unique<PetlaUAR>();
    petla->dodajKomponent(std::make_unique<RegulatorPID>(0.5, 0.1, 0.01), "PID");
    petla->dodajKomponent(std::make_unique<ObiektStatyczny>(-1, 1), "Obiekt");
    config.ustawPetle(std::move(petla));
    config.ustawGenerator(std::make_unique<SygnalStaly>(0.5));
    config.ustawLiczbeKrokow(10);

    for (int t = 0; t < config.pobierzLiczbeKrokow(); ++t) {
        double zadana = config.pobierzGenerator()->symuluj(t);
        double wyjscie = config.pobierzPetle()->symuluj(zadana);
        assert(wyjscie >= -1 && wyjscie <= 1);
    }
    std::cout << "testPelnejSymulacji: OK\n";
}

void uruchomTesty() {
    testZapisuIOdczytu();
    testZmianyParametrow();
    testPelnejSymulacji();
    std::cout << "Wszystkie testy zakonczone pomyslnie.\n";
}