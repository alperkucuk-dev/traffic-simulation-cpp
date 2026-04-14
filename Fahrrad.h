#pragma once
#include "Fahrzeug.h"
#include <limits>

class Fahrrad : public Fahrzeug {

public:
	Fahrrad(const std::string& name, double maxGeschwindigkeit);		//Constructor

	double dGeschwindigkeit() const override;

	void vAusgeben(std::ostream& os) const override;

	~Fahrrad() override = default;			//destructor

	void Zeichnen (Weg &weg) override;
};

