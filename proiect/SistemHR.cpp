#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include "angajati.h"
#include "proiect.h"
#include "departament.h"
#include "angajatFullTime.h"
#include "angajatPartTime.h"
#include "contractor.h"
#include "exceptii.h"
#include "intern.h"

//functie care verifica daca un departament exista
Departament& verificareDepartament (const char* dep, std::vector<Departament>& departamente, bool& gasit){
    gasit = true;
    if (strcmp(dep, "SD") == 0) return departamente[0];
    if (strcmp(dep, "HR") == 0) return departamente[1];
    if (strcmp(dep, "LG") == 0) return departamente[2];
    if (strcmp(dep, "DG") == 0) return departamente[3];

    gasit = false;
    std::cout << "Nu exista acest departament\n";
    return departamente[0]; //returnare aleatorie
}

//functie de adaugare angajati din fisier de intrare ( OBLIGATORIU LA INCEPUT PENTRU A AVEA CATIVA ANGAJATI IN DEPARTAMENTE !!!)
void adaugaDinFisier(const Angajat& a, std::vector<Departament>& departamente) {
    char dep[100];
    bool ok = false;
    do{
        std::cout << "Angajeaza pe ~" << a << "~ intr-un departament -> SD - HR - LG - DG: ";
        std::cin >> dep;
        bool gasit = false;

        Departament& ales = verificareDepartament(dep, departamente, gasit);
        
        if(gasit) {
            ales.adaugaAngajat(a);
            ok = true;
        }

    } while (!ok);
}


