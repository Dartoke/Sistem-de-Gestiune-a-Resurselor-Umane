#pragma once
#include <iostream>
#include "utile.h"

class Proiect {

private:

    char* numeProiect;
    double bugetAlocat;

public: 

    //constructori/destructori
    Proiect (const char* nume, double buget);
    Proiect (const Proiect& altul);
    Proiect& operator=(const Proiect& altul);
    ~Proiect();

    double getBuget() const;
                                        
    const char* getNume() const;

    //afisare proiect
    friend std::ostream& operator<<(std::ostream& os, const Proiect& proiect);
};