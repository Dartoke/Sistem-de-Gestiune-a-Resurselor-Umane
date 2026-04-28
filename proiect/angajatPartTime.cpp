#include "angajatPartTime.h"
#include <iostream>
#include "exceptii.h"

const double AngajatPartTime::salariuMinimOra = 20;

AngajatPartTime::AngajatPartTime(const char* nume, int id, int oreAPT, double salariuAPT)
: Angajat(nume, id), orePerSaptamana(oreAPT), salariuPerOra(salariuAPT) {
    if (salariuAPT < salariuMinimOra) {
        throw ExceptieSalariuInvalid(salariuAPT);
    }
}

AngajatPartTime::AngajatPartTime (const AngajatPartTime& altul)
: Angajat(altul.nume, altul.id), orePerSaptamana(altul.orePerSaptamana), salariuPerOra(altul.salariuPerOra) {}

AngajatPartTime& AngajatPartTime::operator= (const AngajatPartTime& altul) {
    if (this != & altul) {
        delete[] nume;
        nume = copiazaSir(altul.nume);
        id = altul.id;
        orePerSaptamana = altul.orePerSaptamana;
        salariuPerOra = altul.salariuPerOra;
    }
    return *this;
}

AngajatPartTime::~AngajatPartTime() {}

double AngajatPartTime::getsalariuPerOra() const {
    return salariuPerOra;
}

int AngajatPartTime::getorePerSaptamana() const {
    return orePerSaptamana;
}

double AngajatPartTime::calculeazaSalariu() const {
    return orePerSaptamana * salariuPerOra * 4;
}

std::string AngajatPartTime::getTipContract() const {
    return "Part-Time";
}

AngajatPartTime* AngajatPartTime::clone() const {
    return new AngajatPartTime(*this);
}

void AngajatPartTime::print(std::ostream& os) const {
    os << nume << " (#" << id << ") | "
    << orePerSaptamana << " ore/saptamana | Tarif: "
    << salariuPerOra << " RON/ora | Salariu (lunar): " << calculeazaSalariu();
}

void AngajatPartTime::maresteSalariu(double procent) {
    salariuPerOra += (salariuPerOra * procent) / 100;
}


void AngajatPartTime::scadeSalariu(double procent) {
    salariuPerOra -= (salariuPerOra * procent) / 100;
}
