#include "angajati.h"
#include <iostream>
#include <cstring>


//constructori/destructori
Angajat::Angajat (const char* numeAng, int idAng, double salariuAng) 
: id(idAng), salariu(salariuAng) { 
    nume = copiazaSir(numeAng); 
}

Angajat::Angajat(const Angajat& altul) 
: id(altul.id), salariu(altul.salariu) {
    nume = copiazaSir(altul.nume);
}

Angajat& Angajat::operator=(const Angajat& altul) {
    if (this != &altul) {
        delete[] nume;
        nume = copiazaSir(altul.nume);
        id = altul.id;
        salariu = altul.salariu;
    }
    return *this;
}

Angajat::~Angajat() {
    delete[] nume;
}

const char* Angajat::getNume() const { 
    return nume; 
}

int Angajat::getId() const { 
    return id;              //getteri
} 

double Angajat::getSalariu() const { 
    return salariu; 
}

// afisare angajat
std::ostream& operator<<(std::ostream& os, const Angajat& a){
    os << a.nume << " (#" << a.id << ") | Salariu: " << a.salariu;
    return os;
}

//functie de marire a salariului
void Angajat::maresteSalariu(double procent) {
    salariu += (salariu * procent) / 100.0;
    std::cout << "\nSalariu nou: " << salariu << "\n";
}

// functie de scadere a salariului
void Angajat::scadeSalariu(double procent) {
    salariu -= (salariu * procent) / 100.0;
    std::cout << "\nSalariu nou: " << salariu << "\n";
}