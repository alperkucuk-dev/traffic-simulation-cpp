#include "Fahrrad.h"
#include <sstream>
#include <limits>
#include "Simuclient.h"
#include "Weg.h"
Fahrrad::Fahrrad(const std::string& name, double maxGeschwindigkeit)	//constructor
	: Fahrzeug(name, maxGeschwindigkeit) {}



double Fahrrad::dGeschwindigkeit() const {
	double reduktionsrate = (p_dGesamtStrecke / 20) * 0.1;
	double neueGeschwindigkeit = p_dMaxGeschwindigkeit * (1.0 - reduktionsrate);
	if (neueGeschwindigkeit < 12) {
		neueGeschwindigkeit = 12;		// Minimum Geschwindigkeit
	}
	return neueGeschwindigkeit;
}

void Fahrrad::vAusgeben(std::ostream& os) const {
	Fahrzeug::vAusgeben(os);
	os << std::setw(15) << "-"
		<< std::setw(20) << "-"
		<< std::endl;}

void Fahrrad::Zeichnen(Weg &weg){
	double relPosition = getRelPosition(weg);
	bZeichneFahrrad(getName(), weg.getName(), relPosition, dGeschwindigkeit());
}

