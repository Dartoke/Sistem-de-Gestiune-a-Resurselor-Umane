#include <iostream>
#include <cstring>
#include "utile.h"
#include "proiect.h"

//constructori/destructori
Proiect::Proiect (const char* nume, double buget) 
: bugetAlocat(buget) {
    numeProiect = copiazaSir(nume);
}

Proiect::Proiect (const Proiect& altul)
: bugetAlocat(altul.bugetAlocat) {
    numeProiect = copiazaSir(altul.numeProiect);
}

Proiect& Proiect::operator=(const Proiect& altul) {
    if (this != &altul) {
        delete[] numeProiect;
        numeProiect = copiazaSir(altul.numeProiect);
        bugetAlocat = altul.bugetAlocat;
    }
    return *this;
}

Proiect::~Proiect() {
    delete[] numeProiect;
}

double Proiect::getBuget() const { 
    return bugetAlocat;              //getteri
}    
                                    
const char* Proiect::getNume() const { 
    return numeProiect; 
}

//afisare proiect
std::ostream& operator<<(std::ostream& os, const Proiect& proiect){
    os << "Proiect: " << proiect.numeProiect << " | Buget: " << proiect.bugetAlocat;
    return os;
}