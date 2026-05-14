#include <iostream>
#include <cstring>
#include <vector>
#include "departament.h"
#include "angajati.h"
#include "proiect.h"
#include "utile.h"
#include "exceptii.h"
#include "contractor.h"
#include "angajatFullTime.h"
#include "angajatPartTime.h"

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
} 

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
        throw ExceptieAngajatNegasit("Angajatul cu ID #" + std::to_string(id) + " nu exista");
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

double Departament::taxeLogistica(double totalSalarii) const {
    return totalSalarii * 1.2;
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
void Departament::viabilitateProiect (const Proiect& p) const{
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
        throw ExceptieAngajatNegasit("Angajatul cu ID #" + std::to_string(id) + " nu exista");
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
        throw ExceptieAngajatNegasit("Angajatul cu ID #" + std::to_string(id) + " nu exista");
    }
}

void Departament::promoveazaContractor(int id) {
    for (auto i = echipa.begin(); i != echipa.end(); i++) {
        if ((*i) -> getId() == id) {
            Contractor* contractor = dynamic_cast<Contractor*>(*i);
            if (!contractor) {
                throw ExceptieTipGresit("Angajatul cu ID #" + std::to_string(id) + " nu este contractor");
            }
            std::string nume = contractor -> getNume();
            int idAng = contractor -> getId();
            double salariuLunar = contractor -> getSalariuZilnic() * contractor -> getZileLucrate();
            Angajat* nou = new AngajatFullTime(nume.c_str(), idAng, salariuLunar, 20, 0);
            delete *i;
            *i = nou;
            std::cout << "\n~" << nume << "~ a fost promovat la Full-Time cu succes!\n";
            return;
        }
    }
    throw ExceptieAngajatNegasit("Angajatul cu ID #" + std::to_string(id) + " nu exista");
}

void Departament::promoveazaPartTime(int id) {
    for (auto i = echipa.begin(); i != echipa.end(); i++) {
        if ((*i) -> getId() == id) {
            AngajatPartTime* partTime = dynamic_cast<AngajatPartTime*>(*i);
            if (!partTime) {
                throw ExceptieTipGresit("Angajatul cu ID #" + std::to_string(id) + " nu este part-time");
            } 
            std::string nume = partTime -> getNume();
            int idAng = partTime -> getId();
            double salariuLunar = partTime -> getsalariuPerOra() * partTime -> getorePerSaptamana() * 4;
            Angajat* nou = new AngajatFullTime(nume.c_str(), idAng, salariuLunar, 20, 0);
            delete *i;
            *i = nou;
            std::cout << "\n~" << nume << "~ a fost promovat la Full-Time cu succes!\n";
            return;
        }
    }
    throw ExceptieAngajatNegasit("Angajatul cu ID #" + std::to_string(id) + " nu exista");
}