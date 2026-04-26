#pragma once
#include <iostream>
#include "utile.h"

class Angajat {

protected:
    char* nume;
    int id;
    static int numarTotalAngajati;

public:
    Angajat (const char* numeAng, int idAng);
    Angajat(const Angajat& altul);
    Angajat& operator=(const Angajat& altul);
    virtual ~Angajat();

    const char* getNume() const;
    int getId() const;

    friend std::ostream& operator<<(std::ostream& os, const Angajat& a);

    virtual double calculeazaSalariu() const = 0;
    virtual std::string getTipContract() const = 0;
    virtual Angajat* clone() const = 0;
    virtual void maresteSalariu(double procent) = 0;
    virtual void scadeSalariu(double procent) = 0;

    static int getTotalNumarAngajati();

private:
    virtual void print(std::ostream& os) const = 0;

};