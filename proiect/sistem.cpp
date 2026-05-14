#include "sistem.h"
#include <iostream>
#include <cstring>

SistemHR& SistemHR::getInstance() {
    static SistemHR instance; 
    return instance;
}

SistemHR::SistemHR() {
    departamente = { 
        Departament("Software Development"),
        Departament("Human Resources"),
        Departament("Logistics"),
        Departament("Design")
    };
}

Departament& SistemHR::cautaDepartament(const char* dep, bool& gasit){
    gasit = true;
    if (strcmp(dep, "SD") == 0) return departamente[0];
    if (strcmp(dep, "HR") == 0) return departamente[1];
    if (strcmp(dep, "LG") == 0) return departamente[2];
    if (strcmp(dep, "DG") == 0) return departamente[3];

    gasit = false;
    std::cout << "Nu exista acest departament\n\n";
    return departamente[0];
}

std::vector<Departament>& SistemHR::getDepartamente() {
    return departamente;
}

bool SistemHR::existaID(int id) const {
    for (const auto& departament : departamente) {
        for (auto* a : departament.getEchipa()) {
            if (a -> getId() == id) {
                return true;
            }
        }
    }
    return false;
} 