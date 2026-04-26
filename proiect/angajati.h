#pragma once
#include <iostream>
#include "utile.h"

class Angajat {

private:
    char* nume;
    int id;
    double salariu;

public:

    //constructori/destructori
    Angajat (const char* numeAng, int idAng, double salariuAng);
    Angajat(const Angajat& altul);
    Angajat& operator=(const Angajat& altul);
    ~Angajat();

    const char* getNume() const;
    int getId() const;
    double getSalariu() const;


    // afisare angajat
    friend std::ostream& operator<<(std::ostream& os, const Angajat& a);

    //functie de marire a salariului
    void maresteSalariu(double procent);

    // functie de scadere a salariului
    void scadeSalariu(double procent);
};