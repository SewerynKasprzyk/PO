//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <iomanip>
//
//// DEBUG | MAIN | GENERATOR | KOMPOZYT
//#define KOMPOZYT
//
//#include "RegulatorPID.h"
//
//#ifdef DEBUG
//
////Funkcje pomocnicze dla testów:
//
//static void raportBleduSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
//{
//	constexpr size_t PREC = 3;
//	std::cerr << std::fixed << std::setprecision(PREC);
//	std::cerr << "  Spodziewany:\t";
//	for (auto& el : spodz)
//		std::cerr << el << ", ";
//	std::cerr << "\n  Faktyczny:\t";
//	for (auto& el : fakt)
//		std::cerr << el << ", ";
//	std::cerr << std::endl << std::endl;
//}
//
//static bool porownanieSekwencji(std::vector<double>& spodz, std::vector<double>& fakt)
//{
//	constexpr double TOL = 1e-3;	// tolerancja dla porównañ zmiennoprzecinkowych
//	bool result = fakt.size() == spodz.size();
//	for (int i = 0; result && i < fakt.size(); i++)
//		result = fabs(fakt[i] - spodz[i]) < TOL;
//	return result;
//}
//
//static void test_RegulatorP_brakPobudzenia()
//{
//	//Sygnatura testu:
//	std::cerr << "RegP (k = 0.5) -> test zerowego pobudzenia: ";
//	try
//	{
//		// Przygotowanie danych:
//		RegulatorPID instancjaTestowa(0.5);
//		constexpr size_t LICZ_ITER = 30;
//		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu (tu same 0)
//		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy (tu same 0)
//		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy
//
//		// Symulacja modelu:
//
//		for (int i = 0; i < LICZ_ITER; i++)
//			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
//
//		// Walidacja poprawnoœci i raport:
//		if (porownanieSekwencji(spodzSygWy, faktSygWy))
//			std::cerr << "OK!\n";
//		else
//		{
//			std::cerr << "FAIL!\n";
//			raportBleduSekwencji(spodzSygWy, faktSygWy);
//		}
//	}
//	catch (...)
//	{
//		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
//	}
//}
//
//static void test_RegulatorP_skokJednostkowy()
//{
//	//Sygnatura testu:
//	std::cerr << "RegP (k = 0.5) -> test skoku jednostkowego: ";
//
//	try
//	{
//		// Przygotowanie danych:
//		RegulatorPID instancjaTestowa(0.5);
//		constexpr size_t LICZ_ITER = 30;
//		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
//		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
//		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy
//
//		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
//		for (int i = 0; i < LICZ_ITER; i++)
//			sygWe[i] = !!i;
//		spodzSygWy = { 0.0, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5 };
//
//		// Symulacja modelu:
//		for (int i = 0; i < LICZ_ITER; i++)
//			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
//
//		// Walidacja poprawnoœci i raport:
//		if (porownanieSekwencji(spodzSygWy, faktSygWy))
//			std::cerr << "OK!\n";
//		else
//		{
//			std::cerr << "FAIL!\n";
//			raportBleduSekwencji(spodzSygWy, faktSygWy);
//		}
//	}
//	catch (...)
//	{
//		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
//	}
//}
//
//static void test_RegulatorPI_skokJednostkowy_1()
//{
//	//Sygnatura testu:
//	std::cerr << "RegPI (k = 0.5, TI = 1.0) -> test skoku jednostkowego nr 1: ";
//
//	try
//	{
//		// Przygotowanie danych:
//		RegulatorPID instancjaTestowa(0.5, 1.0);
//		constexpr size_t LICZ_ITER = 30;
//		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
//		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
//		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy
//
//		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
//		for (int i = 0; i < LICZ_ITER; i++)
//			sygWe[i] = !!i;
//		spodzSygWy = { 0, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5, 10.5, 11.5, 12.5, 13.5, 14.5, 15.5, 16.5, 17.5, 18.5, 19.5, 20.5, 21.5, 22.5, 23.5, 24.5, 25.5, 26.5, 27.5, 28.5, 29.5 };
//
//		// Symulacja modelu:
//		for (int i = 0; i < LICZ_ITER; i++)
//			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
//
//		// Walidacja poprawnoœci i raport:
//		if (porownanieSekwencji(spodzSygWy, faktSygWy))
//			std::cerr << "OK!\n";
//		else
//		{
//			std::cerr << "FAIL!\n";
//			raportBleduSekwencji(spodzSygWy, faktSygWy);
//		}
//	}
//	catch (...)
//	{
//		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
//	}
//}
//
//static void test_RegulatorPI_skokJednostkowy_2()
//{
//	//Sygnatura testu:
//	std::cerr << "RegPI (k = 0.5, TI = 10.0) -> test skoku jednostkowego nr 2: ";
//
//	try
//	{
//		// Przygotowanie danych:
//		RegulatorPID instancjaTestowa(0.5, 10.0);
//		constexpr size_t LICZ_ITER = 30;
//		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
//		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
//		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy
//
//		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
//		for (int i = 0; i < LICZ_ITER; i++)
//			sygWe[i] = !!i;
//		spodzSygWy = { 0, 0.6, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };
//
//		// Symulacja modelu:
//		for (int i = 0; i < LICZ_ITER; i++)
//			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
//
//		// Walidacja poprawnoœci i raport:
//		if (porownanieSekwencji(spodzSygWy, faktSygWy))
//			std::cerr << "OK!\n";
//		else
//		{
//			std::cerr << "FAIL!\n";
//			raportBleduSekwencji(spodzSygWy, faktSygWy);
//		}
//	}
//	catch (...)
//	{
//		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
//	}
//}
//
//static void test_RegulatorPID_skokJednostkowy()
//{
//	//Sygnatura testu:
//	std::cerr << "RegPID (k = 0.5, TI = 10.0, TD = 0.2) -> test skoku jednostkowego: ";
//
//	try
//	{
//		// Przygotowanie danych:
//		RegulatorPID instancjaTestowa(0.5, 10.0, 0.2);
//		constexpr size_t LICZ_ITER = 30;
//		std::vector<double> sygWe(LICZ_ITER);      // pobudzenie modelu 
//		std::vector<double> spodzSygWy(LICZ_ITER); // spodziewana sekwencja wy 
//		std::vector<double> faktSygWy(LICZ_ITER);  // faktyczna sekwencja wy
//
//		// Symulacja skoku jednostkowego w chwili 1. (!!i - daje 1 dla i != 0);
//		for (int i = 0; i < LICZ_ITER; i++)
//			sygWe[i] = !!i;
//		spodzSygWy = { 0, 0.8, 0.7, 0.8, 0.9, 1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3, 3.1, 3.2, 3.3, 3.4 };
//
//		// Symulacja modelu:
//		for (int i = 0; i < LICZ_ITER; i++)
//			faktSygWy[i] = instancjaTestowa.symuluj(sygWe[i]);
//
//		// Walidacja poprawnoœci i raport:
//		if (porownanieSekwencji(spodzSygWy, faktSygWy))
//			std::cerr << "OK!\n";
//		else
//		{
//			std::cerr << "FAIL!\n";
//			raportBleduSekwencji(spodzSygWy, faktSygWy);
//		}
//	}
//	catch (...)
//	{
//		std::cerr << "INTERUPTED! (niespodziwany wyjatek)\n";
//	}
//}
//
//using namespace std;
//
//int main()
//{
//	test_RegulatorP_brakPobudzenia();
//	test_RegulatorP_skokJednostkowy();
//	test_RegulatorPI_skokJednostkowy_1();
//	test_RegulatorPI_skokJednostkowy_2();
//	test_RegulatorPID_skokJednostkowy();
//
//}
//
//#endif
//
//#ifdef MAIN
//#include "ModelARX.h"
//#include "DekoratorSinus.h"
//#include "DekoratorProstokat.h"
//#include "DekoratorTrojkat.h"
//#include "DekoratorSzumBialy.h"
//#include "DekoratorNasycenie.h"
//#include "SygnalStaly.h"
//#include <memory>
//using namespace std;
//
//int main() {
//	// 1. Konfiguracja generatora jako wartoœci zadanej
//	unique_ptr<Sygnal> generator = make_unique<SygnalStaly>(1.0);       // wartoœæ bazowa = 1.0
//	generator = make_unique<DekoratorSinus>(move(generator), 0.5, 0.2);     // sinus 0.2 Hz
//	generator = make_unique<DekoratorProstokat>(move(generator), 0.3, 30, 0.5); // prostok¹t
//	generator = make_unique<DekoratorNasycenie>(move(generator), 1.5);       // ograniczenie amplitudy
//
//	// 2. Inicjalizacja modelu i regulatora
//	vector<double> a = { 0.4, -0.25 };  // wspó³czynniki AR
//	vector<double> b = { 0.8, 0.1 };    // wspó³czynniki X
//	ModelARX model(a, b, 1, 0.0);     // k=1, bez dodatkowych zak³óceñ
//	RegulatorPID regulator(1.2, 8.0, 0.4); // K=1.2, Ti=8, Td=0.4
//
//	// 3. Symulacja uk³adu sterowania
//	const int KROKI = 200;
//	double wyjscie = 0.0;
//
//	ofstream log("symulacja.csv");
//	log << "t;wartosc_zadana;wyjscie;sterowanie\n";
//
//	for (int t = 0; t < KROKI; ++t) {
//		// Generuj wartoœæ zadan¹ z generatora
//		double wartosc_zadana = generator->symuluj(t);
//
//		// Oblicz uchyb
//		double uchyb = wartosc_zadana - wyjscie;
//
//		// Oblicz sterowanie PID
//		double sterowanie = regulator.symuluj(uchyb);
//
//		// Symuluj model ARX (tylko sterowanie, bez dodatkowych zak³óceñ)
//		wyjscie = model.symuluj(sterowanie);
//
//		// Zapisz dane
//		log << t << ";" << wartosc_zadana << ";" << wyjscie << ";" << sterowanie << "\n";
//	}
//
//	// 4. Serializacja wyników
//	model.serializuj("model_po_symulacji.txt");
//	cout << "Symulacja zakonczona. Wyniki w pliku symulacja_log.csv\n";
//
//	return 0;
//}
//#endif
//
//#ifdef GENERATOR
//#include "DekoratorSinus.h"
//#include "DekoratorProstokat.h"
//#include "DekoratorNasycenie.h"
//#include "SygnalStaly.h"
//#include <memory>
//using namespace std;
//
//int main() {
//	// Konfiguracja generatora
//	unique_ptr<Sygnal> generator = make_unique<SygnalStaly>(1.0);       // wartoœæ bazowa
//	generator = make_unique<DekoratorSinus>(move(generator), 0.5, 0.2);     // sinus
//	generator = make_unique<DekoratorProstokat>(move(generator), 0.3, 30, 0.5); // prostok¹t
//	generator = make_unique<DekoratorNasycenie>(move(generator), 1.5);       // nasycenie
//
//	// Zapis wyników do pliku
//	ofstream log("generator_only.csv");
//	log << "t;wartosc\n";
//
//	for (int t = 0; t < 100; ++t) {
//		double wartosc = generator->symuluj(t);
//		log << t << ";" << wartosc << "\n";
//	}
//
//	cout << "Dane generatora zapisano do pliku generator_only.csv\n";
//	return 0;
//}
//#endif
//
//#ifdef KOMPOZYT
//
//#include "PetlaUAR.h"
//#include "RegulatorPID.h"
//#include "ModelARX.h"
//#include "ObiektStatyczny.h"
//#include <iostream>
//#include <cmath>
//
//int main() {
//	auto petla = std::make_unique<PetlaUAR>();
//	petla->ustawZamknieta(true);
//
//	petla->dodajKomponent(std::make_unique<RegulatorPID>(1.5, 0.7, 0.2), "RegulatorPID");
//	petla->dodajKomponent(std::make_unique<ObiektStatyczny>(-1.0, 1.0), "ObiektStatyczny");
//	petla->dodajKomponent(std::make_unique<ModelARX>(std::vector<double>{0.5, -0.2}, std::vector<double>{1.0}, 1, 0.0), "ModelARX");
//
//	for (int t = 0; t < 20; ++t) {
//		double zadana = sin(0.1 * t);
//		double y = petla->symuluj(zadana);
//		std::cout << "t=" << t << " zadana=" << zadana << " y=" << y << std::endl;
//	}
//
//	petla->serializuj("petla.txt");
//
//	auto wczytanaPetla = std::make_unique<PetlaUAR>();
//	wczytanaPetla->deserializuj("petla.txt");
//
//	return 0;
//}
//#endif