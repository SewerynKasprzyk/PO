#include "PetlaUAR.h"
#include "RegulatorPID.h"
#include "ModelARX.h"
#include "ObiektStatyczny.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

double PetlaUAR::symuluj(double x) {
    double wejscie = x;
    if (zamknieta && !obiekty.empty())
        wejscie = x - poprzednieWyjscie;

    for (auto& ob : obiekty)
        wejscie = ob->symuluj(wejscie);

    if (zamknieta)
        poprzednieWyjscie = wejscie;

    return wejscie;
}

void PetlaUAR::ustawZamknieta(bool stan) {
    zamknieta = stan;
}

void PetlaUAR::dodajKomponent(unique_ptr<ObiektSISO> obiekt, const string& typ) {
    obiekty.push_back(move(obiekt));
    typy.push_back(typ);
}

void PetlaUAR::dodajKomponentNaPozycji(unique_ptr<ObiektSISO> obiekt, size_t index, const string& typ) {
    if (index > obiekty.size()) throw out_of_range("Niepoprawny indeks");
    obiekty.insert(obiekty.begin() + index, move(obiekt));
    typy.insert(typy.begin() + index, typ);
}

void PetlaUAR::usunKomponent(size_t index) {
    if (index >= obiekty.size()) throw out_of_range("Niepoprawny indeks");
    obiekty.erase(obiekty.begin() + index);
    typy.erase(typy.begin() + index);
}

void PetlaUAR::serializuj(const string& nazwaPliku) const {
    ofstream out(nazwaPliku);
    if (!out) {
        cerr << "Nie mozna otworzyc pliku do zapisu." << endl;
        return;
    }

    out << "typ=PetlaUAR\n";
    out << "zamknieta=" << zamknieta << "\n";
    out << "komponenty=" << obiekty.size() << "\n";

    for (size_t i = 0; i < obiekty.size(); ++i) {
        string filename = "komponent" + to_string(i) + ".txt";
        out << "plik" << i << "=" << filename << "\n";
        out << "typ" << i << "=" << typy[i] << "\n";

        if (typy[i] == "ObiektStatyczny")
            dynamic_cast<ObiektStatyczny*>(obiekty[i].get())->serializuj(filename);
        else if (typy[i] == "ModelARX")
            dynamic_cast<ModelARX*>(obiekty[i].get())->serializuj(filename);
        else if (typy[i] == "RegulatorPID")
            dynamic_cast<RegulatorPID*>(obiekty[i].get())->serializuj(filename);
        else
            cerr << "Nieznany typ komponentu: " << typy[i] << endl;
    }
}

void PetlaUAR::deserializuj(const string& nazwaPliku) {
    ifstream in(nazwaPliku);
    if (!in) {
        cerr << "Nie mozna otworzyc pliku do odczytu: " << nazwaPliku << endl;
        return;
    }

    string line;
    obiekty.clear();
    typy.clear();
    map<size_t, pair<string, string>> components; // index -> (type, file)

    while (getline(in, line)) {
        auto pos = line.find('=');
        if (pos == string::npos) continue;

        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);

        // Handle general properties
        if (key == "typ") {
            // Skip the general type line
            continue;
        }
        else if (key == "zamknieta") {
            zamknieta = (value == "1" || value == "true" || value == "True");
        }
        else if (key == "komponenty") {
            // We'll handle components later
        }
        // Handle component-specific lines
        else if (key.find("typ") == 0 && key.size() > 3) {
            try {
                size_t idx = stoul(key.substr(3));
                components[idx].first = value;
            }
            catch (...) {
                cerr << "Blad parsowania indeksu typu: " << key << endl;
            }
        }
        else if (key.find("plik") == 0 && key.size() > 4) {
            try {
                size_t idx = stoul(key.substr(4));
                components[idx].second = value;
            }
            catch (...) {
                cerr << "Blad parsowania indeksu pliku: " << key << endl;
            }
        }
    }

    // Create components after reading all data
    for (auto& [idx, comp] : components) {
        string typ = comp.first;
        string plik = comp.second;

        try {
            if (typ == "ObiektStatyczny") {
                dodajKomponent(make_unique<ObiektStatyczny>(plik), typ);
            }
            else if (typ == "ModelARX") {
                dodajKomponent(make_unique<ModelARX>(plik), typ);
            }
            else if (typ == "RegulatorPID" || typ == "PID") {
                dodajKomponent(make_unique<RegulatorPID>(plik), "RegulatorPID");
            }
            else {
                cerr << "Nieznany typ komponentu: " << typ << " (pominiêto)" << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Blad tworzenia komponentu " << typ << ": " << e.what() << endl;
        }
    }
}

std::vector<std::string> PetlaUAR::pobierzTypyKomponentow() const {
    return typy;
}
