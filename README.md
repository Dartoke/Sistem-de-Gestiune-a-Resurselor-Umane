# Sistem de Gestiune a Resurselor Umane

Un sistem interactiv de management HR implementat în C++, care permite unui HR-ist să gestioneze angajații, departamentele și proiectele unei firme.

---

## Structura proiectului
proiect/
├── angajati.h / angajati.cpp        # Clasa abstracta de baza
├── angajatFullTime.h / .cpp         # Angajat cu norma intreaga
├── angajatPartTime.h / .cpp         # Angajat cu timp partial
├── contractor.h / .cpp              # Angajat tip contractor
├── intern.h / .cpp                  # Stagiar (a 4-a derivata)
├── departament.h / .cpp             # Container de angajati
├── proiect.h / .cpp                 # Clasa proiect
├── exceptii.h                       # Ierarhie de exceptii
├── utile.h                          # Functii utilitare
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
// Baza abstracta
class Angajat {
    virtual double calculeazaSalariu() const = 0;
    virtual Angajat* clone() const = 0;
    // ...
};

// Derivate
class AngajatFullTime : public Angajat { /* salariu fix + bonus vechime */ };
class AngajatPartTime : public Angajat { /* ore/sapt * tarif orar * 4 */ };
class Contractor      : public Angajat { /* tarif zilnic * zile lucrate */ };
class Intern          : public Angajat { /* stipendiu fix lunar */ };
```

### 2. Polimorfism
`Departament` tine un `vector<Angajat*>` si apeleaza functiile virtual prin pointer de baza — fara sa stie tipul concret al fiecarui angajat:

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
// In baza — public, non-virtual
friend std::ostream& operator<<(std::ostream& os, const Angajat& a) {
    a.print(os);  // apel polimorfic intern
    return os;
}

// In fiecare derivata — privat, virtual
void AngajatFullTime::print(std::ostream& os) const {
    os << nume << " | Salariu: " << salariu
       << " | Zile concediu: " << zileConcediu
       << " | Ani vechime: " << aniVechime;
}
```

### 4. Copiere corecta (Rule of Three + clone)
`Departament` implementeaza constructor de copiere, `operator=` si destructor pentru a gestiona corect memoria dinamica. Copierea angajatilor se face prin `clone()` pentru a evita shallow copy:

```cpp
Departament::Departament(const Departament& altul) {
    for (auto* a : altul.echipa)
        echipa.push_back(a->clone());  // deep copy polimorfic
}

Departament::~Departament() {
    for (auto* a : echipa)
        delete a;  // elibereaza fiecare angajat
}
```

### 5. Ierarhie de exceptii
Toate erorile din sistem deriva din `ExceptieHR`, care la randul ei deriva din `std::exception`:
std::exception
└── ExceptieHR
├── ExceptieSalariuInvalid   // salariu < minim legal
├── ExceptieAngajatNegasit   // ID inexistent
└── ExceptieProiectNeviabil  // buget insuficient

Exemplu de utilizare:
```cpp
try {
    departament.stergeAngajat(id);
} catch (const ExceptieAngajatNegasit& e) {
    std::cout << e.what() << "\n";
} catch (const ExceptieHR& e) {
    std::cout << "Eroare HR: " << e.what() << "\n";
}
```

### 6. Membrii statici
Fiecare clasa derivata are un minim legal propriu ca membru `static const`:

```cpp
const double AngajatFullTime::SALARIU_MINIM = 4300.0;
const double AngajatPartTime::TARIF_ORAR_MINIM = 25.0;
const double Contractor::TARIF_ZILNIC_MINIM = 200.0;
```

`Angajat` tine un contor global de angajati activi, incrementat/decrementat automat in constructori/destructor:

```cpp
std::cout << "Total angajati: " << Angajat::getTotalNumarAngajati();
```

### 7. dynamic_cast
Promovarea unui angajat foloseste `dynamic_cast` pentru a verifica tipul la runtime:

```cpp
void Departament::promoveazaContractor(int id) {
    for (auto i = echipa.begin(); i != echipa.end(); i++) {
        if ((*i)->getId() == id) {
            Contractor* c = dynamic_cast<Contractor*>(*i);
            if (c) {
                double salariuLunar = c->getSalariuZilnic() * c->getZileLucrate();
                delete *i;
                *i = new AngajatFullTime(c->getNume(), id, salariuLunar, 20, 0);
            } else {
                throw ExceptieAngajatNegasit("Angajatul nu este contractor");
            }
        }
    }
}
```

---

## Functionalitati

| Optiune | Descriere |
|---------|-----------|
| `1` | Angajeaza o persoana (Full Time / Part Time / Contractor / Intern) |
| `2` | Concediaza un angajat dupa ID |
| `3` | Baza de date — afiseaza toti angajatii sau un departament |
| `4` | Mareste salariul unui angajat cu un procent |
| `5` | Scade salariul unui angajat cu un procent |
| `6` | Verifica viabilitatea financiara a unui proiect |
| `7` | Promoveaza un Contractor sau PartTime la Full Time |
| `0` | Iesire din program |

---

## Format fisier de intrare

La pornirea programului se cere un fisier cu angajati predefiniti. Formatul fiecarei linii:
Full Time % Nume Angajat % ID % Salariu % ZileConcediu % AniVechime
Part Time % Nume Angajat % ID % OrePerSaptamana % TarifOrar
Contractor % Nume Angajat % ID % TarifZilnic % ZileLucrate % DataExpirare
Intern % Nume Angajat % ID % Stipendiu % DurataLuni % NumeMentor

Exemplu (`angajati.txt`):
Full Time % Ion Popescu % 1 % 6000 % 21 % 3
Part Time % Maria Ionescu % 2 % 20 % 35
Contractor % Andrei Popa % 3 % 400 % 15 % 31-12-2025
Intern % Ana Dumitrescu % 4 % 1500 % 6 % Ion Popescu

---

## Departamente disponibile

| Cod | Nume |
|-----|------|
| `SD` | Software Development |
| `HR` | Human Resources |
| `LG` | Logistics |
| `DG` | Design |

---

## Compilare si rulare

```bash
# Compilare
g++ -std=c++17 SistemHR.cpp angajati.cpp angajatFullTime.cpp angajatPartTime.cpp contractor.cpp intern.cpp departament.cpp proiect.cpp -I . -o SistemHR.exe

# Rulare
./SistemHR.exe
```
