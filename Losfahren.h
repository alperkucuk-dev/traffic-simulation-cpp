#pragma once
#include "Fahrausnahme.h"


class Losfahren : public Fahrausnahme {
public:
	Losfahren(Fahrzeug &fahrzeug, Weg &weg)
		: Fahrausnahme(fahrzeug,weg){}

	void vBearbeiten() override {
		std::cout << "Fahrzeug" << p_fahrzeug.getName()
			<< " fährt auf dem Weg " << p_weg.getName() << " los. \n";
	}
};