int main(){

    std::vector<Departament> departamente = { 
        Departament("Software Development"),
        Departament("Human Resources"),
        Departament("Logistics"),
        Departament("Design")
    };

    char nume_fisier[100];
    std::cout << "Nume fisier cu viitorii angajati: ";
    std::cin >> nume_fisier;
    std::ifstream fin(nume_fisier);

    char numeAng[100], dep[100], tipContract[100];
    int idAng, zileConcediu, aniVechime, orePerSaptamana, zileLucrate, durataInternship;;
    double salariuAng, salariuPerOra, salariuZilnic, stipendiu;
    char separator;
    std::string dateExpirareContract, numeMentor;

    //adaugarea din fisier, se apeleaza functia de mai sus
    while (fin.getline(tipContract, sizeof(tipContract), '%')) {

        char* start = tipContract;
        while(*start == ' ' || *start == '\n' || *start == '\r') {
            start++;
        }
        if (strlen(start) > 0 && start[strlen(start) - 1] == ' ') {
            start[strlen(start) - 1] = '\0';
        }
        if (strcmp(start, "Full Time") == 0) {
            fin.getline(numeAng, sizeof(numeAng), '%');
            fin >> idAng >> separator >> salariuAng >> separator >> zileConcediu >> separator >> aniVechime;
            AngajatFullTime a(numeAng, idAng, salariuAng, zileConcediu, aniVechime);
            adaugaDinFisier(a, departamente);
            fin.ignore(1000, '\n');
        }
        else if (strcmp(start, "Part Time") == 0) {
            fin.getline(numeAng, sizeof(numeAng), '%');
            fin >> idAng >> separator >> orePerSaptamana >> separator >> salariuPerOra;
            AngajatPartTime a(numeAng, idAng, orePerSaptamana, salariuPerOra);
            adaugaDinFisier(a, departamente);
            fin.ignore(1000, '\n');
        }
        else if (strcmp(start, "Contractor") == 0) {
            fin.getline(numeAng, sizeof(numeAng), '%');
            fin >> idAng >> separator >> salariuZilnic >> separator >> zileLucrate >> separator >> dateExpirareContract;
            Contractor a(numeAng, idAng, salariuZilnic, zileLucrate, dateExpirareContract);
            adaugaDinFisier(a, departamente);
            fin.ignore(1000, '\n');
        }
        else if (strcmp(start, "Intern") == 0) {
            fin.getline(numeAng, sizeof(numeAng), '%');
            fin >> idAng >> separator >> stipendiu >> separator >> durataInternship >> separator;
            fin.ignore(1000, '\n');
            std::getline(fin, numeMentor);
            Intern a(numeAng, idAng, stipendiu, durataInternship, numeMentor);
            adaugaDinFisier(a, departamente);
        }
    }
    fin.close();

    //inceputul gestiunii propriu-zise
    std::cout << "\nBine ai venit, e timpul sa gestionezi firma la care lucrezi.\n\n";

    int optiune;
    int optiuneAngajat;
    double procent;
    bool gasit;

    do {
        std::cout << "0: Iesire din program\n";
        std::cout << "1: Angajeaza persoana\n";
        std::cout << "2: Concediaza persoana\n";
        std::cout << "3: Baza de date\n";
        std::cout << "4: Mareste salariu\n";
        std::cout << "5: Scade salariu\n";
        std::cout << "6: Verifica viabilitate proiect\n";
        std::cout << "7: Promoveaza la Full Time\n";
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
                Angajat* a = nullptr;
                std::cout << "Nume persoana: ";
                std::cin.ignore();
                std::cin.getline(numeAng, 100);
                std::cout << "Id persoana: ";
                std::cin >> idAng;
                std::cout <<"Tip angajat\n1 - Full Time\n2 - Part Time\n3 - Contractor\n4 - Internship\n";
                std::cout << "\nAlege optiune (numarul): ";
                std::cin >> optiuneAngajat;
                switch (optiuneAngajat) {
                    case 1: {
                        std::cout << "Salariu: ";
                        std::cin >> salariuAng;
                        std::cout << "Zile concediu: ";
                        std::cin >> zileConcediu;
                        std::cout << "Ani Vechime: ";
                        std::cin >> aniVechime;
                        a = new AngajatFullTime(numeAng, idAng, salariuAng, zileConcediu, aniVechime);
                        break;
                    }
                    case 2: {
                        std::cout << "Ore pe Saptamana: ";
                        std::cin >> orePerSaptamana;
                        std::cout << "Salariu pe ora: ";
                        std::cin >> salariuPerOra;
                        a = new AngajatPartTime(numeAng, idAng, orePerSaptamana, salariuPerOra);
                        break;
                    }
                    case 3: {
                        std::cout << "Salariu zilnic: ";
                        std::cin >> salariuZilnic;
                        std::cout << "Zile lucrate: ";
                        std::cin >> zileLucrate;
                        std::cout << "Data expirare contract (format: DD-MM-YYYY): ";
                        std::cin >> dateExpirareContract;
                        a = new Contractor(numeAng, idAng, salariuZilnic, zileLucrate, dateExpirareContract);
                        break;
                    }
                    case 4: {
                        std::cout << "Stipendiu: ";
                        std::cin >> stipendiu;
                        std::cout << "Durata internship (in luni): ";
                        std::cin >> durataInternship;
                        std::cout << "Nume mentor: ";
                        std::cin.ignore();
                        std::getline(std::cin, numeMentor);
                        a = new Intern(numeAng, idAng, stipendiu, durataInternship, numeMentor);
                        break;
                    }
                    default:
                        std::cout << "Optiune invalida pentru tip angajat\n";
                        continue;
                }
                if (a != nullptr) {
                    std::cout << "Departament (SD - HR - LG - DG): ";
                    std::cin >> dep;
                    
                    Departament& d1 = verificareDepartament(dep, departamente, gasit);
                    if (gasit) {
                        d1.adaugaAngajat(*a);
                        std::cout << "\n~" << numeAng <<"~ a fost angajat cu succes!\n\n";
                    }
                delete a;
                }
                break;
            }

            case 2: {
                //stergerea de angajat dintr-un departament
                try {
                    std::cout << "Alege departament (SD - HR - LG - DG): ";
                    std::cin >> dep;
                    std::cout << "Introdu id-ul angajatului: ";
                    std::cin >> idAng;
                    Departament& d2 = verificareDepartament(dep, departamente, gasit);
                    if (gasit) {
                        d2.stergeAngajat(idAng);
                    }
                    std::cout << "\n";
                } catch (const ExceptieAngajatNegasit& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }

            case 3: {
                //baza de date
                std::cout << "Total angajati in firma: " << Angajat::getTotalNumarAngajati() << "\n\n";
                std::cout << "Afisare\n1 - Toata firma\n2 - UN singur departament";
                std::cout << "Alege optiune (numarul): ";
                std::cin >> optiuneAngajat;
                switch (optiuneAngajat) {
                    case 1: {
                        std::cout << departamente[0] << '\n';
                        std::cout << departamente[1] << '\n';
                        std::cout << departamente[2] << '\n';
                        std::cout << departamente[3] << '\n';
                        break;
                    }
                    
                    case 2: {
                        std::cout << "Alege departament (SD - HR - LG - DG): ";
                        std::cin >> dep;
                        Departament& d3 = verificareDepartament(dep, departamente, gasit);
                        if (gasit) {
                            std::cout << "\n" << d3 << "\n";
                        }
                        break;
                    }
                    
                    default: {
                        std::cout << "Optiune invalida";
                        continue;
                    }
                }
                break;   
            }

            case 4: {
                //marirea unui salariu cu un procent
                try { 
                    std::cout << "Alege departament (SD - HR - LG - DG): ";
                    std::cin >> dep;
                    std::cout << "Introdu id-ul angajatului: ";
                    std::cin >> idAng;
                    std::cout << "Procent marire: ";
                    std::cin >> procent;
                    Departament& d4 = verificareDepartament(dep, departamente, gasit);
                    if (gasit) {
                        d4.maresteSalariuId(procent, idAng);
                    }
                    std::cout << "\n";
                } catch (const ExceptieAngajatNegasit& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            case 5: {
                //scaderea unui salariu cu un procent
                try {
                    std::cout << "Alege departament(SD - HR - LG - DG): ";
                    std::cin >> dep;
                    std::cout << "Introdu id-ul angajatului: ";
                    std::cin >> idAng;
                    std::cout << "Procent scadere: ";
                    std::cin >> procent;
                    Departament& d5 = verificareDepartament(dep, departamente, gasit);
                    if (gasit) {
                        d5.scadereSalariuId(procent, idAng);
                    }
                    std::cout << "\n";
                } catch (const ExceptieAngajatNegasit& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }
            
            case 6: {
                //verificarea viabilitatii unui proiect, proiect introdus de user de la tastatura
                char numeProiect[100];
                double buget;
                try {
                    std::cout << "Nume proiect: ";
                    std::cin.ignore();
                    std::cin.getline(numeProiect, 100);
                    std::cout << "Buget proiect: ";
                    std::cin >> buget;
                    std::cout << "Alege departament (SD - HR - LG - DG): ";
                    std::cin >> dep;
                    Departament& d6 = verificareDepartament(dep, departamente, gasit);
                    if (gasit) {
                        Proiect p(numeProiect, buget);
                        d6.viabiliateProiect(p);
                    }
                    std::cout << "\n";
                } catch (const ExceptieProiectNeviabil& e){
                    std::cout << e.what() << '\n';                
                }
                break;
            }

            case 7: {
                try {
                    std::cout << "Tip angajat\n1 - Cotractor\n2 - Part-Time\n";
                    std::cout << "Alege optiune (numarul): ";
                    std::cin >> optiuneAngajat;
                    switch (optiuneAngajat) {
                        case 1: {
                            std::cout << "Alege departament (SD - HR - LG - DG): ";
                            std::cin >> dep;
                            std::cout << "Introdu id-ul angajatului: ";
                            std::cin >> idAng;
                            Departament& d7 = verificareDepartament(dep, departamente, gasit);
                            if (gasit) {
                                d7.promoveazaContractor(idAng);
                            }
                            std::cout << "\n";
                            break;
                        }
                        case 2: {
                            std::cout << "Alege departament (SD - HR - LG - DG): ";
                            std::cin >> dep;
                            std::cout << "Introdu id-ul angajatului: ";
                            std::cin >> idAng;
                            Departament& d7 = verificareDepartament(dep, departamente, gasit);
                            if (gasit) {
                                d7.promoveazaPartTime(idAng);
                            }
                            std::cout << "\n";
                            break;
                        }
                        default: {
                            std::cout << "Optiune invalida pentru tip angajat\n";
                            continue;
                        }
                    }
                } catch (const ExceptieAngajatNegasit& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            }

            default:
                //optiune default in cazul in care se alege un numar nu intre 0-7
                if (optiune != 0) {
                    std::cout << "Optiune invalida\n\n";
                }
            
        }
    } while (optiune != 0) ;

    return 0;
}