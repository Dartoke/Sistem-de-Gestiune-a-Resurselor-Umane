#pragma once 
#include "angajati.h"


class AngajatFullTime : public Angajat {
    private:
        double salariu;
        int zileConcediu;
        int aniVechime;
        static const double salariuMinim;

        void print(std::ostream& os) const override;

    public:
        AngajatFullTime (const char* nume, int id, double salariu, int zileConcediu, int aniVechime);
        AngajatFullTime(const AngajatFullTime& altul);
        AngajatFullTime& operator=(const AngajatFullTime& altul);
        ~AngajatFullTime();

        double calculeazaSalariu() const override;
        std::string getTipContract() const override;
        AngajatFullTime* clone() const override;
        void maresteSalariu(double procent) override;
        void scadeSalariu(double procent) override;
};       