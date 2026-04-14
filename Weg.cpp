#include "Weg.h"
#include <iostream>
#include <iomanip>
#include "Fahrzeug.h"
#include "FahrendVerhalten.h"
#include <memory>
#include "Streckenende.h"
#include "Simuclient.h"
#include <algorithm>



Weg::Weg(const std::string& name, double laenge, Tempolimit tempolimit)		//constructor
	: Simulationobjekt(name), p_dLaenge(laenge), p_eTempolimit(tempolimit) {}

Weg::~Weg() {
	p_pFahrzeuge.clear();		//listeyi temizler
}

double Weg::getTempolimit() const {		//Tempolimit geri döndürür
	return static_cast<double>(p_eTempolimit);
}

void Weg::vSimulieren() {
    for (auto& fahrzeug : p_pFahrzeuge) {
        try {
            fahrzeug->vSimulieren();			// Araçları simüle et
        }
        catch (Fahrausnahme& _fahrausnahme) {
            _fahrausnahme.vBearbeiten();
        }

    }
    this->p_pFahrzeuge.vAktualisieren();
    this->vFahrzeugVisualisiert();
}

void Weg::vAusgeben(std::ostream& os) const {
    Simulationobjekt::vAusgeben(os);
    os << std::setw(10) << p_dLaenge;

    os << " (";

    for(const auto& fzg : p_pFahrzeuge){
    	os << fzg->getName() << " ";
    }
    os << ")" << std::endl;
}




void Weg::vKopf() {
    std::cout << std::left
        << std::setw(5) << "ID"
        << std::setw(20) << "Name"
        << std::setw(20) << "Laenge"
        << std::setw(10) << "Fahrzeuge"
        << std::endl;
    std::cout << std::string(50, '-') << std::endl;
}

double Weg::getLaenge() const {
    return p_dLaenge;
}
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug) {
    fahrzeug->vNeueStrecke(*this);
    p_pFahrzeuge.push_back(std::move(fahrzeug));
}

const vertagt::VListe<std::unique_ptr<Fahrzeug>>& Weg::getFahrzeuge() const {
    return p_pFahrzeuge; // Doğrudan vertagt::VListe döndürülür
}
void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit) {
    fahrzeug->vNeueStrecke(*this, startzeit);
    p_pFahrzeuge.push_front(std::move(fahrzeug));
}

void Weg::vAusgebenfurFahrzeuge(std::ostream& os) const {
    for (const auto& fahrzeug : p_pFahrzeuge) {
        fahrzeug->vAusgeben(std::cout);
        }
}

void Weg::vFahrzeugVisualisiert(){
	for (const auto& fahrzeug : p_pFahrzeuge) {
	        fahrzeug->Zeichnen(*this);
	        }
}

std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fz) {
    std::list<std::unique_ptr<Fahrzeug>>::iterator it = p_pFahrzeuge.begin();
    auto tmp = std::find_if(p_pFahrzeuge.begin(), p_pFahrzeuge.end(),
                            [&fz](std::unique_ptr<Fahrzeug>& a) { return a.get() == &fz; });
    while (it != p_pFahrzeuge.end()) {
        if (*it == *tmp) {
            break;
        }
        ++it;
    }
    if (it != p_pFahrzeuge.end()) {
        std::unique_ptr<Fahrzeug> ptr = std::move(*tmp);
        p_pFahrzeuge.erase(tmp);
        return ptr;
    } else {
        return std::make_unique<Fahrzeug>(nullptr);
    }
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, const std::string& zustand){		// Park eden aracı ekleme
	if (zustand == "Parkend") {
		p_pFahrzeuge.push_front(std::move(fahrzeug));		// Park eden araç listenin başına eklenir
	}
	else if (zustand == "Fahrend"){
		p_pFahrzeuge.push_back(std::move(fahrzeug));		// Hareket eden araç listenin sonuna eklenir
	}
};
