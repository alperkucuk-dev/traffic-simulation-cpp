#pragma once
#include <exception>
#include "Fahrzeug.h"
#include "Weg.h"

class Fahrausnahme : public std::exception {
protected:
	Fahrzeug& p_fahrzeug;
	Weg& p_weg;

public:
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg)
		: p_fahrzeug(fahrzeug), p_weg(weg){}
	virtual ~Fahrausnahme() = default;

	virtual void vBearbeiten() = 0;
};
