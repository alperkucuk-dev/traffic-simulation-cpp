#pragma once
#include <string>
#include <list>
#include <memory>
#include "SimulationObjekt.h"
#include "vertagt_liste.h"

class Fahrzeug;

class Kreuzung;

//Tempolimit için enumclass

enum class Tempolimit { Innersorts = 50, Landstrase = 100, Autobahn = INT_MAX };

class Weg : public Simulationobjekt {
protected:
	double p_dLaenge;
	Tempolimit p_eTempolimit;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	 std::weak_ptr<Kreuzung> p_zielKreuzung; // Hedef kavşak
	 std::weak_ptr<Weg> p_rueckWeg;         // Geri dönüş yolu
public:
	Weg(const std::string& name, double laenge, Tempolimit tempolimit = Tempolimit::Autobahn);	//constructor

	~Weg();

	double getTempolimit() const;

	const vertagt::VListe<std::unique_ptr<Fahrzeug>>& getFahrzeuge() const;

	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug& fahrzeug);

	void vSimulieren() override;

	void vAusgeben(std::ostream& os) const;

	double getLaenge() const;

	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug);

	void vKopf();

	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double startzeit);

	void vAusgebenfurFahrzeuge(std::ostream& os) const;

	void vFahrzeugVisualisiert();

	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, const std::string& zustand);


	Kreuzung& getZielkreuzung() { return *(p_zielKreuzung.lock()); }

	Weg& getRueckweg() { return *p_rueckWeg.lock(); }

	void setZielkreuzung(const std::shared_ptr<Kreuzung>& ziel) { p_zielKreuzung = ziel; }

	void setRueckweg(const std::shared_ptr<Weg>& rueckweg) { p_rueckWeg = rueckweg; }

};
