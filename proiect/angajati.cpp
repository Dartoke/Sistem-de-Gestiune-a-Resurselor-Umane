#include "angajati.h"
#include <iostream>


//constructori/destructori
Angajat::Angajat (const char* numeAng, int idAng) 
: id(idAng) { 
    nume = copiazaSir(numeAng); 
}

Angajat::Angajat(const Angajat& altul) 
: id(altul.id) {
    nume = copiazaSir(altul.nume);
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
}

const char* Angajat::getNume() const { 
    return nume; 
}

int Angajat::getId() const { 
    return id;              //getteri
} 

// afisare angajat
std::ostream& operator<<(std::ostream& os, const Angajat& a){
    a.print(os);
    return os;
}
