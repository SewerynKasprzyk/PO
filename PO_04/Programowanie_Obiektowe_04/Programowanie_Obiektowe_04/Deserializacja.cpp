#include "Sygnal.h"
#include "SygnalStaly.h"
#include "DekoratorSinus.h"
#include "DekoratorProstokat.h"
#include "DekoratorTrojkat.h"
#include "DekoratorSzumBialy.h"
#include "DekoratorNasycenie.h"

std::unique_ptr<Sygnal> deserializujSygnal(std::istream& in) {
    std::string typ;
    in >> typ;

    if (typ == "SygnalStaly") {
        double wartosc;
        in >> wartosc;
        return std::make_unique<SygnalStaly>(wartosc);
    }
    else if (typ == "DekoratorSinus") {
        double amp, czest;
        in >> amp >> czest;
        auto komponent = deserializujSygnal(in);
        return std::make_unique<DekoratorSinus>(std::move(komponent), amp, czest);
    }
    else if (typ == "DekoratorProstokat") {
        double amp, wyp;
        int okr;
        in >> amp >> okr >> wyp;
        auto komponent = deserializujSygnal(in);
        return std::make_unique<DekoratorProstokat>(std::move(komponent), amp, okr, wyp);
    }
    else if (typ == "DekoratorTrojkat") {
        double amp, wyp;
        int okr;
        in >> amp >> okr >> wyp;
        auto komponent = deserializujSygnal(in);
        return std::make_unique<DekoratorTrojkat>(std::move(komponent), amp, okr, wyp);
    }
    else if (typ == "DekoratorSzumBialy") {
        double odch;
        in >> odch;
        auto komponent = deserializujSygnal(in);
        return std::make_unique<DekoratorSzumBialy>(std::move(komponent), odch);
    }
    else if (typ == "DekoratorNasycenie") {
        double max;
        in >> max;
        auto komponent = deserializujSygnal(in);
        return std::make_unique<DekoratorNasycenie>(std::move(komponent), max);
    }

    throw std::runtime_error("Nieznany typ sygnalu: " + typ);
}