#pragma once
#include "Verhalten.h"

class Fahrzeug;
class Weg;

class FahrendVerhalten : public Verhalten {
public:
	FahrendVerhalten (Weg &weg) : Verhalten(weg) {}
	~FahrendVerhalten() = default;

	double dStrecke(Fahrzeug& fzg, double dZeitIntervall) override;
};
