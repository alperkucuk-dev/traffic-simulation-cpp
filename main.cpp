#include "Simuclient.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include "Fahrrad.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <limits>
#include <cmath>
#include "Weg.h"
#include "vertagt_liste.h"
#include <random>
#include "Kreuzung.h"

void vAufgabe_1() {
	// Statische Objekte
	Fahrzeug car;
	Fahrzeug bike;

	// Dynamische Objekte
	Fahrzeug* dynamicCar = new Fahrzeug("Dynamisches Auto");
	delete dynamicCar;
	Fahrzeug* dynamicBike = new Fahrzeug("Dynamisches Fahrrad");
	delete dynamicBike;

	auto sharedCar = std::make_shared<Fahrzeug>(" Shared Car ");		//Shared Pointer
	auto sharedBike = std::make_shared<Fahrzeug>(" Shared Bike");
	std::cout << "Anzahl der Referenzen: " << sharedCar.use_count() << std::endl;

	auto anotherSharedCar = sharedCar;
	std::cout << "Anzahl der Referenzen: " << sharedCar.use_count() << std::endl;

	auto uniqueCar = std::make_unique<Fahrzeug>("Unique Car");		//Unique pointer
	auto uniqueBike = std::make_unique<Fahrzeug>("Unique Bike");

	std::vector<std::unique_ptr <Fahrzeug>> vehicleVector; // Verwendung unique Pointer mit Vektor
	vehicleVector.push_back(std::move(uniqueCar));
	vehicleVector.push_back(std::move(uniqueBike));

	vehicleVector.clear(); // Vektor löschen

	std::vector<std::shared_ptr<Fahrzeug>>sharedVehicleVector;
	auto sharedTruck = std::make_shared<Fahrzeug>("Shared Truck");
	sharedVehicleVector.push_back(sharedTruck);

	auto anotherSharedTruck = std::make_shared<Fahrzeug>("Another Shared Truck");
	sharedVehicleVector.push_back(std::move(anotherSharedTruck));

	std::cout << "Anzahl der Referenzen: " << sharedTruck.use_count() << std::endl;
	std::cout << "Anzahl der Referenzen: " << sharedVehicleVector.back().use_count() << std::endl;

	sharedVehicleVector.clear();

}

void vAufgabe_1a() {
	std::vector<std::unique_ptr<Fahrzeug>> fahrzeuge;
	std::string name;
	double maxGeschwindigkeit;

	for (int i = 0; i < 3; i++) {		// Empfang von 3 Fahrzeuginformationen vom Benutzer
		std::cout << "Bitte geben Sie den Namen des Fahrzeugs ein: " << std::endl;
		std::cin >> name;
		std::cout << "Bitte geben Sie die Maximum Geschwindigkeit des Fahrzeugs ein: " << std::endl;
		std::cin >> maxGeschwindigkeit;

		fahrzeuge.push_back(std::make_unique<Fahrzeug>(name, maxGeschwindigkeit));
	}
	//Simulation
	double dZeittakt = 0.5;		// Zeitschritt (z.B. eine halbe Stunde)
	double dSimulationsdauer = 3.0;		// Dauer der Simulation (z.B. 3 Stunden)
	dGlobaleZeit = 0.0;		// Globale Zeit zurücksetzen



	while (dGlobaleZeit < dSimulationsdauer) {
		dGlobaleZeit += dZeittakt;

		std::cout << "Zeit: " << dGlobaleZeit << " Stunde" << std::endl;
		Fahrzeug::vKopf();
		for (auto& fahrzeug : fahrzeuge) {
			fahrzeug->vSimulieren();
			std::cout << *fahrzeug << std::endl;
		}
		std::cout << std::endl;

	}

}

