#include <cstring>
#include <iostream>

char* copiazaSir(const char* sursa) {
    if (!sursa) return nullptr;
    char* dest = new char[strlen(sursa) + 1];
    strcpy(dest, sursa);
    return dest;
}


class Angajat {

private:

    char* nume;
    int id;
    double salariu;

public:

    //constructori/destructori
    Angajat (const char* numeAng, int idAng, double salariuAng) 
    : id(idAng), salariu(salariuAng) { 
        nume = copiazaSir(numeAng); 
    }

    Angajat(const Angajat& altul) 
    : id(altul.id), salariu(altul.salariu) {
        nume = copiazaSir(altul.nume);
    }

    Angajat& operator=(const Angajat& altul) {
        if (this != &altul) {
            delete[] nume;
            nume = copiazaSir(altul.nume);
            id = altul.id;
            salariu = altul.salariu;
        }
        return *this;
    }

    ~Angajat() {
        delete[] nume;
    }

    const char* getNume() const { 
        return nume; 
    }

    int getId() const { 
        return id;              //getteri
    } 

    double getSalariu() const { 
        return salariu; 
    }

    // afisare angajat
    friend std::ostream& operator<<(std::ostream& os, const Angajat& a){
        os << a.nume << " (#" << a.id << ") | Salariu: " << a.salariu;
        return os;
    }

    //functie de marire a salariului
    void maresteSalariu(double procent) {
        salariu += (salariu * procent) / 100.0;
        std::cout << "\nSalariu nou: " << salariu << "\n";
    }

    // functie de scadere a salariului
    void scadeSalariu(double procent) {
        salariu -= (salariu * procent) / 100.0;
        std::cout << "\nSalariu nou: " << salariu << "\n";
    }
};