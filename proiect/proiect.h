#pragma once
#include <iostream>
#include <cstring>
#include "utile.h"

template <typename TipBuget>

class Proiect {
    private:
        char* numeProiect;
        TipBuget bugetAlocat;

    public:

    Proiect (const char* nume, TipBuget buget) 
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

    TipBuget getBuget() const { 
        return bugetAlocat;              //getteri
    }    
                                        
    const char* getNume() const { 
        return numeProiect;  
    }

    //afisare proiect
    friend std::ostream& operator<<(std::ostream& os, const Proiect& proiect){
        os << "Proiect: " << proiect.numeProiect << " | Buget: " << proiect.bugetAlocat;
        return os;
    }

};