#pragma once
#include <iostream>
#include <vector>
#include "angajati.h"
#include "proiect.h"
#include "utile.h"

class Departament {

private:

    char* numeDepartament;
    std::vector <Angajat> echipa;

    //functie privata pentru taxa de logistica la proiect
    double taxeLogistica(double totalSalarii) const;

public: 

    //constructori/destructori
    Departament (const char* numeDep);
    Departament (const Departament& altul);
    Departament& operator=(const Departament& altul);
    ~Departament();

    std::string getNume() const;

    //functie de adaugare angajat in departament
    void adaugaAngajat (const Angajat& a);

    //functie de stergere angajat din departament
    void stergeAngajat(int id);

    //afisare departament
    friend std::ostream& operator<<(std::ostream& os, const Departament& dep);

    //functie de calcul a costului unui proiect
    double costProiectEchipa() const;

    //functie care verifica daca un departament poate face proiectul ( in functie de bugetul alocat )
    void viabiliateProiect (const Proiect& p) const;

    // functie de marire a salariului
    void maresteSalariuId(double procent, int id);

    //functie de scadere a salariului
    void scadereSalariuId(double procent, int id);

};