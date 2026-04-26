#include <iostream>
#include <cstring>


char* copiazaSir(const char* sursa) {
    if (!sursa) return nullptr;
    char* dest = new char[strlen(sursa) + 1];
    strcpy(dest, sursa);
    return dest;
}


class Proiect {

private:

    char* numeProiect;
    double bugetAlocat;

public: 

    //constructori/destructori
    Proiect (const char* nume, double buget) 
    : bugetAlocat(buget) {
        numeProiect = copiazaSir(nume);
    }

    Proiect (const Proiect& altul) 
    : bugetAlocat(altul.bugetAlocat) {
        numeProiect = copiazaSir(altul.numeProiect);
    }

    Proiect& operator=(const Proiect& altul) {
        if (this != &altul) {
            delete[] numeProiect;
            numeProiect = copiazaSir(altul.numeProiect);
            bugetAlocat = altul.bugetAlocat;
        }
        return *this;
    }

    ~Proiect() {
        delete[] numeProiect;
    }

    double getBuget() const { 
        return bugetAlocat;              //getteri
    }    
                                        
    const char* getNume() const { 
        return numeProiect; 
    }

    //afisare proiect
    friend std::ostream& operator<<(std::ostream& os, const Proiect& prc){
        os << "Proiect: " << prc.numeProiect << " | Buget: " << prc.bugetAlocat;
        return os;
    }

};