void vAufgabe_2() {
	// Eingaben von der Konsole
	int pkwCount = 0, fahrradCount = 0;
	std::cout << "Geben Sie die Anzahl der PKW: ";
	std::cin >> pkwCount;
	std::cout << "Geben Sie die Anzahl der Fahrrad: ";
	std::cin >> fahrradCount;

	std::vector<std::unique_ptr<Fahrzeug>>fahrzeuge;

	for (int i = 0; i < pkwCount; i++) {		// Hinzufügen von PKW-Objekten
		std::string name = "PKW" + std::to_string(i + 1);
		fahrzeuge.push_back(std::make_unique<PKW>(name, 120, 8.0, 50.0));
	}
	for (int i = 0; i < fahrradCount; i++) {	// Hinzufügen von Fahrrad-Objekten
		std::string name = "Bike" + std::to_string(i + 1);
		fahrzeuge.push_back(std::make_unique<Fahrrad>(name, 25));
	}
	double simStep = 0.5;		// Zeitschritt
	constexpr double epsilon = 1e-5;

	while (dGlobaleZeit <= 5) {			// Bis zu 5 Stunden Simulation
		std::cout << "Zeit:" << dGlobaleZeit << "Stunde\n";
		Fahrzeug::vKopf();

		// Führen Sie die Simulation für jedes Fahrzeug durch
		for (auto& fahrzeug : fahrzeuge) {
			fahrzeug->vSimulieren();
			std::cout << *fahrzeug << std::endl;
		}
		if (std::fabs(dGlobaleZeit - 3) < epsilon) {
			for (auto& fahrzeug : fahrzeuge) {
				if (dynamic_cast<PKW*>(fahrzeug.get())) {
					dynamic_cast<PKW*>(fahrzeug.get())->dTanken();
				}
			}
		}
		std::cout << std::string(80, '-') << std::endl;
		dGlobaleZeit += simStep;


	}
}

void vAufgabe_3() {
	Fahrzeug f1("PKW", 120);
	Fahrzeug f2("Fahrrad", 30);

	f1.vSimulieren();
	f2.vSimulieren();

	// < Operator test
	if (f1 < f2) {
		std::cout << f1.getName() << " legte weniger Strecke zurück." << std::endl;
	}
	else {
		std::cout << f2.getName() << " legte weniger Strecke zurück." << std::endl;
	}

	// Test des Zuweisungsoperators
	Fahrzeug f3("Neufahrzeug", 80);
	f3 = f1; // Aufrufen des Zuweisungsoperators
	std::cout << f3.getName() << " kopiert: " << f3 << std::endl;

	// Der folgende Code gibt einen Fehler, weil der Kopierkonstruktor verboten ist:
	// Fahrzeug f4 = f1; // Das ist verboten!
}

void vAufgabe_4() {
	// Yeni Weg nesnesi oluşturma
	Weg weg1("Landstrase", 100.0, Tempolimit::Landstrase);

	// Weg bilgilerini ekrana yazdırma
	std::cout << weg1 << std::endl;

	// Araç ekleme ve simülasyon testi
	weg1.vAnnahme(std::make_unique<Fahrzeug>("Auto1", 80.0));
	weg1.vAnnahme(std::make_unique<Fahrzeug>("Auto2", 100.0));

	// Simülasyonu çalıştırma
	weg1.vSimulieren();

	// Son durum bilgilerini yazdırma
	std::cout << weg1 << std::endl;
}

void vAufgabe_5() {
	// Bir yol oluşturuyoruz
	Weg weg1("Landstrase", 1000, Tempolimit::Landstrase);

	// Araçlar oluşturuyoruz
	auto pkw1 = std::make_unique<PKW>("Auto1", 120, 8.5);
	auto pkw2 = std::make_unique<PKW>("Auto2", 100, 7.0);
	auto fahrrad = std::make_unique<Fahrrad>("Bike1", 25);

	// Araçları yola ekliyoruz
	weg1.vAnnahme(std::move(pkw1));
	weg1.vAnnahme(std::move(pkw2));
	weg1.vAnnahme(std::move(fahrrad));


	// Yolu simüle ediyoruz
	for (int i = 0; i < 10; ++i) {
		dGlobaleZeit += 1.0; // Zamanı artırıyoruz
		weg1.vSimulieren();
		weg1.vAusgebenfurFahrzeuge(std::cout); // Yolu konsola yazdırıyoruz
		std::cout << "-----------------------------------" << std::endl;
	}
}

