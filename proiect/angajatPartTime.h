#pragma once
#include "angajati.h"

class AngajatPartTime : public Angajat { 
    private: 
        int orePerSaptamana;
        double salariuPerOra;
        static const double salariuMinimOra;

        void print(std::ostream& os) const override;

    public:
        AngajatPartTime(const char* nume, int id, int orePerSaptamana, double salariuPerOra);
        AngajatPartTime(const AngajatPartTime& altul);
        AngajatPartTime& operator= (const AngajatPartTime& altul);
        ~AngajatPartTime ();

        double calculeazaSalariu() const override;
        std::string getTipContract() const override;
        AngajatPartTime* clone() const override;
        void maresteSalariu(double procent) override;
        void scadeSalariu(double procent) override;
};