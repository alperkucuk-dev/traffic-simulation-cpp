#pragma once
#include "Fahrausnahme.h"
#include "Fahrzeug.h"

class Streckenende : public Fahrausnahme {
public:
	Streckenende(Fahrzeug &fahrzeug, Weg &weg)
		: Fahrausnahme(fahrzeug,weg){}

	void vBearbeiten() override;
};