void vAufgabe_6() {
	// Weg nesnesini oluştur
	Weg weg1("Hauptstraße", 1000.0, Tempolimit::Landstrase);

	// 3 farklı Fahrzeug nesnesi oluştur
	auto fzg1 = std::make_unique<PKW>("Auto1", 120.0, 8.5, 50.0);
	auto fzg2 = std::make_unique<Fahrrad>("Bike1", 25.0);
	auto fzg3 = std::make_unique<PKW>("Auto2", 150.0, 9.0, 60.0);

	// Araçları Weg'e kaydet
	weg1.vAnnahme(std::move(fzg1));
	weg1.vAnnahme(std::move(fzg2));
	weg1.vAnnahme(std::move(fzg3));

	weg1.vSimulieren();

	std::cout << std::endl << std::endl;
	weg1.vKopf();
	weg1.vAusgeben(std::cout);
	std::cout << std::endl << std::endl;


	// Weg simülasyonunu başlat
	std::cout << "Weg Simülasyonu Başlatılıyor...\n";
	for (int i = 0; i < 10; i++) {  // 10 adım simülasyon yap
		std::cout << "Simülasyon Adımı: " << i + 1 << "\n";
		weg1.vSimulieren();
		std::cout << std::endl;
		Fahrzeug::vKopf();
		// Weg içindeki araçların bilgilerini yazdır
		weg1.vAusgebenfurFahrzeuge(std::cout);

		dGlobaleZeit += 1.0;
		std::cout << "-----------------------------------\n";
	}
}

void vAufgabe_6_mitGUI() {
    // Weg nesnesini olu tur
	bInitialisiereGrafik(2000, 2000);
	vSetzeZeit(0);
    Weg weg1("Weg1", 500.0, Tempolimit::Autobahn);
    Weg weg2("Weg2", 500.0, Tempolimit::Autobahn);

    std::string name1_Anfang = "Weg1";
    std::string name1_Ende = "Weg2";
    int Laenge1 = 500;
    int AnzahlKoord1 = 2;
    int Koordinaten1[] = {100, 200, 700, 200};
    bZeichneStrasse(name1_Anfang, name1_Ende, Laenge1, AnzahlKoord1, Koordinaten1);

    auto fzg1 = std::make_unique<PKW>("Ferrari", 50, 8.5, 500);
    auto fzg2 = std::make_unique<PKW>("Lamborghini", 20, 8.5, 500);

    weg1.vAnnahme(std::move(fzg1));
    weg2.vAnnahme(std::move(fzg2));

    bZeichnePKW("Ferrari", "Weg1", 0.0, 50, 500);
    bZeichnePKW("Lamborghini", "Weg2", 0.0, 20, 500);

    for (int i = 0; i < 11; i++) {  // 10 ad m sim lasyon yap
    	weg1.vSimulieren();
        weg2.vSimulieren();
        dGlobaleZeit += 1.0;
        vSetzeZeit(dGlobaleZeit);
        weg1.vFahrzeugVisualisiert();
        weg2.vFahrzeugVisualisiert();
        vSleep(2000);
        }
}

void vAufgabe_6a() {
	vertagt::VListe<int> list;
	for (int i = 0; i < 10; i++) {
		int val = rand() % 10 + 1;
		list.push_back(val);
	}

	list.vAktualisieren();

	auto iter = list.begin();
	while (iter != list.end()) {
		if (*iter > 5) {
			list.erase(iter++);
		}
		else {
			++iter;
		}
	}

	list.vAktualisieren();

	std::cout << "Liste nach der Schleife: " << std::endl;

	for (int el : list) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}

