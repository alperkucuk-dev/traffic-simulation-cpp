#include "SimulationObjekt.h"
#include "Weg.h"
#include <list>
#include <memory>

class Kreuzung : public Simulationobjekt {

protected:
	std::list<std::shared_ptr<Weg>> p_pWege;	// Kavşaktan çıkan yollar
	double p_dTankstelle;						// Yakıt istasyonu hacmi
public:
	Kreuzung(const std::string& name, double tankstelle = 0.0)
	: Simulationobjekt(name), p_dTankstelle(tankstelle){}

	void vTanken(Fahrzeug &fahrzeug);			// Araç yakıt ikmali yapar
	void vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double zeit);		// Aracı kavşağa alır
	void vSimulieren();		// Kavşaktan çıkan yolları simüle eder
	double getTankinhalt(){
		return p_dTankstelle;
	};
	std::string getName(){
		return p_sName;
	}
	static void vVerbinde(const std::string& wegHinname, const std::string& wegZurueckname,
						 double wegLange, const std::shared_ptr<Kreuzung>& start,
						 const std::shared_ptr<Kreuzung>&  ziel, Tempolimit limit);
	Weg& pZufaelligerWeg(Weg& w);
};
