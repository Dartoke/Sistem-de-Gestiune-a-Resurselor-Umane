#include <iostream>
#include <cstring>
#include <vector>
#include "departament.h"
#include "angajati.h"
#include "proiect.h"
#include "utile.h"

//constructori/destructori
Departament::Departament(const char* numeDep) { 
    numeDepartament = copiazaSir(numeDep);
}

Departament::Departament (const Departament& altul) 
: echipa(altul.echipa) {
    numeDepartament = copiazaSir(altul.numeDepartament);
}

Departament& Departament::operator=(const Departament& altul) {
    if (this != &altul) {
        delete[] numeDepartament;
        numeDepartament = copiazaSir(altul.numeDepartament);
        echipa = altul.echipa;
    }
    return *this;
}

Departament::~Departament() {
    delete[] numeDepartament;
}

std::string Departament::getNume() const { 
    return numeDepartament; 
} //getter

//functie de adaugare angajat in departament
void Departament::adaugaAngajat (const Angajat& a) {
    echipa.push_back(a);
}

//functie de stergere angajat din departament
void Departament::stergeAngajat(int id) {
    bool gasit = false;
    for (auto i = echipa.begin(); i != echipa.end(); ++i) {
        if (i -> getId() == id) {
            std::cout <<"\n~" << i -> getNume() << "~ a fost concediat cu succes!\n";
            echipa.erase(i);
            gasit = true;
            break;
        }
    }
    if (!gasit) {
        std::cout << "Angajatul cu ID #" << id << " nu exista.\n";
    }
}

//afisare departament
std::ostream& operator<<(std::ostream& os, const Departament& dep) {
    os << dep.numeDepartament << ":\n";
    for (const auto& ang : dep.echipa) {
        os << ang << "\n";
    }
    return os;
}

//functie de calcul a costului unui proiect
double Departament::costProiectEchipa() const {
    double total = 0;
    for (const auto& ang : echipa){
        total += ang.getSalariu();
    }
    return taxeLogistica(total);
}

//functie care verifica daca un departament poate face proiectul ( in functie de bugetul alocat )
void Departament::viabiliateProiect (const Proiect& p) const{
    double costProiect = costProiectEchipa();
    if (costProiect > p.getBuget()) {
        std::cout << "\nProiectul ~" << p.getNume() << "~ nu este realizabil din punct de vedere financiar.\n";
    }
    else {
        std::cout << "\nProiectul ~" << p.getNume() << "~ este realizabil. Buget ramas: " << p.getBuget() - costProiect << std::endl;
    }
}

// functie de marire a salariului
void Departament::maresteSalariuId(double procent, int id){
    bool gasit = false;
    for (auto i = echipa.begin(); i != echipa.end(); ++i) {
        if (i -> getId() == id) {
            i -> maresteSalariu(procent);
            gasit = true;
            break; 
        }
    }
    if (!gasit) {
        std::cout << "Angajatul cu ID #" << id << " nu exista.\n";
    }
}

//functie de scadere a salariului
void Departament::scadereSalariuId(double procent, int id){
    bool gasit = false;
    for (auto i = echipa.begin(); i != echipa.end(); ++i) {
        if (i -> getId() == id) {
            i -> scadeSalariu(procent); 
            gasit = true;
            break; 
        }
    }
    if (!gasit) {
        std::cout << "Angajatul cu ID #" << id << " nu exista.\n";
    }
}
