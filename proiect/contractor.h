#pragma once
#include "angajati.h"
#include <string>

class Contractor : public Angajat {
    private:
        double salariuZilnic;
        int zileLucrate; 
        std::string dataExpirareContract;
        void print(std::ostream& os) const override;

    public:    
        Contractor (const char* nume, int id, double salariuZilnic, int zileLucrate, const std::string& dataExpirareContract);
        Contractor (const Contractor& altul);
        Contractor& operator= (const Contractor& altul);
        ~Contractor();

        double calculeazaSalariu() const override;
        std::string getTipContract() const override;
        Contractor* clone() const override;
        void maresteSalariu (double procent) override;
        void scadeSalariu (double procent) override;

};