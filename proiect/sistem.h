#pragma once
#include <vector>
#include "departament.h"


class SistemHR {
private:
    std::vector<Departament> departamente;
    SistemHR();  

public:
    SistemHR(const SistemHR&) = delete;
    SistemHR& operator=(const SistemHR&) = delete;
    
    static SistemHR& getInstance();
    
    std::vector<Departament>& getDepartamente();
    Departament& cautaDepartament(const char* cod, bool& gasit);
    bool existaID(int id) const;
};