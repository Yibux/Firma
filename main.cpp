#include <iostream>
#include <vector>

using namespace std;

class Osoba {
protected:
    string imie, nazwisko;
    int wiek;
public:
    Osoba(string imie, string nazwisko, int wiek) : imie(imie), nazwisko(nazwisko), wiek(wiek) {}

    ~Osoba() {}
    friend ostream& operator<<(ostream& os, const Osoba& pracownik) {
        os << "Imie: " << pracownik.imie << endl;
        os << "Nazwisko: " << pracownik.nazwisko << endl;
        os << "Wiek: " << pracownik.wiek << endl;

        return os;
    }
};

class Kierownik;

class Pracownik : public Osoba {
private:

protected:
    string stanowisko;
    int stawkaGodzinowa;

public:
    Pracownik(string imie, string nazwisko, int wiek, string stanowisko, int stawkaGodzinowa, Kierownik* kierownik)
            : Osoba(imie, nazwisko, wiek), stanowisko(stanowisko), stawkaGodzinowa(stawkaGodzinowa), kierownik(kierownik) {}

    Pracownik& operator=(const Pracownik& k) {
        if (this != &k) {
            Osoba::operator=(k); // Przypisanie składowych dziedziczonych z klasy Osoba
            stanowisko = k.stanowisko;
            stawkaGodzinowa = k.stawkaGodzinowa;
            kierownik = k.kierownik;
        }
        return *this;
    }

    float wyliczStawke(float liczbaGodzin) const {
        return float(stawkaGodzinowa)*liczbaGodzin;
    }


    friend ostream& operator<<(ostream& os, const Pracownik& pracownik) {
        os << "Imie: " << pracownik.imie << endl;
        os << "Nazwisko: " << pracownik.nazwisko << endl;
        os << "Wiek: " << pracownik.wiek << endl;
        os << "Stanowisko: " << pracownik.stanowisko << endl;
        os << "Stawka godzinowa: " << pracownik.stawkaGodzinowa << endl;
        os<<endl;

        return os;
    }




    Kierownik *kierownik;
};

class Kierownik : public Pracownik {
private:
    vector<Pracownik> podwladni;

public:
    Kierownik(string imie, string nazwisko, int wiek, int stawkaGodzinowa)
            : Pracownik(imie, nazwisko, wiek, "Kierownik", stawkaGodzinowa, nullptr) {}

    void dodajPodwladnego(const Pracownik& pracownik) {
        podwladni.push_back(pracownik);
    }

    float wyliczStawke(float liczbaGodzin) {
        return float(stawkaGodzinowa)*liczbaGodzin*1.25;
    }


    friend ostream& operator<<(ostream& os, const Kierownik& kierownik) {
        os << "Dane Kierownika:"<<endl;
        os << "Imie: " << kierownik.imie << endl;
        os << "Nazwisko: " << kierownik.nazwisko << endl;
        os << "Wiek: " << kierownik.wiek << endl;
        os << "Stanowisko: " << kierownik.stanowisko << endl;
        os << "Stawka godzinowa: " << kierownik.stawkaGodzinowa << endl;


        if(!kierownik.podwladni.empty())
            os << "Podwladni:"<<endl;
        for (const Pracownik &podwladny : kierownik.podwladni) {
            os << podwladny << endl;
        }
        os<<endl;
        return os;
    }
};

void ustawKierownika(Kierownik &kierownik, Pracownik &pracownik) {
    pracownik.kierownik = &kierownik;
    kierownik.dodajPodwladnego(pracownik);
}

void dodajPodwladnego(Kierownik &kierownik, Pracownik &pracownik) {
    kierownik.dodajPodwladnego(pracownik);
    pracownik.kierownik = &kierownik;
}


int main() {
    Kierownik kierownik("Jakub", "Sz", 21,25);
    Pracownik pracownik("Karolina", "Skudzinska", 21, "piekarz", 25, &kierownik);
    cout<<pracownik;

    cout<<kierownik;
    ustawKierownika(kierownik, pracownik);
    cout<<kierownik;

    cout<<pracownik.wyliczStawke(123)<<endl;
    cout<<kierownik.wyliczStawke(123)<<endl;
    return 0;
}
