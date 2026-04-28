#pragma once
#include "angajati.h"
#include <string>


class Intern : public Angajat {
    private: 
        double stipendiu;
        int durataInternship; // in luni
        std::string numeMentor;

        void print(std::ostream& os) const override;

    public:
        Intern(const char* nume, int id, double stipendiu, int durataInternship, const std::string& numeMentor);
        Intern (const Intern& altul);
        Intern & operator= (const Intern& altul);
        ~Intern();

        double calculeazaSalariu() const override;
        std::string getTipContract() const override;
        Intern* clone() const override;
        void maresteSalariu(double procent) override;
        void scadeSalariu(double procent) override;
        
};