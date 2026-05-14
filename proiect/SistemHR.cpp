#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>
#include "angajati.h"
#include "proiect.h"
#include "departament.h"
#include "angajatFullTime.h"
#include "angajatPartTime.h"
#include "contractor.h"
#include "exceptii.h"
#include "intern.h"
#include "angajatFactory.h"
#include "sistem.h"


int main(){

    char nume_fisier[100];
    std::cout << "Nume fisier cu viitorii angajati: ";
    std::cin >> nume_fisier;
    std::ifstream fin(nume_fisier);

    char numeAng[100], dep[100], tipContract[100];
    int idAng, zileConcediu, aniVechime, orePerSaptamana, zileLucrate, durataInternship;;
    double salariuAng, salariuPerOra, salariuZilnic, stipendiu;
    char separator;
    std::string dateExpirareContract, numeMentor;

    std::vector<Angajat*> angajati;
    SistemHR& sistem = SistemHR::getInstance();

    try {
        if (!fin.is_open()) {
            throw ExceptieFisier(nume_fisier);
        }

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
            angajati.push_back(AngajatFactory::creeazaFullTime(numeAng, idAng, salariuAng, zileConcediu, aniVechime));
            fin.ignore(1000, '\n');
        }
        else if (strcmp(start, "Part Time") == 0) {
            fin.getline(numeAng, sizeof(numeAng), '%');
            fin >> idAng >> separator >> orePerSaptamana >> separator >> salariuPerOra;
            angajati.push_back(AngajatFactory::creeazaPartTime(numeAng, idAng, orePerSaptamana, salariuPerOra));
            fin.ignore(1000, '\n');
        }
        else if (strcmp(start, "Contractor") == 0) {
            fin.getline(numeAng, sizeof(numeAng), '%');
            fin >> idAng >> separator >> salariuZilnic >> separator >> zileLucrate >> separator >> dateExpirareContract;
            angajati.push_back(AngajatFactory::creeazaContractor(numeAng, idAng, salariuZilnic, zileLucrate, dateExpirareContract));
            fin.ignore(1000, '\n');
        }
        else if (strcmp(start, "Intern") == 0) {
            fin.getline(numeAng, sizeof(numeAng), '%');
            fin >> idAng >> separator >> stipendiu >> separator >> durataInternship >> separator;
            fin.ignore(1000, '\n');
            std::getline(fin, numeMentor);
            angajati.push_back(AngajatFactory::creeazaIntern(numeAng, idAng, stipendiu, durataInternship, numeMentor));
        }
    }
    fin.close();

    } catch (const ExceptieFisier& e) {
        std::cout << '\n' << e.what() << "\n\n";
    }


    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(angajati.begin(), angajati.end(), g);

    size_t nrAngajatiSelectati = 60; 
    if (angajati.size() < nrAngajatiSelectati) {
        nrAngajatiSelectati = angajati.size();
    }

    for (int i = 0; i < nrAngajatiSelectati; i++) {
        sistem.getDepartamente()[i % 4].adaugaAngajat(*angajati[i]);
    }

    for (auto* a : angajati) {
        delete a;
    }
    angajati.clear();

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

        try {
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
                if (sistem.existaID(idAng)) {
                    throw ExceptieIdDuplicat(idAng);
                }
                std::cout <<"\nTip angajat\n1 - Full Time\n2 - Part Time\n3 - Contractor\n4 - Internship\n";
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
                        a = AngajatFactory::creeazaFullTime(numeAng, idAng, salariuAng, zileConcediu, aniVechime);
                        break;
                    }
                    case 2: {
                        std::cout << "Ore pe Saptamana: ";
                        std::cin >> orePerSaptamana;
                        std::cout << "Salariu pe ora: ";
                        std::cin >> salariuPerOra;
                        a = AngajatFactory::creeazaPartTime(numeAng, idAng, orePerSaptamana, salariuPerOra);
                        break;
                    }
                    case 3: {
                        std::cout << "Salariu zilnic: ";
                        std::cin >> salariuZilnic;
                        std::cout << "Zile lucrate: ";
                        std::cin >> zileLucrate;
                        std::cout << "Data expirare contract (format: DD-MM-YYYY): ";
                        std::cin >> dateExpirareContract;
                        a = AngajatFactory::creeazaContractor(numeAng, idAng, salariuZilnic, zileLucrate, dateExpirareContract);
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
                        a = AngajatFactory::creeazaIntern(numeAng, idAng, stipendiu, durataInternship, numeMentor);
                        break;
                    }
                    default:
                        std::cout << "Optiune invalida pentru tip angajat\n\n";
                        continue;
                }
                if (a != nullptr) {
                    std::cout << "Departament (SD - HR - LG - DG): ";
                    std::cin >> dep;
                    
                    Departament& d1 = sistem.cautaDepartament(dep, gasit);
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
                std::cout << "Alege departament (SD - HR - LG - DG): ";
                std::cin >> dep;
                std::cout << "Introdu id-ul angajatului: ";
                std::cin >> idAng;
                Departament& d2 = sistem.cautaDepartament(dep, gasit);
                if (gasit) {
                    d2.stergeAngajat(idAng);
                }
                std::cout << "\n";
                break;
            }

            case 3: {
                //baza de date
                std::cout << "Total angajati in firma: " << Angajat::getTotalNumarAngajati() << "\n\n";
                std::cout << "Afisare\n1 - Toata firma\n2 - Un singur departament\n\n";
                std::cout << "Alege optiune (numarul): ";
                std::cin >> optiuneAngajat;
                switch (optiuneAngajat) {
                    case 1: {
                        std::cout << sistem.getDepartamente()[0] << '\n';
                        std::cout << sistem.getDepartamente()[1] << '\n';
                        std::cout << sistem.getDepartamente()[2] << '\n';
                        std::cout << sistem.getDepartamente()[3] << '\n';
                        break;
                    }
                    
                    case 2: {
                        std::cout << "Alege departament (SD - HR - LG - DG): ";
                        std::cin >> dep;
                        Departament& d3 = sistem.cautaDepartament(dep, gasit);
                        if (gasit) {
                            std::cout << "\n" << d3 << "\n";
                        }
                        break;
                    }
                    
                    default: {
                        std::cout << "Optiune invalida\n\n";
                        continue;
                    }
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
                Departament& d4 = sistem.cautaDepartament(dep, gasit);
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
                Departament& d5 = sistem.cautaDepartament(dep, gasit);
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
                Departament& d6 = sistem.cautaDepartament(dep, gasit);
                if (gasit) {
                    Proiect p(numeProiect, buget);
                    d6.viabilitateProiect(p);
                }
                std::cout << "\n";
                break;
            }

            case 7: {
                std::cout << "Tip angajat\n1 - Contractor\n2 - Part-Time\n\n";
                std::cout << "Alege optiune (numarul): ";
                std::cin >> optiuneAngajat;
                switch (optiuneAngajat) {
                    case 1: {
                        std::cout << "Alege departament (SD - HR - LG - DG): ";
                        std::cin >> dep;
                        std::cout << "Introdu id-ul angajatului: ";
                        std::cin >> idAng;
                        Departament& d7 = sistem.cautaDepartament(dep, gasit);
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
                        Departament& d7 = sistem.cautaDepartament(dep, gasit);
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
                break;
            }

            default:
                //optiune default in cazul in care se alege un numar nu intre 0-7
                if (optiune != 0) {
                    std::cout << "Optiune invalida\n\n";
                }
            
        }
        } catch (const ExceptieHR& e) {
            std::cout << '\n' <<  e.what() << "\n\n";
        } catch (const std::exception& e) {
            std::cout << "\n" << "Eroare neasteptata: " << e.what() << "\n\n";
        }       
    } while (optiune != 0) ;

    return 0;
}