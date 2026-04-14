#pragma once
#include "Weg.h"
#include "Fahrzeug.h"

class Verhalten {
protected:
	Weg& p_rWeg;	//Weg referansı

public:
	Verhalten(Weg& weg);
	virtual ~Verhalten() = default;
	Weg& getWeg() const { return p_rWeg; }

	virtual double dStrecke(Fahrzeug& fzg, double dZeitIntervall) = 0;
};
