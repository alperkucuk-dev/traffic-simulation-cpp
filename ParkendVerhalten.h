#pragma once
#include "Verhalten.h"

class ParkendVerhalten : public Verhalten {
protected:
	double p_dStartZeitPunkt;

public:
	ParkendVerhalten(Weg& weg, double startzeit);
	~ParkendVerhalten();

	double dStrecke(Fahrzeug& fzg, double dZeitIntervall) override;
};

