#include "contractor.h"
#include <iostream>
#include "exceptii.h"

const double salariuMinimZi = 175;

Contractor::Contractor(const char* nume, int id, double salariuZilnicCTR, int zileLucrateCTR, const std::string& expirare)
: Angajat(nume, id), salariuZilnic(salariuZilnicCTR), zileLucrate(zileLucrateCTR), dataExpirareContract(expirare) {
    if (salariuZilnicCTR < salariuMinimZi) {
        throw ExceptieSalariuInvalid(salariuZilnicCTR);
    }
}

Contractor::Contractor(const Contractor& altul)
: Angajat(altul.nume, altul.id), salariuZilnic(altul.salariuZilnic), zileLucrate(altul.zileLucrate), dataExpirareContract(altul.dataExpirareContract) {}


Contractor& Contractor::operator= (const Contractor& altul) {
    if (this != &altul) {
        delete[] nume;
        nume = copiazaSir(altul.nume);
        id = altul.id;
        salariuZilnic = altul.salariuZilnic;
        zileLucrate = altul.zileLucrate;
        dataExpirareContract = altul.dataExpirareContract;
    }
    return *this;
}

Contractor::~Contractor() {}

double Contractor::calculeazaSalariu() const {
    return salariuZilnic * zileLucrate;
}

std::string Contractor::getTipContract() const {
    return "Contractor";
}

Contractor* Contractor::clone() const {
    return new Contractor(*this);
}


void Contractor::print(std::ostream& os) const {
    os << nume << " (#" << id << ") | Tarif: "
    << salariuZilnic << " RON/zi | Zile lucrate: " 
    << zileLucrate << "| Salariu (total): "
    << calculeazaSalariu();
}


void Contractor::maresteSalariu (double procent) {
    salariuZilnic += (salariuZilnic * procent) / 100;
}

void Contractor::scadeSalariu (double procent) {
    salariuZilnic -= (salariuZilnic * procent) / 100;
}