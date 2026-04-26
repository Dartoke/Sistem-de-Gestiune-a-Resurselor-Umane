#pragma once
#include <iostream>
#include <vector>
#include "angajati.h"
#include "proiect.h"
#include "utile.h"

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

    void adaugaAngajat (const Angajat& a);
    void stergeAngajat(int id);
    friend std::ostream& operator<<(std::ostream& os, const Departament& dep);
    double costProiectEchipa() const;
    void viabiliateProiect (const Proiect& p) const;
    void maresteSalariuId(double procent, int id);
    void scadereSalariuId(double procent, int id);

};