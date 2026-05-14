#pragma once
#include "angajati.h"

class AngajatFactory {
public:
    static Angajat* creeazaFullTime(const char* nume, int id, double sal, int zile, int ani);
    static Angajat* creeazaPartTime(const char* nume, int id, int ore, double tarif);
    static Angajat* creeazaContractor(const char* nume, int id, double tarif, int zile, const std::string& exp);
    static Angajat* creeazaIntern(const char* nume, int id, double stip, int durata, const std::string& mentor);
};