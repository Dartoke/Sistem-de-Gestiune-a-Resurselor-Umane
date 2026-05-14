#pragma once
#include <iostream>
#include <vector>
#include "angajati.h"
#include "proiect.h"
#include "utile.h"
#include "exceptii.h"

class Departament {

private:

    char* numeDepartament;
    std::vector<Angajat*> echipa;

    double taxeLogistica(double totalSalarii) const;

public: 

    //constructori/destructori
    Departament (const char* numeDep);
    Departament (const Departament& altul);
    Departament& operator=(const Departament& altul);
    ~Departament();

    std::string getNume() const;
    const std::vector<Angajat*>& getEchipa() const { return echipa; }

    void adaugaAngajat (const Angajat& a);
    void stergeAngajat(int id);
    friend std::ostream& operator<<(std::ostream& os, const Departament& dep);
    double costProiectEchipa() const;
    void maresteSalariuId(double procent, int id);
    void scadereSalariuId(double procent, int id);
    void promoveazaContractor(int id);
    void promoveazaPartTime(int id);


    template <typename TipBuget>
    void viabilitateProiect (const Proiect<TipBuget>& p) const{
        double costProiect = costProiectEchipa();
        if (costProiect > p.getBuget()) {
            throw ExceptieProiectNeviabil(p.getNume());
        }
        else {
            std::cout << "\nProiectul ~" << p.getNume() << "~ este realizabil. Buget ramas: " << p.getBuget() - costProiect << std::endl;
        }
    }

};