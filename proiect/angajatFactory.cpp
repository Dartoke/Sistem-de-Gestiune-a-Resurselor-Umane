#include "angajatFactory.h"
#include "angajatFullTime.h"
#include "angajatPartTime.h"
#include "contractor.h"
#include "intern.h"

Angajat* AngajatFactory::creeazaFullTime(const char* nume, int id, double sal, int zile, int ani) {
    return new AngajatFullTime(nume, id, sal, zile, ani);
}

Angajat* AngajatFactory::creeazaPartTime(const char* nume, int id, int ore, double tarif) {
    return new AngajatPartTime(nume, id, ore, tarif);
}

Angajat* AngajatFactory::creeazaContractor(const char* nume, int id, double tarif, int zile, const std::string& exp) {
    return new Contractor(nume, id, tarif, zile, exp);
}

Angajat* AngajatFactory::creeazaIntern(const char* nume, int id, double stip, int durata, const std::string& mentor) {
    return new Intern(nume, id, stip, durata, mentor);
}