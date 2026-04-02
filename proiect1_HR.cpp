/* GESTIUNE RESURSE UMANE - trebuie sa gestionezi firma la care lucrezi
    ai la dispozitie urmatoarele operatii:
        1. adauga angajat
        2. concedieaza angajat 
        3. afiseaza departamentul
        4. mareste salariul unui angajat
        5. verifica viabilitatea unui proiect in functie de salariile angajatilor
    
    la inceput trebuie creat un fisier cu niste angajati predefiniti (nu neaparat, introducerea de string = fisier inexistent 
    va porni programul fara angajati noi), fiecare scris pe cate o linie, de forma:
        " nume complet % id % salariu ", dupa care acestia vor fi adaugati in departamente predefinite: SD - HR - LG - DG

    s-au definit 3 clase: Angajat, Proiect, Departament
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>

//pointer sir de caractere
char* copiazaSir(const char* sursa) {
    if (!sursa) return nullptr;
    char* dest = new char[strlen(sursa) + 1];
    strcpy(dest, sursa);
    return dest;
}

class Angajat {

private:

    char* nume;
    int id;
    double salariu;

public:

    //constructori/destructori
    Angajat (const char* numeAng, int idAng, double salariuAng) 
    : id(idAng), salariu(salariuAng) { 
        nume = copiazaSir(numeAng); 
    }

    Angajat(const Angajat& altul) 
    : id(altul.id), salariu(altul.salariu) {
        nume = copiazaSir(altul.nume);
    }

    Angajat& operator=(const Angajat& altul) {
        if (this != &altul) {
            delete[] nume;
            nume = copiazaSir(altul.nume);
            id = altul.id;
            salariu = altul.salariu;
        }
        return *this;
    }

    ~Angajat() {
        delete[] nume;
    }

    const char* getNume() const { 
        return nume; 
    }

    int getId() const { 
        return id;              //getteri
    } 

    double getSalariu() const { 
        return salariu; 
    }

    // afisare angajat
    friend std::ostream& operator<<(std::ostream& os, const Angajat& a){
        os << a.nume << " (#" << a.id << ") | Salariu: " << a.salariu;
        return os;
    }

    //functie de marire a salariului
    void maresteSalariu(double procent) {
        salariu += (salariu * procent) / 100.0;
        std::cout << "\nSalariu nou: " << salariu << "\n";
    }

    // functie de scadere a salariului
    void scadeSalariu(double procent) {
        salariu -= (salariu * procent) / 100.0;
        std::cout << "\nSalariu nou: " << salariu << "\n";
    }
};

class Proiect {

private:

    char* numeProiect;
    double bugetAlocat;

public: 

    //constructori/destructori
    Proiect (const char* nume, double buget) 
    : bugetAlocat(buget) {
        numeProiect = copiazaSir(nume);
    }

    Proiect (const Proiect& altul) 
    : bugetAlocat(altul.bugetAlocat) {
        numeProiect = copiazaSir(altul.numeProiect);
    }

    Proiect& operator=(const Proiect& altul) {
        if (this != &altul) {
            delete[] numeProiect;
            numeProiect = copiazaSir(altul.numeProiect);
            bugetAlocat = altul.bugetAlocat;
        }
        return *this;
    }

    ~Proiect() {
        delete[] numeProiect;
    }

    double getBuget() const { 
        return bugetAlocat;              //getteri
    }    
                                        
    const char* getNume() const { 
        return numeProiect; 
    }

    //afisare proiect
    friend std::ostream& operator<<(std::ostream& os, const Proiect& prc){
        os << "Proiect: " << prc.numeProiect << " | Buget: " << prc.bugetAlocat;
        return os;
    }

};

class Departament {

private:

    char* numeDepartament;
    std::vector <Angajat> echipa;

    //functie privata pentru taxa de logistica la proiect
    double taxeLogistica(double totalSalarii) const {
        return totalSalarii * 1.2;  //taxa de logistica de 20%
    }

public: 

    //constructori/destructori
    Departament (const char* numeDep) { 
        numeDepartament = copiazaSir(numeDep);
    }

    Departament (const Departament& altul) 
    : echipa(altul.echipa) {
        numeDepartament = copiazaSir(altul.numeDepartament);
    }

    Departament& operator=(const Departament& altul) {
        if (this != &altul) {
            delete[] numeDepartament;
            numeDepartament = copiazaSir(altul.numeDepartament);
            echipa = altul.echipa;
        }
        return *this;
    }

    ~Departament() {
        delete[] numeDepartament;
    }

    std::string getNume() const { 
        return numeDepartament; 
    } //getter

    //functie de adaugare angajat in departament
    void adaugaAngajat (const Angajat& a) {
        echipa.push_back(a);
    }

    //functie de stergere angajat din departament
    void stergeAngajat(int id) {
        bool gasit = false;
        for (auto i = echipa.begin(); i != echipa.end(); ++i) {
            if (i -> getId() == id) {
                std::cout <<"\n~" << i -> getNume() << "~ a fost concediat cu succes!\n";
                echipa.erase(i);
                gasit = true;
                break;
            }
        }
        if (!gasit) {
            std::cout << "Angajatul cu ID #" << id << " nu exista.\n";
        }
    }

    //afisare departament
    friend std::ostream& operator<<(std::ostream& os, const Departament& dep) {
        os << dep.numeDepartament << ":\n";
        for (const auto& ang : dep.echipa) {
            os << ang << "\n";
        }
        return os;
    }

    //functie de calcul a costului unui proiect
    double costProiectEchipa() const {
        double total = 0;
        for (const auto& ang : echipa){
            total += ang.getSalariu();
        }
        return taxeLogistica(total);
    }

    //functie care verifica daca un departament poate face proiectul ( in functie de bugetul alocat )
    void viabiliateProiect (const Proiect& p) const{
        double costProiect = costProiectEchipa();
        if (costProiect > p.getBuget()) {
            std::cout << "\nProiectul ~" << p.getNume() << "~ nu este realizabil din punct de vedere financiar.\n";
        }
        else {
            std::cout << "\nProiectul ~" << p.getNume() << "~ este realizabil. Buget ramas: " << p.getBuget() - costProiect << std::endl;
        }
    }

    // functie de marire a salariului
    void maresteSalariuId(double procent, int id){
        bool gasit = false;
        for (auto i = echipa.begin(); i != echipa.end(); ++i) {
            if (i -> getId() == id) {
                i -> maresteSalariu(procent);
                gasit = true;
                break; 
            }
        }
        if (!gasit) {
            std::cout << "Angajatul cu ID #" << id << " nu exista.\n";
        }
    }

    //functie de scadere a salariului
    void scadereSalariuId(double procent, int id){
        bool gasit = false;
        for (auto i = echipa.begin(); i != echipa.end(); ++i) {
            if (i -> getId() == id) {
                i -> scadeSalariu(procent); 
                gasit = true;
                break; 
            }
        }
        if (!gasit) {
            std::cout << "Angajatul cu ID #" << id << " nu exista.\n";
        }
    }

};

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


    //afisare provizorie pentru prezentare
    Angajat a1("Angajat 1", 1, 4000);
    Angajat a2("Angajat 2", 2, 5000);
    Angajat a3("Angajat 3", 3, 2500);
    Angajat a4("Angjat 4", 4, 2000);
    std::cout << a1 << "\n" << a2 << "\n" << a3 << "\n" << a4 << "\n\n";
    SD.adaugaAngajat(a1);
    SD.adaugaAngajat(a2);
    HR.adaugaAngajat(a3);
    HR.adaugaAngajat(a4);
    std::cout << SD << "\n" << HR << "\n";
    Proiect p1("Aplicatie Mobila", 7000);
    Proiect p2("Recrutari", 8000);
    std::cout << p1 << "\n" << p2 << "\n";
    SD.viabiliateProiect(p1);
    HR.viabiliateProiect(p2);


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
