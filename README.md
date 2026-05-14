# Sistem de Gestiune a Resurselor Umane

Un sistem interactiv de management HR implementat în C++, care permite unui HR-ist să gestioneze angajații, departamentele și proiectele unei firme. Proiectul demonstrează concepte fundamentale și avansate de programare orientată pe obiecte.

---

## Structura proiectului
proiect/
├── angajati.h / angajati.cpp        # Clasa abstracta de baza
├── angajatFullTime.h / .cpp         # Angajat cu norma intreaga
├── angajatPartTime.h / .cpp         # Angajat cu timp partial
├── contractor.h / .cpp              # Angajat tip contractor
├── intern.h / .cpp                  # Stagiar (a 4-a derivata)
├── departament.h / .cpp             # Container de angajati
├── proiect.h                        # Clasa template Proiect<T>
├── angajatFactory.h / .cpp          # Design pattern Factory
├── sistem.h / .cpp                  # Design pattern Singleton
├── exceptii.h                       # Ierarhie de exceptii
├── utile.h                          # Functii utilitare
├── utileTemplate.h                  # Functii template libere
└── SistemHR.cpp                     # Punctul de intrare (main)

---

## Concepte OOP implementate

### 1. Ierarhie de mostenire
Clasa abstracta `Angajat` sta la baza intregii ierarhii. Nu poate fi instantiata direct — defineste un "contract" pe care toate tipurile de angajati trebuie sa il respecte prin functii virtuale pure:

- `calculeazaSalariu()` — fiecare tip calculeaza altfel
- `getTipContract()` — returneaza tipul contractului
- `clone()` — pattern virtual constructor, necesar pentru copiere corecta in container
- `maresteSalariu()` / `scadeSalariu()` — modifica atributul specific fiecarui tip

```cpp
class Angajat {
    virtual double calculeazaSalariu() const = 0;
    virtual Angajat* clone() const = 0;
    // ...
};

class AngajatFullTime : public Angajat { /* salariu fix + bonus vechime */ };
class AngajatPartTime : public Angajat { /* ore/sapt * tarif orar * 4 */ };
class Contractor      : public Angajat { /* tarif zilnic * zile lucrate */ };
class Intern          : public Angajat { /* stipendiu fix lunar */ };
```

### 2. Polimorfism
`Departament` tine un `vector<Angajat*>` si apeleaza functiile virtual prin pointer de baza:

```cpp
double Departament::costProiectEchipa() const {
    double total = 0;
    for (const auto* ang : echipa)
        total += ang->calculeazaSalariu();  // apel polimorfic
    return taxeLogistica(total);
}
```

### 3. Pattern NVI (Non-Virtual Interface)
Afisarea angajatilor foloseste pattern-ul NVI — `operator<<` public apeleaza `print()` privat virtual:

```cpp
friend std::ostream& operator<<(std::ostream& os, const Angajat& a) {
    a.print(os);
    return os;
}
```

### 4. Copiere corecta (Rule of Three + clone)
`Departament` implementeaza constructor de copiere, `operator=` si destructor pentru a gestiona corect memoria dinamica. Copierea angajatilor se face prin `clone()` pentru a evita shallow copy.

### 5. Ierarhie de exceptii
Toate erorile din sistem deriva din `ExceptieHR`:
std::exception
├── ExceptieFisier              // probleme la deschidere fisier
└── ExceptieHR
├── ExceptieSalariuInvalid   // salariu < minim legal
├── ExceptieAngajatNegasit   // ID inexistent
├── ExceptieIdDuplicat       // ID deja folosit
├── ExceptieTipGresit        // dynamic_cast esuat
└── ExceptieProiectNeviabil  // buget insuficient

### 6. Membrii statici
Fiecare clasa derivata are un minim legal propriu ca membru `static const`. `Angajat` tine un contor global de angajati activi, incrementat automat in constructori.

### 7. dynamic_cast
Promovarea unui Contractor sau PartTime la FullTime foloseste `dynamic_cast` pentru a verifica tipul la runtime.

---

## Concepte avansate (Tema 3)

### 8. Clasa template Proiect<T>
`Proiect` a fost transformat in clasa template — bugetul poate fi orice tip numeric:

```cpp
template <typename TipBuget>
class Proiect {
    TipBuget bugetAlocat;
    // ...
};

// utilizare
Proiect<double> p1("Site web", 15000.50);    // buget cu zecimale
Proiect<int> p2("Restructurare", 50000);      // buget rotund
```

