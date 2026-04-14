#include "FahrendVerhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"

double FahrendVerhalten::dStrecke(Fahrzeug& aFzg, double zeitintervall){
	double dMoeglicheStrecke = aFzg.dGeschwindigkeit()*zeitintervall;
	double dVerbliebendeStrecke = p_rWeg.getLaenge() - aFzg.getAbschnittStrecke();

	if (dMoeglicheStrecke < dVerbliebendeStrecke) {
		return dMoeglicheStrecke;
	}
	else {
		throw Streckenende(aFzg, p_rWeg); // Yolun sonuna ulaşıldığında Streckenende exception’ını fırlat
	}
}
