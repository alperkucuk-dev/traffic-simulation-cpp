#include "Kreuzung.h"
#include "Fahrzeug.h"
#include <algorithm>
#include <random>

void Kreuzung::vTanken(Fahrzeug& fahrzeug){
	if(p_dTankstelle > 0){
		double fehlendeMenge = fahrzeug.dTanken();
		double getankteMenge = std::min(p_dTankstelle , fehlendeMenge);
		p_dTankstelle -= getankteMenge;
		std::cout << "Tank dolumu yapıldı: " << getankteMenge << "litre" << std::endl;
	}
};

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fahrzeug, double zeit){	 // İlk çıkış yoluna aracı park et
	if (!p_pWege.empty()){
		p_pWege.front()->vAnnahme(std::move(fahrzeug), zeit);
	}
}

void Kreuzung::vSimulieren(){
	for(auto& weg : p_pWege){
		weg->vSimulieren();		// Kavşaktan çıkan yolları simüle et
	}
}

void Kreuzung::vVerbinde(const std::string& wegHinName, const std::string& wegZurueckName,
        double wegLaenge, const std::shared_ptr<Kreuzung>& start,
        const std::shared_ptr<Kreuzung>& ziel, Tempolimit limit){
	auto wegHin = std::make_shared<Weg>(wegHinName, wegLaenge, limit);
	auto wegZurueck = std::make_shared<Weg>(wegZurueckName, wegLaenge, limit);

		wegHin->setZielkreuzung(ziel);
	    wegZurueck->setZielkreuzung(start);

	    wegHin->setRueckweg(wegZurueck);
	    wegZurueck->setRueckweg(wegHin);

	    start->p_pWege.push_back(wegHin);
	    ziel->p_pWege.push_back(wegZurueck);
	}

/*
Weg& Kreuzung::pZufaelligerWeg(Weg& w) {
    if (p_pWege.size() > 2) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, p_pWege.size() - 1);

        Weg* zufaelligerWeg = nullptr;

        do {
            int randomIndex = dist(gen);
            auto it = std::next(p_pWege.begin(), randomIndex);
            zufaelligerWeg = it->get();
        } while (zufaelligerWeg == &w); // Aynı Weg seçilirse tekrar dene

        return *zufaelligerWeg;
    }
    else {
        return w.getRueckweg();
    }
}
*/
Weg& Kreuzung::pZufaelligerWeg(Weg& w) {
	if (p_pWege.size() > 2) {
		auto tmp = find_if(p_pWege.begin(), p_pWege.end(), [&](std::shared_ptr<Weg>& wg) { return wg.get() == &w; });
		auto zfWeg = next(p_pWege.begin(), rand() % p_pWege.size());

		while (tmp == zfWeg)
			zfWeg = next(p_pWege.begin(), rand() % p_pWege.size());

		return **zfWeg;
	}
	else
		return w.getRueckweg();
}

