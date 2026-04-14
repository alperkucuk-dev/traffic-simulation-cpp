#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Simulationobjekt {
protected:
    std::string p_sName;       // Ortak isim
    const int p_iID;           // Kimlik numarası
    static int p_iMaxID;       // Benzersiz ID oluşturmak için en yüksek ID
    double p_dZeit;            // Simülasyon zamanı
    double p_dGesamtZeit;      // Gesamt Zeit

public:
    Simulationobjekt(const std::string& name);
    virtual ~Simulationobjekt();

    virtual void vSimulieren() = 0; // soyut işlev
    virtual void vAusgeben(std::ostream& os) const;

    static void vKopf();

    std::string getName() const;			// get-Funktion, die den Namen zurückgibt
    int getID() const;						// get-Funktion, die die ID-Nummer zurückgibt
};
std::ostream& operator<<(std::ostream& os, const Simulationobjekt& obj); // Überladen des <<-Operators
bool operator==(const Simulationobjekt& lhs, const Simulationobjekt& rhs);
