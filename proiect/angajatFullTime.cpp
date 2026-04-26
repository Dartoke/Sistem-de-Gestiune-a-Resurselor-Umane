#include "angajatFullTime.h"
#include <iostream>
#include "exceptii.h"

const double AngajatFullTime::salariuMinim = 4300.0;

AngajatFullTime::AngajatFullTime(const char* nume, int id, double salariuAFT, int zileConcediuAFT, int aniVechimeAFT) 
: Angajat(nume, id), salariu(salariuAFT), zileConcediu(zileConcediuAFT), aniVechime(aniVechimeAFT) {
    if (salariuAFT < salariuMinim) {
        throw ExceptieSalariuInvalid(salariuAFT);
    }
}

AngajatFullTime::AngajatFullTime(const AngajatFullTime& altul) 
: Angajat(altul.nume, altul.id), salariu(altul.salariu), zileConcediu(altul.zileConcediu), aniVechime(altul.aniVechime) {}

AngajatFullTime& AngajatFullTime::operator= (const AngajatFullTime& altul) {
    if (this != &altul) {
        delete[] nume;
        nume = copiazaSir(altul.nume);
        id = altul.id;
        salariu = altul.salariu;
        zileConcediu = altul.zileConcediu;
        aniVechime = altul.aniVechime;

    }
    return *this;
} 

AngajatFullTime::~AngajatFullTime() {}

double AngajatFullTime::calculeazaSalariu() const {
    double bonusVechime = 0.05 * aniVechime * salariu;
    return salariu + bonusVechime;
}

std::string AngajatFullTime::getTipContract() const {
    return "Full-Time";
}

AngajatFullTime* AngajatFullTime::clone() const {
    return new AngajatFullTime(*this);
}
    
void AngajatFullTime::print(std::ostream& os) const {
    os << nume << " (#" << id << ") | Salariu: " << salariu 
       << " | Zile concediu: " << zileConcediu 
       << " | Ani vechime: " << aniVechime;
}

void AngajatFullTime::maresteSalariu(double procent) {
    salariu += (salariu * procent) / 100;
}

void AngajatFullTime::scadeSalariu(double procent) {
    salariu -= (salariu * procent) / 100;
}