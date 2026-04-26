#include <iostream>
#include <cstring>
#include <vector>
#include <angajati.h>
#include <proiect.h>


char* copiazaSir(const char* sursa) {
    if (!sursa) return nullptr;
    char* dest = new char[strlen(sursa) + 1];
    strcpy(dest, sursa);
    return dest;
}


class Departament {

private:

    char* numeDepartament;
    std::vector <Angajat> echipa;

    //functie privata pentru taxa de logistica la proiect
    double taxeLogistica(double totalSalarii) const {
        return totalSalarii * 1.2;  //taxa de logistica de 20%
    }

public: 

    //constructori/destructori
    Departament (const char* numeDep) { 
        numeDepartament = copiazaSir(numeDep);
    }

    Departament (const Departament& altul) 
    : echipa(altul.echipa) {
        numeDepartament = copiazaSir(altul.numeDepartament);
    }

    Departament& operator=(const Departament& altul) {
        if (this != &altul) {
            delete[] numeDepartament;
            numeDepartament = copiazaSir(altul.numeDepartament);
            echipa = altul.echipa;
        }
        return *this;
    }

    ~Departament() {
        delete[] numeDepartament;
    }

    std::string getNume() const { 
        return numeDepartament; 
    } //getter

    //functie de adaugare angajat in departament
    void adaugaAngajat (const Angajat& a) {
        echipa.push_back(a);
    }

    //functie de stergere angajat din departament
    void stergeAngajat(int id) {
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
    friend std::ostream& operator<<(std::ostream& os, const Departament& dep) {
        os << dep.numeDepartament << ":\n";
        for (const auto& ang : dep.echipa) {
            os << ang << "\n";
        }
        return os;
    }

    //functie de calcul a costului unui proiect
    double costProiectEchipa() const {
        double total = 0;
        for (const auto& ang : echipa){
            total += ang.getSalariu();
        }
        return taxeLogistica(total);
    }

    //functie care verifica daca un departament poate face proiectul ( in functie de bugetul alocat )
    void viabiliateProiect (const Proiect& p) const{
        double costProiect = costProiectEchipa();
        if (costProiect > p.getBuget()) {
            std::cout << "\nProiectul ~" << p.getNume() << "~ nu este realizabil din punct de vedere financiar.\n";
        }
        else {
            std::cout << "\nProiectul ~" << p.getNume() << "~ este realizabil. Buget ramas: " << p.getBuget() - costProiect << std::endl;
        }
    }

    // functie de marire a salariului
    void maresteSalariuId(double procent, int id){
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
    void scadereSalariuId(double procent, int id){
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

};