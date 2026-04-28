#pragma once
#include <string>
#include <exception>

class ExceptieHR : public std::exception {
    std::string mesaj;

    public:
        ExceptieHR(const std::string& msg) : mesaj(msg) {}
        const char* what() const noexcept override {
            return mesaj.c_str();
        }
};


class ExceptieSalariuInvalid : public ExceptieHR {
    public:
        explicit ExceptieSalariuInvalid(int salariu)
        : ExceptieHR("Salariu invalid: " + std::to_string(salariu)) {}
};


class ExceptieAngajatNegasit : public ExceptieHR {
    public: 
        explicit ExceptieAngajatNegasit(const std::string& mesaj)
        : ExceptieHR(mesaj) {} 
};

class ExceptieProiectNeviabil : public ExceptieHR {
    public: 
        explicit ExceptieProiectNeviabil(const std::string& numeP) 
        : ExceptieHR("Proiectul ~" + numeP + "~ nu este realizabil") {}
};