void vAufgabe_7() {
	bInitialisiereGrafik(1200, 1000);

	//Kreuzungen
	std::shared_ptr<Kreuzung>kr1p = std::make_shared<Kreuzung>("Kr1", 1000);
	bZeichneKreuzung(680, 40);

	std::shared_ptr<Kreuzung>kr2p = std::make_shared<Kreuzung>("Kr2", 1000);
	bZeichneKreuzung(680, 300);

	std::shared_ptr<Kreuzung>kr3p = std::make_shared<Kreuzung>("Kr3", 1000);
	bZeichneKreuzung(680, 570);

	std::shared_ptr<Kreuzung>kr4p = std::make_shared<Kreuzung>("Kr4", 1000);
	bZeichneKreuzung(320, 300);

 	//Strasse 1
	kr1p->vVerbinde("W12", "W21", 40, kr1p, kr2p, Tempolimit::Innersorts);
	int Koord1[] = { 680, 40, 680, 300 };
	bZeichneStrasse("W12", "W21", 40, 2, Koord1);

	//Strasse 2
	kr2p->vVerbinde("W23a", "W32a", 115, kr2p, kr3p, Tempolimit::Autobahn);
	int Koord2[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };
	bZeichneStrasse("W23a", "W32a", 40, 6, Koord2);

	//Strasse 3
	kr3p->vVerbinde("W23b", "W32b", 40, kr2p, kr3p, Tempolimit::Innersorts);
	int Koord3[] = { 680, 300, 680, 570 };
	bZeichneStrasse("W23b", "W32b", 40, 2, Koord3);

	//Strasse 4
	kr4p->vVerbinde("W24", "W42", 40, kr2p, kr4p, Tempolimit::Innersorts);
	int Koord4[] = { 680, 300, 320, 300 };
	bZeichneStrasse("W24", "W42", 40, 2, Koord4);

	//Strasse 5
	kr3p->vVerbinde("W34", "W43", 85, kr3p, kr4p, Tempolimit::Autobahn);
	int Koord5[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };
	bZeichneStrasse("W34", "W43", 85, 5, Koord5);

	//Strasse 6
	kr4p->vVerbinde("W44a", "W44b", 130, kr4p, kr4p, Tempolimit::Landstrase);
	int Koord6[] = { 320, 300, 170, 300, 70, 250, 80, 90, 200, 60, 320, 150, 320, 300 };
	bZeichneStrasse("W44a", "W44b", 85, 7, Koord6);


	std::unique_ptr<PKW> f1 = std::make_unique<PKW>("BMW", 70, 12);
	std::unique_ptr<PKW> f2 = std::make_unique<PKW>("Audi", 40, 10);
	std::unique_ptr<PKW> f3 = std::make_unique<PKW>("Mercedes-Benz", 50, 1);
	std::unique_ptr<PKW> f4 = std::make_unique<PKW>("Opel", 80, 8);
	std::unique_ptr<Fahrrad> f5 = std::make_unique<Fahrrad>("BMX", 25);


	kr4p->vAnnahme(move(f1), 1);
	kr2p->vAnnahme(move(f2), 1);
	kr1p->vAnnahme(move(f3), 1);
	kr1p->vAnnahme(move(f4), 1);
	kr1p->vAnnahme(move(f5), 1);


	dGlobaleZeit = 0;
	while (true) {
		std::cout << "Zeit:  " << dGlobaleZeit << std::endl;
		vSetzeZeit(dGlobaleZeit);
		kr1p->vSimulieren();
		kr2p->vSimulieren();
		kr3p->vSimulieren();
		kr4p->vSimulieren();



		dGlobaleZeit += 0.1;
		std::cout << std::endl;
		vSleep(200);
	}
	vBeendeGrafik();
}


int main() {
	vAufgabe_7();
	return 0;
}