La verificarea viabilitatii unui proiect, userul poate alege tipul bugetului.

### 9. Functie template membra
`Departament::viabilitateProiect<T>` accepta proiecte de orice tip:

```cpp
template <typename TipBuget>
void viabilitateProiect(const Proiect<TipBuget>& p) const {
    double costProiect = costProiectEchipa();
    if (costProiect > p.getBuget())
        throw ExceptieProiectNeviabil(p.getNume());
    // ...
}
```

### 10. Functie template libera
`numaraDeTip<TipDorit, TipBaza>` foloseste templates plus `dynamic_cast` pentru a numara angajati de un anumit tip concret:

```cpp
template <typename TipDorit, typename TipBaza>
int numaraDeTip(const std::vector<TipBaza*>& vec) {
    int count = 0;
    for (const auto* elem : vec)
        if (dynamic_cast<const TipDorit*>(elem) != nullptr)
            count++;
    return count;
}

// utilizare
int nrContractori = numaraDeTip<Contractor>(departament.getEchipa());
```

### 11. Design Pattern: Factory
`AngajatFactory` centralizeaza construirea diferitelor tipuri de angajati. Astfel, `main` nu mai depinde direct de tipurile concrete:

```cpp
class AngajatFactory {
public:
    static Angajat* creeazaFullTime(const char* nume, int id, double sal, int zile, int ani);
    static Angajat* creeazaPartTime(const char* nume, int id, int ore, double tarif);
    static Angajat* creeazaContractor(const char* nume, int id, double tarif, int zile, const std::string& exp);
    static Angajat* creeazaIntern(const char* nume, int id, double stip, int durata, const std::string& mentor);
};
```

### 12. Design Pattern: Singleton
`SistemHR` exista ca o singura instanta in tot programul. Gestioneaza centralizat cele 4 departamente si ofera functionalitati precum cautare departament si validare ID unic la nivel de firma:

```cpp
class SistemHR {
private:
    std::vector<Departament> departamente;
    SistemHR();  // constructor privat
public:
    SistemHR(const SistemHR&) = delete;
    SistemHR& operator=(const SistemHR&) = delete;
    static SistemHR& getInstance();
    bool existaID(int id) const;
    // ...
};

// utilizare
SistemHR& sistem = SistemHR::getInstance();
```

---

## Functionalitati

| Optiune | Descriere |
|---------|-----------|
| `1` | Angajeaza o persoana (Full Time / Part Time / Contractor / Intern) |
| `2` | Concediaza un angajat dupa ID |
| `3` | Baza de date — afiseaza firma, departament, sau statistici pe tipuri |
| `4` | Mareste salariul unui angajat cu un procent |
| `5` | Scade salariul unui angajat cu un procent |
| `6` | Verifica viabilitatea financiara a unui proiect (buget int sau double) |
| `7` | Promoveaza un Contractor sau PartTime la Full Time |
| `0` | Iesire din program |

---

## Selectie aleatoare la pornire

La pornire, programul:
1. Citeste 100 de angajati din fisierul de intrare
2. Amesteca aleator vectorul cu `std::shuffle`
3. Selecteaza primii 60 si ii distribuie echitabil in cele 4 departamente (round-robin)

Acest mecanism asigura ca fiecare rulare ofera o configuratie diferita a firmei.

---

## Format fisier de intrare
Full Time % Nume Angajat % ID % Salariu % ZileConcediu % AniVechime
Part Time % Nume Angajat % ID % OrePerSaptamana % TarifOrar
Contractor % Nume Angajat % ID % TarifZilnic % ZileLucrate % DataExpirare
Intern % Nume Angajat % ID % Stipendiu % DurataLuni % NumeMentor

Exemplu:
Full Time % Ion Popescu % 101 % 6000 % 21 % 3
Part Time % Maria Ionescu % 102 % 20 % 35
Contractor % Andrei Popa % 103 % 400 % 15 % 31-12-2026
Intern % Ana Dumitrescu % 104 % 1500 % 6 % Ion Popescu

---

## Departamente disponibile

| Cod | Nume |
|-----|------|
| `SD` | Software Development |
| `HR` | Human Resources |
| `LG` | Logistics |
| `DG` | Design |

---

## Tag-uri git

- `v0.1` — Tema 1: compunere, 3 clase, separare h/cpp
- `v0.2` — Tema 2: mostenire, polimorfism, exceptii, dynamic_cast
- `v0.3` — Tema 3: templates, design patterns (Factory, Singleton)
