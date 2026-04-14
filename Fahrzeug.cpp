#pragma once
#include <iostream>
#include "Fahrzeug.h"
#include <iomanip> // für die Formatierung erforderliche Bibliothek
#include <limits>
#include "Fahrzeug.h"
#include "Verhalten.h"
#include "FahrendVerhalten.h"
#include "ParkendVerhalten.h"



double dGlobaleZeit = 0.0;	// globale Zeitvariable und Anfangswertzuweisung

Fahrzeug::Fahrzeug() : // default constructor				//A ARDAYA SOR
	Simulationobjekt("Defaultfahrzeug"),
	p_dMaxGeschwindigkeit(0.0),
	p_dGesamtStrecke(0.0), p_dAbschnittStrecke(0.0) {
	std::cout << "Default Constructor: Fahrzeug \"" << p_sName << "\", ID" << p_iID << " erstellt." << std::endl;
}

Fahrzeug::Fahrzeug(const std::string& name) :	 // parametrisierter Konstruktur

	Simulationobjekt(name),
	p_dMaxGeschwindigkeit(0.0),
	p_dGesamtStrecke(0.0), p_dAbschnittStrecke(0.0) {
	std::cout << "Fahrzeug erstelt ! Name: " << p_sName << "ID: " << p_iID << std::endl;
}

Fahrzeug::Fahrzeug(const std::string& name, double maxGeschwindigkeit)
	:
	Simulationobjekt(name),
	p_dMaxGeschwindigkeit(maxGeschwindigkeit > 0 ? maxGeschwindigkeit : 0.0), // Ternäre Kontrolle
	p_dGesamtStrecke(0.0), p_dAbschnittStrecke(0.0){
	std::cout << "Fahrzeug erstelt: Name = \"" << p_sName << "\", ID: " << p_iID
		<< "Max Geschwindigkeit = " << p_dMaxGeschwindigkeit << "km/h" << std::endl;
}

Fahrzeug::~Fahrzeug() {		 //destructor
	std::cout << "Fahrzeug geloescht! Name:" << p_sName << "ID: " << p_iID << std::endl;
}

// Getter Funktionen
double Fahrzeug::dGeschwindigkeit() const { // Ausgabe der Max Geschwindigkeit
	return p_dMaxGeschwindigkeit;
}

Weg& Fahrzeug::getWeg(){
	return p_pVerhalten->getWeg();
}

void Fahrzeug::setVerhalten(std::unique_ptr<Verhalten> verhalten) {
	p_pVerhalten = std::move(verhalten);
}

void Fahrzeug::vNeueStrecke(Weg& weg) {
	p_pVerhalten = std::make_unique<FahrendVerhalten>(weg);
	p_dAbschnittStrecke = 0.0; // Bölüm mesafesini sıfırla
}

void Fahrzeug::vNeueStrecke(Weg& weg, double startzeit){
	p_pVerhalten = std::make_unique<FahrendVerhalten>(weg);
	p_dAbschnittStrecke = 0.0;	// Bölüm mesafesini ayarla
}


double Fahrzeug::getAbschnittStrecke() const {
	return p_dAbschnittStrecke;
}

double Fahrzeug::getRelPosition(Weg&weg){
	return p_dAbschnittStrecke / weg.getLaenge();
}

void Fahrzeug::vSimulieren() {
	double deltaZeit = dGlobaleZeit - p_dZeit; // Zaman farkını hesapla

	if (deltaZeit > 0.0) {
		double gefahreneStrecke = this->p_pVerhalten->dStrecke(*this, deltaZeit); // Mevcut davranıştan alınan mesafe
		p_dGesamtStrecke += gefahreneStrecke; // Toplam mesafeye ekle
		p_dAbschnittStrecke += gefahreneStrecke; // Sonraki hesaplama için mesafeyi güncelle

		p_dGesamtZeit += deltaZeit; // Toplam geçen süreyi güncelle
		p_dZeit = dGlobaleZeit; // Simülasyon zamanını güncelle
	}
}

//  Druckt Fahrzeugdaten in Tabellenform
void Fahrzeug::vAusgeben(std::ostream& os) const {
	os << std::left << std::setw(5) << p_iID
		<< std::setw(20) << p_sName
		<< std::setw(15) << std::fixed << std::setprecision(1) << dGeschwindigkeit()
		<< std::setw(15) << std::fixed << std::setprecision(2) << p_dGesamtStrecke;
}


bool Fahrzeug::operator<(const Fahrzeug& other) const {		// Überladung von Vergleichungsoperator <
	return this->p_dGesamtStrecke < other.p_dGesamtStrecke;
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& other) {		// Deklarierung von Vergleichungsoperator =				//BUNU DA SOR
	if (this == &other) {
		return *this;	// Selbstzuweisung verhindern
	}

	// Grunddaten kopieren
	this->p_sName = other.p_sName;
	this->p_dMaxGeschwindigkeit = other.p_dMaxGeschwindigkeit;
	// ID wird nicht kopiert,da jedes Objekt eine eindeutige ID haben müssen

	return *this;
}

void Fahrzeug::Zeichnen(Weg &weg) {};



