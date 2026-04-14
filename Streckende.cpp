#include "Streckenende.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Kreuzung.h"
#include <iostream>
#include "SimulationObjekt.h"

using namespace std;

void Streckenende::vBearbeiten(){
	auto f_ptr = p_weg.pAbgabe(p_fahrzeug);
	Kreuzung& Zielkreuzung = p_weg.getZielkreuzung();
	Zielkreuzung.vTanken(*f_ptr);
	Weg& NeuerWeg = Zielkreuzung.pZufaelligerWeg(p_weg);

	f_ptr->vNeueStrecke(NeuerWeg);
	const string Fahrzeugname = f_ptr->getName();
	const string Kreuzungname = p_weg.getZielkreuzung().getName();
	const int FahrzeugID = f_ptr->getID();
	NeuerWeg.vAnnahme(move(f_ptr));

		cout << "Art der Ausnahme: Streckenende" << endl << "Fahrzeug ID: " << FahrzeugID << endl;
		cout << "ZEIT       :" << dGlobaleZeit << endl;
		cout << "KREUZUNG   :" << Kreuzungname << " INHALT:  " << Zielkreuzung.getTankinhalt() << endl;
		cout << "WECHSEL    :" << p_weg.getName() << " -> " << NeuerWeg.getName() << endl;
		cout << "FAHRZEUG   :" << FahrzeugID << endl<< endl;


}
