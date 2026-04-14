#pragma once
#include <string>
#include <iostream>
#include <sstream>   // erforderlich für ostream
#include <limits>
#include "SimulationObjekt.h"
#include <memory>

extern double dGlobaleZeit;	// Deklaration einer globalen Variablen

class Weg;

class Verhalten;

class Fahrzeug : public Simulationobjekt{

protected:	// Unterklassen können erreichen
	double p_dMaxGeschwindigkeit;	// Max Geschwindigkeit
	double p_dGesamtStrecke;		// Gesamt Strecke
	double p_dAbschnittStrecke;
	std::unique_ptr<Verhalten> p_pVerhalten;
public:
	Fahrzeug();								// default constructor
	Fahrzeug(const std::string& name);		// constructor
	Fahrzeug(const std::string& name, double maxGeschwindigkeit);		// constructor
	void setVerhalten(std::unique_ptr<Verhalten> verhalten);		// Davranışı ayarlamak için setter

	virtual ~Fahrzeug();							// destructor
	virtual void Zeichnen(Weg &weg);
	virtual double dGeschwindigkeit() const;   // get-Funktion zur Ermittlung der Höchstgeschwindigkeit

	void vSimulieren() override;	// Funktion, die eine Fahrzeugsimulation durchführt

	void vAusgeben(std::ostream& os) const override;	// virtuelle Datenausgabe

	virtual double dTanken(double dMenge = std::numeric_limits<double>::infinity()) {			//BUNU DA SOR
		return 0;
	}

	Weg& getWeg();

	double getAbschnittStrecke() const;

	double getRelPosition( Weg & weg);

	std::string getName(){
		return this->p_sName;
	}

	void vNeueStrecke(Weg& weg);

	void vNeueStrecke(Weg& weg, double startzeit);

	Fahrzeug& operator=(const Fahrzeug& other);		// Operatordefinition			BUNA BAK

	Fahrzeug(const Fahrzeug&) = delete;		// Verbot des Kopierkonstrukteurs


	bool operator<(const Fahrzeug& other) const;		// Überladung von Vergleichungsoperator <
};
