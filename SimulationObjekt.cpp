#include "SimulationObjekt.h"

int Simulationobjekt::p_iMaxID = 0;

Simulationobjekt::Simulationobjekt(const std::string& name)
	: p_sName(name), p_iID(++p_iMaxID), p_dZeit(0.0), p_dGesamtZeit(0.0) {}

Simulationobjekt::~Simulationobjekt() {
	std::cout << "Simulationobjekt '" << p_sName << "' (ID: " << p_iID << ") yok edildi." << std::endl;
}

void Simulationobjekt::vKopf() {
    std::cout << std::left
        << std::setw(5) << "ID"
        << std::setw(20) << "Name"
        << std::setw(15) << "MaxGeschwindigkeit"
        << std::setw(15) << "Gesamtstrecke"
        << std::setw(15) << "Tankinhalt"
        << std::setw(20) << "Gesamtverbrauch"
        << std::endl;
    std::cout << std::string(95, '-') << std::endl;
}

void Simulationobjekt::vAusgeben(std::ostream& os) const {
    os << std::setw(5) << p_iID << std::setw(20) << p_sName;
}

std::string Simulationobjekt::getName() const { // Ausdruck der Fahrzeugbezeichnung
	return p_sName;
}

int Simulationobjekt::getID() const {		// Fahrzeug-ID-Ausdruck
	return p_iID;
}

std::ostream& operator<<(std::ostream& os, const Simulationobjekt& obj) {
	obj.vAusgeben(os);	// Polimorfik çağrı
	return os;
}
bool operator==(const Simulationobjekt& obj1, const Simulationobjekt& obj2) {
	return obj1.getID() == obj2.getID(); // ID'lerin eşitliğini kontrol eder
}
