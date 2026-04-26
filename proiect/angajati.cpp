#include "angajati.h"
#include <iostream>

int Angajat::numarTotalAngajati = 0;

//constructori/destructori
Angajat::Angajat (const char* numeAng, int idAng) 
: id(idAng) { 
    nume = copiazaSir(numeAng); 
    numarTotalAngajati++;
}

Angajat::Angajat(const Angajat& altul) 
: id(altul.id) {
    nume = copiazaSir(altul.nume);
    numarTotalAngajati++;
}

Angajat& Angajat::operator=(const Angajat& altul) {
    if (this != &altul) {
        delete[] nume;
        nume = copiazaSir(altul.nume);
        id = altul.id;
    }
    return *this;
}

Angajat::~Angajat() {
    delete[] nume;
    numarTotalAngajati--;
}

const char* Angajat::getNume() const { 
    return nume; 
}

int Angajat::getId() const { 
    return id;              //getteri
} 

int Angajat::getTotalNumarAngajati() {
    return numarTotalAngajati;
}

// afisare angajat
std::ostream& operator<<(std::ostream& os, const Angajat& a){
    a.print(os);
    return os;
}
