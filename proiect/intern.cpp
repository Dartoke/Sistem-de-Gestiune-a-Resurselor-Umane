#include <iostream>
#include "intern.h"
#include "exceptii.h"


Intern::Intern(const char* nume, int id, double stipendiu, int durataInternship, const std::string& numeMentor)
: Angajat(nume, id), stipendiu(stipendiu), durataInternship(durataInternship), numeMentor(numeMentor) {}

Intern::Intern(const Intern& altul)
: Angajat(altul.nume, altul.id), stipendiu(altul.stipendiu), durataInternship(altul.durataInternship), numeMentor(altul.numeMentor) {}

Intern& Intern::operator= (const Intern& altul) {
    if (this != &altul) {
        delete[] nume;
        nume = copiazaSir(altul.nume);
        id = altul.id;
        stipendiu = altul.stipendiu;
        durataInternship = altul.durataInternship;
        numeMentor = altul.numeMentor;
    }
    return *this;
}

Intern::~Intern() {}

std::string Intern::getTipContract() const {
    return "Internship";
}

double Intern::calculeazaSalariu() const {
    return stipendiu;
}

Intern *Intern::clone() const {
    return new Intern(*this);
}

void Intern::maresteSalariu(double procent) {
    stipendiu += (stipendiu * procent) / 100;
}

void Intern::scadeSalariu(double procent) {
    stipendiu -= (stipendiu * procent) / 100;
}

void Intern::print(std::ostream& os) const {
    os << nume << " (#" << id << ") | Stipendiu: "
    << stipendiu << " RON/Luna | Durata Internship: "
    << durataInternship << " luni | Mentor: " << numeMentor;
}