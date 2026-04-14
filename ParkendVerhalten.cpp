#include "Weg.h"
#include "Fahrzeug.h"
#include "ParkendVerhalten.h"
#include "Losfahren.h"
#include <iostream>
#include <cmath> // fabs için

extern double dGlobaleZeit;

ParkendVerhalten::ParkendVerhalten(Weg & weg, double zeit) : Verhalten(weg), p_dStartZeitPunkt(zeit) {}

ParkendVerhalten::~ParkendVerhalten() {}

double ParkendVerhalten::dStrecke(Fahrzeug& f, double zeit) {
	if (dGlobaleZeit < p_dStartZeitPunkt)
		return 0.0;
	else
		throw Losfahren(f, p_rWeg);
}
