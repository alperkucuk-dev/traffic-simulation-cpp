#pragma once
#include "Fahrzeug.h"
#include <limits>
#include "Verhalten.h"

class PKW : public Fahrzeug {

private:
	double p_dVerbrauch;	// Kraftstoffverbrauch
	double p_dTankvolumen;	// Tank Volumen
	double p_dTankinhalt;	// Tank Inhalt(Liter)


public:
	PKW(const std::string& name, double maxGeschwindigkeit, double verbrauch, double tankvolumen = 55.0);	// Constructor
	~PKW() override;		// Destructor

	double dGeschwindigkeit() const override;		//

	void vAusgeben(std::ostream& os) const override;	// PKW-spezifischer Ausdruck

	void vSimulieren() override;

	double dTanken(double dMenge = std::numeric_limits<double>::infinity());

	double getTankinhalt() const;

	void Zeichnen(Weg &weg) override;

};
