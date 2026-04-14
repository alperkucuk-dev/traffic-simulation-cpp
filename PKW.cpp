#include "PKW.h"
#include <iomanip>
#include <sstream>
#include <limits>
#include <iostream>
#include "Simuclient.h"

PKW::PKW(const std::string& name, double maxGeschwindigkeit, double verbrauch, double tankvolumen)
	:Fahrzeug(name, maxGeschwindigkeit),
	p_dVerbrauch(verbrauch),
	p_dTankvolumen(tankvolumen),
	p_dTankinhalt(tankvolumen / 2) {		// Tank startet halbvoll
	std::cout << "PKW erstellt Name = " << name
		<< ", MaxGeschwindigkeit = " << maxGeschwindigkeit
		<< ", Verbrauch = " << verbrauch
		<< ", Tankvolumen = " << tankvolumen
		<< ", Tankinhalt = " << p_dTankinhalt << " L" << std::endl;
}

PKW::~PKW() {
	std::cout << "PWK geloescht: Name = " << p_sName << std::endl;
}

// Datenausgabefunktion des PKW
void PKW::vAusgeben(std::ostream& os) const {
    Fahrzeug::vAusgeben(os);
    os << std::setw(15) << std::fixed << std::setprecision(2) << p_dTankinhalt
       << std::setw(20) << std::fixed << std::setprecision(2) << (p_dGesamtStrecke / 100.0) * p_dVerbrauch
       << std::endl;
}

void PKW::vSimulieren() {
	double deltaZeit = dGlobaleZeit - p_dZeit; // Simulationszeit
	if (deltaZeit <= 0) {
		return; // Beenden, wenn die Simulation nicht abgeschlossen ist
	}

	if (p_dTankinhalt <= 0) {
		// Wenn kein Kraftstoff vorhanden ist, bewegt sich das Fahrzeug nicht
		std::cout << std::endl << "PKW " << p_sName << " hat kein Kraftstoff! Fahrzeug bleibt stehen." << std::endl
		<<std::endl;
		p_dZeit = dGlobaleZeit; // Simulationszeit aktualisieren
		return;
	}

	double gefahreneStrecke = this->p_pVerhalten->dStrecke(*this, deltaZeit);

	double tempolimit = p_pVerhalten->getWeg().getTempolimit();
	if (dGeschwindigkeit() > tempolimit) {
		gefahreneStrecke *= tempolimit / dGeschwindigkeit();
	}

	double verbrauchterKraftstoff = (gefahreneStrecke / 100.0) * p_dVerbrauch;

	if (verbrauchterKraftstoff <= p_dTankinhalt) {
		p_dGesamtStrecke += gefahreneStrecke;
		p_dAbschnittStrecke += gefahreneStrecke;
		p_dTankinhalt -= verbrauchterKraftstoff;
		p_dGesamtZeit += deltaZeit;
		// Kraftstoff aktualisieren
	}
	else {
		// Wenn nicht genügend Kraftstoff vorhanden ist, bewegt sich das Fahrzeug überhaupt nicht

		std::cout << std::endl << "PKW " << p_sName << " hat nicht genug Kraftstoff! Fahrzeug bleibt stehen." << std::endl << std::endl;
		// Treibstoff bleibt gleich, keine Bewegung
	}
	p_dZeit = dGlobaleZeit;
}


double PKW::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit;		// PKW immer mit Maximum Geschwindigkeit
}



double PKW::dTanken(double dMenge) {
	// Prüfung auf negative Werte (keine negativen Werte erlaubt)
	if (dMenge < 0) {
		std::cout << "Fehler: Negative Tankmenge ist unzulaessig!" << std::endl;
		return 0.0; // Gibt bei einem negativen Wert 0 zurück, ohne etwas zu tun
	}

	// Wenn Vollfüllung gewünscht ist
	if (dMenge == std::numeric_limits<double>::infinity()) {
		dMenge = p_dTankvolumen - p_dTankinhalt;
	}

	// Verbleibende Vorgänge (Kraftstoff hinzufügen)
	double tatsaechlichGetankt = 0.0;
	if (p_dTankinhalt + dMenge <= p_dTankvolumen) {
		tatsaechlichGetankt = dMenge;
	}
	else {
		tatsaechlichGetankt = p_dTankvolumen - p_dTankinhalt;
	}
	p_dTankinhalt += tatsaechlichGetankt;

	return tatsaechlichGetankt;
}

double PKW::getTankinhalt() const {
    return p_dTankinhalt; // Mevcut yakıt miktarını döndür
}
void PKW::Zeichnen(Weg &weg){
	double relPosition = getRelPosition(weg);
	bZeichnePKW(getName(), weg.getName(),relPosition, dGeschwindigkeit(), getTankinhalt());
}


