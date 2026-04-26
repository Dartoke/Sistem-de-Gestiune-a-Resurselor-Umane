#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <angajati.h>
#include <proiect.h>
#include <departament.h>


//4 departamente predefinite
Departament SD("Software Development");
Departament HR("Human Resources");
Departament LG("Logistics");
Departament DG("Design");

//functie care verifica daca un departament exista
Departament& verificareDepartament (const char* dep, bool& gasit){
    gasit = true;
    if (strcmp(dep, "SD") == 0) return SD;
    if (strcmp(dep, "HR") == 0) return HR;
    if (strcmp(dep, "LG") == 0) return LG;
    if (strcmp(dep, "DG") == 0) return DG;
    
    gasit = false;
    std::cout << "Nu exista acest departament\n";
    return SD; //returnare aleatorie
}

//functie de adaugare angajati din fisier de intrare ( OBLIGATORIU LA INCEPUT PENTRU A AVEA CATIVA ANGAJATI IN DEPARTAMENTE !!!)
void adaugaDinFisier(const Angajat& a) {
    char dep[100];
    bool ok = false;
    do{
        std::cout << "Angajeaza pe ~" << a << "~ intr-un departament -> SD - HR - LG - DG: ";
        std::cin >> dep;
        bool gasit = false;

        Departament& ales = verificareDepartament(dep, gasit);
        
        if(gasit) {
            ales.adaugaAngajat(a);
            ok = true;
        }

    } while (!ok);
}


int main(){

    char nume_fisier[100];
    std::cout << "Nume fisier cu viitorii angajati: ";
    std::cin >> nume_fisier;
    std::ifstream fin(nume_fisier);

    char numeAng[100], dep[100];
    int idAng;
    double salariuAng;
    char separator;

    //adaugarea din fisier, se apeleaza functia de mai sus
    while (fin.getline(numeAng, sizeof(numeAng), '%')) {

        char* start = numeAng;
        while(*start == ' ' || *start == '\n' || *start == '\r') {
            start++;
        }
        if (strlen(start) > 0 && start[strlen(start) - 1] == ' ') {
            start[strlen(start) - 1] = '\0';
        }
        if (fin >> idAng >> separator >> salariuAng) {
            Angajat a(start, idAng, salariuAng);
            adaugaDinFisier(a);
            fin.ignore(1000, '\n');
        }

    }
    fin.close();

    //inceputul gestiunii propriu-zise
    std::cout << "\nBine ai venit, e timpul sa gestionezi firma la care lucrezi.\n\n";

    int optiune;
    double procent;
    bool gasit;

    do {
        std::cout << "0: Iesire din program\n";
        std::cout << "1: Angajeaza persoana\n";
        std::cout << "2: Concediaza persoana\n";
        std::cout << "3: Afiseaza departament\n";
        std::cout << "4: Mareste salariu\n";
        std::cout << "5: Scade salariu\n";
        std::cout << "6: Verifica viabilitate proiect\n";
        std::cout << "\nAlege optiune (numarul): ";
        std::cin >> optiune;
        std::cout << "\n";

        switch (optiune) {
            case 0: 
                //iesirea din program
                std::cout << "Maine e o noua zi";
                break;
            case 1: {
                //adaugarea de angajat la un departament
                std::cout << "Nume persoana: ";
                std::cin.ignore();
                std::cin.getline(numeAng, 100);
                std::cout << "Id persoana: ";
                std::cin >> idAng;
                std::cout << "Salariu persoana: ";
                std::cin >> salariuAng;
                std::cout << "Departament (SD - HR - LG - DG): ";
                std::cin >> dep;
                Angajat a(numeAng, idAng, salariuAng);
                Departament& d1 = verificareDepartament(dep, gasit);
                if (gasit) {
                    d1.adaugaAngajat(a);
                }
                std::cout << "\n~" << numeAng <<"~ a fost angajat cu succes!\n\n";
                break;
            }

            case 2: {
                //stergerea de angajat dintr-un departament
                std::cout << "Alege departament (SD - HR - LG - DG): ";
                std::cin >> dep;
                std::cout << "Introdu id-ul angajatului: ";
                std::cin >> idAng;
                Departament& d2 = verificareDepartament(dep, gasit);
                if (gasit) {
                    d2.stergeAngajat(idAng);
                }
                std::cout << "\n";
                break;
            }

            case 3: {
                //afisarea unui departament
                std::cout << "Alege departament (SD - HR - LG - DG): ";
                std::cin >> dep;
                Departament& d3 = verificareDepartament(dep, gasit);
                if (gasit) {
                    std::cout << "\n" << d3 << "\n";
                }
                break;
            }

            case 4: {
                //marirea unui salariu cu un procent
                std::cout << "Alege departament (SD - HR - LG - DG): ";
                std::cin >> dep;
                std::cout << "Introdu id-ul angajatului: ";
                std::cin >> idAng;
                std::cout << "Procent marire: ";
                std::cin >> procent;
                Departament& d4 = verificareDepartament(dep, gasit);
                if (gasit) {
                    d4.maresteSalariuId(procent, idAng);
                }
                std::cout << "\n";
                break;
            }
            case 5: {
                //scaderea unui salariu cu un procent
                std::cout << "Alege departament(SD - HR - LG - DG): ";
                std::cin >> dep;
                std::cout << "Introdu id-ul angajatului: ";
                std::cin >> idAng;
                std::cout << "Procent scadere: ";
                std::cin >> procent;
                Departament& d5 = verificareDepartament(dep, gasit);
                if (gasit) {
                    d5.scadereSalariuId(procent, idAng);
                }
                std::cout << "\n";
                break;
            }
            
            case 6: {
                //verificarea viabilitatii unui proiect, proiect introdus de user de la tastatura
                char numeProiect[100];
                double buget;
                std::cout << "Nume proiect: ";
                std::cin.ignore();
                std::cin.getline(numeProiect, 100);
                std::cout << "Buget proiect: ";
                std::cin >> buget;
                std::cout << "Alege departament (SD - HR - LG - DG): ";
                std::cin >> dep;
                Departament& d6 = verificareDepartament(dep, gasit);
                if (gasit) {
                    Proiect p(numeProiect, buget);
                    d6.viabiliateProiect(p);
                }
                std::cout << "\n";
                break;
            }

            default:
                //optiune default in cazul in care se alege un numar nu intre 0-5
                if (optiune != 0) {
                    std::cout << "Optiune invalida\n\n";
                }
                
        }
    } while (optiune != 0) ;

    return 0;
}
