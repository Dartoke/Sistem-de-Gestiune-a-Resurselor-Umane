#include <iostream>
#include <cstring>
#include <vector>
#include "departament.h"
#include "angajati.h"
#include "proiect.h"
#include "utile.h"
#include "exceptii.h"

//constructori/destructori
Departament::Departament(const char* numeDep) { 
    numeDepartament = copiazaSir(numeDep);
}

Departament::Departament (const Departament& altul) 
: numeDepartament(copiazaSir(altul.numeDepartament)) {
    for (auto* a : altul.echipa) {
        echipa.push_back(a -> clone());
    }
}

Departament& Departament::operator=(const Departament& altul) {
    if (this != &altul) {
        delete[] numeDepartament;
        numeDepartament = copiazaSir(altul.numeDepartament);
        for (auto* a : echipa) {
            delete a;
        }
        echipa.clear();
        for (auto* a : altul.echipa) {
            echipa.push_back(a -> clone());
        }
    }
    return *this;
}

Departament::~Departament() {
    delete[] numeDepartament;
    for (auto* a: echipa) {
        delete a;
    }
}

std::string Departament::getNume() const { 
    return numeDepartament; 
} //getter

//functie de adaugare angajat in departament
void Departament::adaugaAngajat (const Angajat& a) {
    echipa.push_back(a.clone());
}

//functie de stergere angajat din departament
void Departament::stergeAngajat(int id) {
    bool gasit = false;
    for (auto i = echipa.begin(); i != echipa.end(); ++i) {
        if ((*i) -> getId() == id) {
            std::cout <<"\n~" << (*i) -> getNume() << "~ a fost concediat cu succes!\n";
            delete *i;
            echipa.erase(i);
            gasit = true;
            break;
        }
    }
    if (!gasit) {
        throw ExceptieAngajatNegasit(id);
    }
}

//afisare departament
std::ostream& operator<<(std::ostream& os, const Departament& dep) {
    os << dep.numeDepartament << ":\n";
    for (const auto* ang : dep.echipa) {
        os << *ang << "\n";
    }
    return os;
}

//functie de calcul a costului unui proiect
double Departament::costProiectEchipa() const {
    double total = 0;
    for (const auto* ang : echipa){
        total += ang -> calculeazaSalariu();
    }
    return taxeLogistica(total);
}

//functie care verifica daca un departament poate face proiectul ( in functie de bugetul alocat )
void Departament::viabiliateProiect (const Proiect& p) const{
    double costProiect = costProiectEchipa();
    if (costProiect > p.getBuget()) {
        throw ExceptieProiectNeviabil(p.getNume());
    }
    else {
        std::cout << "\nProiectul ~" << p.getNume() << "~ este realizabil. Buget ramas: " << p.getBuget() - costProiect << std::endl;
    }
}

// functie de marire a salariului
void Departament::maresteSalariuId(double procent, int id){
    bool gasit = false;
    for (auto i = echipa.begin(); i != echipa.end(); ++i) {
        if ((*i) -> getId() == id) {
            (*i) -> maresteSalariu(procent);
            gasit = true;
            break; 
        }
    }
    if (!gasit) {
        throw ExceptieAngajatNegasit(id);
    }
}

//functie de scadere a salariului
void Departament::scadereSalariuId(double procent, int id){
    bool gasit = false;
    for (auto i = echipa.begin(); i != echipa.end(); ++i) {
        if ((*i) -> getId() == id) {
            (*i) -> scadeSalariu(procent); 
            gasit = true;
            break; 
        }
    }
    if (!gasit) {
        throw ExceptieAngajatNegasit(id);
    }
}
