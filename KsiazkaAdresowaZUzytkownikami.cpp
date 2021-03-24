#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <cstdio>
#include <stdio.h>
#include <typeinfo>
#include <algorithm>

using namespace std;

const string PlikZUzytkownikami = "Uzytkownicy.txt";
const string PlikZKontaktamiTymczasowy = "kontaktyTemporary.txt";
const string plikZAdresatami = "ksiazkaPoKonwersji.txt";

struct Uzytkownik{
    int idUzytkownika;
    string nazwa, haslo;
};

struct Adresat{
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
    int idUzytkownika;
};

int zaloguj(vector<Uzytkownik>& uzytkownicy){
    string nazwa, haslo;
    cout << "Podaj login: ";
    cin >> nazwa;

    for (int i = 0; i < uzytkownicy.size(); i++) {
        if (uzytkownicy[i].nazwa == nazwa){
            for (int p = 0; p < 3; p++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-p << ": ";
                cin >> haslo;
                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie" << endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo" << endl;
            Sleep(1500);
        }
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

void dopiszUzytkownika(Uzytkownik uzytkownik){
    fstream plikTekstowy;
    plikTekstowy.open(PlikZUzytkownikami, ios::out | ios::app);
    plikTekstowy << uzytkownik.idUzytkownika << "|" << uzytkownik.nazwa << "|" << uzytkownik.haslo << "|" << endl;
}

vector<Uzytkownik> wczytajPlikZUzytkownikami(){
    vector<Uzytkownik> uzytkownicy;
    string nazwa;
    string haslo;
    int idUzytkownika;
    fstream plikDoOdczytu;
    plikDoOdczytu.open(PlikZUzytkownikami, ios::in);

    if (plikDoOdczytu.good() == false) {
        cout << "baza uzytkownikow jest pusta" << endl;
        system("pause");
    } else {
        string linia;
        int numerLinii=1;

        while(getline(plikDoOdczytu, linia)) {
            string delimiter = "|";
            idUzytkownika = stoi(linia.substr(0, linia.find(delimiter)));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            nazwa = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            haslo = linia.substr(0, linia.find(delimiter));

            Uzytkownik osoba;
            osoba.idUzytkownika=idUzytkownika;
            osoba.nazwa=nazwa;
            osoba.haslo=haslo;

            uzytkownicy.push_back(osoba);
            numerLinii++;
        }

        cout << endl << "Baza uzytkownikow zaczytana poprawnie" << endl;
        system("pause");
    }
    return uzytkownicy;
}

void zarejestruj(vector<Uzytkownik>& uzytkownicy){
    int idUzytkownika;
    string nazwa;
    string haslo;
    int dlugoscWektora = uzytkownicy.size();

    if (dlugoscWektora==0){
        idUzytkownika = 1;
    } else {
        idUzytkownika=uzytkownicy[dlugoscWektora-1].idUzytkownika+1;
    }

    cin.ignore();
    cout << "Podaj login: ";
    getline(cin, nazwa);
    cout << "Podaj haslo: ";
    getline(cin, haslo);

    Uzytkownik osoba;
    osoba.idUzytkownika=idUzytkownika;
    osoba.nazwa=nazwa;
    osoba.haslo=haslo;
    uzytkownicy.push_back(osoba);

    /*ofstream f(PlikZUzytkownikami, ios::app);
    vector<string> kontaktyDoZapisu;
    string liniaKontaktu;
    liniaKontaktu = to_string(osoba.idUzytkownika)+"|"+osoba.nazwa+"|"+osoba.haslo+"|";
    kontaktyDoZapisu.push_back(liniaKontaktu);

    for(vector<string>::const_iterator i = kontaktyDoZapisu.begin(); i != kontaktyDoZapisu.end(); ++i) {
        f << *i << '\n';
    }
    */

    dopiszUzytkownika(osoba);

    cout << "Uzytkownik zarejestrowany poprawnie" << endl;
    system("pause");
}

vector<Adresat> wczytajPlik(int idZalogowanegoUzytkownika){
    vector<Adresat> adresaci;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
    int idUzytkownika;
    fstream plikDoOdczytu2;
    plikDoOdczytu2.open(plikZAdresatami, ios::in);

    if (plikDoOdczytu2.good() == false) {
        cout << "Ksiazka kontaktow nie istnieje" << endl;
        system("pause");
    } else {
        string linia;
        int numerLinii=1;

        while(getline(plikDoOdczytu2, linia)) {
            string delimiter = "|";
            idKontaktu = stoi(linia.substr(0, linia.find(delimiter)));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            idUzytkownika = stoi(linia.substr(0, linia.find(delimiter)));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            imie = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            nazwisko = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            numerTelefonu = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            email = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            adres = linia.substr(0, linia.find(delimiter));

            if (idUzytkownika==idZalogowanegoUzytkownika) {
                Adresat kontakt;
                kontakt.idKontaktu=idKontaktu;
                kontakt.idUzytkownika=idUzytkownika;
                kontakt.imie=imie;
                kontakt.nazwisko=nazwisko;
                kontakt.numerTelefonu=numerTelefonu;
                kontakt.email=email;
                kontakt.adres=adres;

                adresaci.push_back(kontakt);
                numerLinii++;
            }
        }

        cout << endl << "Ksiazka kontaktow zaczytana poprawnie" << endl;
        system("pause");
    }
    return adresaci;
}

int sprawdzOstatnieIdKontaktu(){
    int ostatnieIdKontaktu;
    int idKontaktu;
    fstream plikDoOdczytu;
    plikDoOdczytu.open(plikZAdresatami, ios::in);

    if (plikDoOdczytu.good() == false) {
        ostatnieIdKontaktu=0;
        system("pause");
        //exit(0);
    } else {
        string linia;
        int numerLinii=1;

        while(getline(plikDoOdczytu, linia)) {
            string delimiter = "|";
            idKontaktu = stoi(linia.substr(0, linia.find(delimiter)));
            numerLinii++;
            }
        ostatnieIdKontaktu=idKontaktu;
        }

    return ostatnieIdKontaktu;
}

void dodajAdresataDoPliku(Adresat adresat){
    fstream plikTekstowy;
    plikTekstowy.open(plikZAdresatami, ios::out | ios::app);
    plikTekstowy << adresat.idKontaktu << "|" << adresat.idUzytkownika << "|" <<
    adresat.imie << "|" << adresat.nazwisko << "|" << adresat.numerTelefonu << "|" <<
    adresat.email << "|" << adresat.adres << "|" << endl;
}

int dodajKontakt(vector<Adresat>& adresaci, int idZalogowanegoUzytkownika, int ostatnieIdKontaktu){
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu=ostatnieIdKontaktu+1;
    int idUzytkownika=idZalogowanegoUzytkownika;

    //dane kontaktu
    cin.ignore();
    cout << "Podaj imie: ";
    getline(cin, imie);
    cout << "Podaj nazwisko: ";
    getline(cin, nazwisko);
    cout << "Podaj numer telefonu: ";
    getline(cin, numerTelefonu);
    cout << "Podaj email: ";
    getline(cin, email);
    cout << "Podaj adres: ";
    getline(cin, adres);

    //dodaj kontakt do wektora
    Adresat kontakt;
    kontakt.idKontaktu=idKontaktu;
    kontakt.idUzytkownika=idUzytkownika;
    kontakt.imie=imie;
    kontakt.nazwisko=nazwisko;
    kontakt.numerTelefonu=numerTelefonu;
    kontakt.email=email;
    kontakt.adres=adres;
    adresaci.push_back(kontakt);
    dodajAdresataDoPliku(kontakt);

    ostatnieIdKontaktu = idKontaktu;
    return ostatnieIdKontaktu;
}

void wyswietlDanePojedynczejOsoby(Adresat adresat){
    cout << adresat.idKontaktu << "|" << adresat.imie << "|" << adresat.nazwisko << "|";
    cout << adresat.numerTelefonu << "|" << adresat.email << "|" << adresat.adres << endl;
}

void wyszukajPoImieniu(vector<Adresat>& adresaci, string imieDoWyszukania){
    for (int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].imie == imieDoWyszukania){
            wyswietlDanePojedynczejOsoby(adresaci[i]);
        }
    }
    cout << endl;
    system("pause");
}

void wyszukajPoNazwisku(vector<Adresat>& adresaci, string nazwiskoDoWyszukania){
    for (int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].nazwisko == nazwiskoDoWyszukania){
            wyswietlDanePojedynczejOsoby(adresaci[i]);
        }
    }
    cout << endl;
    system("pause");
}

void wyswietlWszystkich(const vector<Adresat>& adresaci){
    for (int i = 0; i < adresaci.size(); i++) {
        wyswietlDanePojedynczejOsoby(adresaci[i]);
    }
    cout << endl;
    system("pause");
}

void zapiszPlikZUzytkownikami(vector<Uzytkownik> &uzytkownicy){
    vector<string> uzytkownicyPoZmianie;
    string liniaKontaktu;
    for (int i=0; i<uzytkownicy.size(); i++) {
        liniaKontaktu = to_string(uzytkownicy[i].idUzytkownika)+"|"+uzytkownicy[i].nazwa+"|"+uzytkownicy[i].haslo+"|";
        uzytkownicyPoZmianie.push_back(liniaKontaktu);
    }
    ofstream f(PlikZUzytkownikami);
    for(vector<string>::const_iterator i = uzytkownicyPoZmianie.begin(); i != uzytkownicyPoZmianie.end(); ++i) {
        f << *i << '\n';
    }
}

void zmianahasla(vector<Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika){
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for (int i=0; i < uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione" << endl;
            Sleep(1500);
        }
    }

    zapiszPlikZUzytkownikami(uzytkownicy);
}

void usunKontakt(vector<Adresat>& adresaci, int idDoUsuniecia){
    char potwierdzenie;
    cout << "Czy na pewno chcesz usunac kontakt? [t/n]: ";
    cin >> potwierdzenie;
    int pozycjaKontaktu;

    if (potwierdzenie == 't'){
        for (int i=0; i<adresaci.size(); i++) {
            if (adresaci[i].idKontaktu == idDoUsuniecia) {
                pozycjaKontaktu=i;
                adresaci.erase(adresaci.begin() + pozycjaKontaktu);
            }
        }
    } else {
        cout << "Usuniecie kontaktu przerwane" << endl;
    }
    system("pause");
}

void edytujKontakt(int opcja, vector<Adresat>& adresaci){
    int pozycjaKontaktu;
    int idDoEdycji;

    switch(opcja)
    {
    case 1: {
        cout << "Podaj id kontaktu do edycji: ";
        cin >> idDoEdycji;
        string imie;

        for (int i=0; i<adresaci.size(); i++) {
            if (adresaci[i].idKontaktu == idDoEdycji) {
                pozycjaKontaktu=i;
                cout << "Podaj imie po zmianie: ";
                cin >> imie;
                adresaci[pozycjaKontaktu].imie = imie;
            }
        }
        break;
    }
    case 2: {
        cout << "Podaj id kontaktu do edycji: ";
        cin >> idDoEdycji;
        string nazwisko;

        for (int i=0; i<adresaci.size(); i++) {
            if (adresaci[i].idKontaktu == idDoEdycji) {
                pozycjaKontaktu=i;
                cout << "Podaj nazwisko po zmianie: ";
                cin >> nazwisko;
                adresaci[pozycjaKontaktu].nazwisko = nazwisko;
            }
        }
        break;
    }
    case 3: {
        cout << "Podaj id kontaktu do edycji: ";
        cin >> idDoEdycji;
        string numerTelefonu;

        for (int i=0; i<adresaci.size(); i++) {
            if (adresaci[i].idKontaktu == idDoEdycji) {
                pozycjaKontaktu=i;
                cout << "Podaj numer telefonu po zmianie: ";
                cin >> numerTelefonu;
                adresaci[pozycjaKontaktu].numerTelefonu = numerTelefonu;
            }
        }
        break;
    }
    case 4: {
        cout << "Podaj id kontaktu do edycji: ";
        cin >> idDoEdycji;
        string email;

        for (int i=0; i<adresaci.size(); i++) {
            if (adresaci[i].idKontaktu == idDoEdycji) {
                pozycjaKontaktu=i;
                cout << "Podaj email po zmianie: ";
                cin >> email;
                adresaci[pozycjaKontaktu].email = email;
            }
        }
        break;
    }
    case 5: {
        cout << "Podaj id kontaktu do edycji: ";
        cin >> idDoEdycji;
        string adres;

        for (int i=0; i<adresaci.size(); i++) {
            if (adresaci[i].idKontaktu == idDoEdycji) {
                pozycjaKontaktu=i;
                cout << "Podaj adres po zmianie: ";
                cin >> adres;
                adresaci[pozycjaKontaktu].adres = adres;
            }
        }
        break;
    }
    default:
        break;
    }
}


vector<Adresat> wczytajCalyPlik(){
    vector<Adresat> adresaciOryginalni;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
    int idUzytkownika;
    fstream plikDoOdczytu;
    plikDoOdczytu.open(plikZAdresatami, ios::in);

    string linia;
    int numerLinii=1;

    while(getline(plikDoOdczytu, linia)) {
            string delimiter = "|";
            idKontaktu = stoi(linia.substr(0, linia.find(delimiter)));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            idUzytkownika = stoi(linia.substr(0, linia.find(delimiter)));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            imie = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            nazwisko = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            numerTelefonu = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            email = linia.substr(0, linia.find(delimiter));
            linia.erase(0, linia.find(delimiter) + delimiter.length());
            adres = linia.substr(0, linia.find(delimiter));

            Adresat kontakt;
            kontakt.idKontaktu=idKontaktu;
            kontakt.idUzytkownika=idUzytkownika;
            kontakt.imie=imie;
            kontakt.nazwisko=nazwisko;
            kontakt.numerTelefonu=numerTelefonu;
            kontakt.email=email;
            kontakt.adres=adres;
            adresaciOryginalni.push_back(kontakt);
            numerLinii++;
        }

    return adresaciOryginalni;
}

vector<Adresat> wybierzKontaktyDoZapisu(vector<Adresat> &adresaciOryginalni, vector<Adresat> &adresaci,
                                        int idZalogowanegoUzytkownika){
    vector<Adresat> adresaciDoZapisu;

    for (int i=0; i<adresaci.size(); i++){
        Adresat kontaktDoZapisu;
        kontaktDoZapisu.idKontaktu=adresaci[i].idKontaktu;
        kontaktDoZapisu.idUzytkownika=adresaci[i].idUzytkownika;
        kontaktDoZapisu.imie=adresaci[i].imie;
        kontaktDoZapisu.nazwisko=adresaci[i].nazwisko;
        kontaktDoZapisu.numerTelefonu=adresaci[i].numerTelefonu;
        kontaktDoZapisu.email=adresaci[i].email;
        kontaktDoZapisu.adres=adresaci[i].adres;
        adresaciDoZapisu.push_back(kontaktDoZapisu);
    }

    for (int i=0; i<adresaciOryginalni.size(); i++){
        Adresat kontaktDoZapisu2;
        if (adresaciOryginalni[i].idUzytkownika!=idZalogowanegoUzytkownika){
            kontaktDoZapisu2.idKontaktu=adresaciOryginalni[i].idKontaktu;
            kontaktDoZapisu2.idUzytkownika=adresaciOryginalni[i].idUzytkownika;
            kontaktDoZapisu2.imie=adresaciOryginalni[i].imie;
            kontaktDoZapisu2.nazwisko=adresaciOryginalni[i].nazwisko;
            kontaktDoZapisu2.numerTelefonu=adresaciOryginalni[i].numerTelefonu;
            kontaktDoZapisu2.email=adresaciOryginalni[i].email;
            kontaktDoZapisu2.adres=adresaciOryginalni[i].adres;
            adresaciDoZapisu.push_back(kontaktDoZapisu2);
        }
    }

    return adresaciDoZapisu;
}

vector<Adresat> sortujWektor(vector<Adresat> &adresaciDoZapisuTmp){
    sort(adresaciDoZapisuTmp.begin(), adresaciDoZapisuTmp.end(), [](Adresat a, Adresat b) {
		return a.idKontaktu < b.idKontaktu;
	});
    return adresaciDoZapisuTmp;
}

void zapiszPlik(vector<Adresat> &adresaci, int ostatnieIdKontaktu, int idZalogowanegoUzytkownika){
    vector<Adresat> adresaciOryginalni = wczytajCalyPlik();
    vector<Adresat> adresaciDoZapisuTmp = wybierzKontaktyDoZapisu(adresaciOryginalni, adresaci, idZalogowanegoUzytkownika);
    vector<Adresat> adresaciDoZapisu = sortujWektor(adresaciDoZapisuTmp);

    vector<string> noweKontakty;
    string nowaLinia;
    for (int i=0; i<adresaciDoZapisu.size(); i++) {
        nowaLinia = to_string(adresaciDoZapisu[i].idKontaktu)+"|"+to_string(adresaciDoZapisu[i].idUzytkownika)+"|"+adresaciDoZapisu[i].imie+"|"+adresaciDoZapisu[i].nazwisko+"|"+adresaciDoZapisu[i].numerTelefonu+"|"+adresaciDoZapisu[i].email+"|"+adresaciDoZapisu[i].adres+"|";
        noweKontakty.push_back(nowaLinia);
    }

    fstream tworzonyPlik;
    tworzonyPlik.open(plikZAdresatami, ios::in);
    ofstream f(plikZAdresatami);
    for(vector<string>::const_iterator i = noweKontakty.begin(); i != noweKontakty.end(); ++i) {
        f << *i << '\n';
    }
}

int main() {

    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;
    uzytkownicy = wczytajPlikZUzytkownikami();
    int idZalogowanegoUzytkownika;
    int ostatnieIdKontaktu;
    int idDoUsuniecia;

    char wyborInstrukcji;
    char wyborInstrukcjiPoLogowaniu;

    while (1) {
        system ("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "9. Zamknij program" << endl;

        cout << endl << "Twoj wybor: ";
        cin >> wyborInstrukcji;
        cout << endl;

        if (wyborInstrukcji == '1') {
            idZalogowanegoUzytkownika = zaloguj(uzytkownicy);
            if (idZalogowanegoUzytkownika==0){
                cout << "Logowanie nie powiodlo sie" << endl;
            } else {
                adresaci = wczytajPlik(idZalogowanegoUzytkownika);
                ostatnieIdKontaktu=sprawdzOstatnieIdKontaktu();

                while (idZalogowanegoUzytkownika!=0) {
                    cout << endl;
                    cout << "1. Dodaj adresata" << endl;
                    cout << "2. Wyszukaj po imieniu" << endl;
                    cout << "3. Wyszukaj po nazwisku" << endl;
                    cout << "4. Wyswietl wszystkich adresatow" << endl;
                    cout << "5. Usun adresata" << endl;
                    cout << "6. Edytuj adresata" << endl;
                    cout << "7. Zmien haslo" << endl;
                    cout << "8. Wyloguj sie" << endl;
                    cout << endl << "Twoj wybor: ";
                    cin >> wyborInstrukcjiPoLogowaniu;
                    cout << endl;

                    if (wyborInstrukcjiPoLogowaniu == '1') {
                        ostatnieIdKontaktu = dodajKontakt(adresaci, idZalogowanegoUzytkownika, ostatnieIdKontaktu);
                    } else if (wyborInstrukcjiPoLogowaniu == '2') {
                        string imieDoWyszukania;
                        cout << "Podaj imie kontaktu: ";
                        cin >> imieDoWyszukania;
                        cout << endl;
                        wyszukajPoImieniu(adresaci, imieDoWyszukania);
                    } else if (wyborInstrukcjiPoLogowaniu == '3') {
                        string nazwiskoDoWyszukania;
                        cout << "Podaj nazwisko kontaktu: ";
                        cin >> nazwiskoDoWyszukania;
                        cout << endl;
                        wyszukajPoNazwisku(adresaci, nazwiskoDoWyszukania);
                    } else if (wyborInstrukcjiPoLogowaniu == '4') {
                        wyswietlWszystkich(adresaci);
                    } else if (wyborInstrukcjiPoLogowaniu == '5') {
                        cout << "Podaj id kontaktu do usuniecia: ";
                        cin >> idDoUsuniecia;
                        usunKontakt(adresaci, idDoUsuniecia);
                        if (ostatnieIdKontaktu==idDoUsuniecia){
                            ostatnieIdKontaktu = ostatnieIdKontaktu-1;
                        }
                        zapiszPlik(adresaci, ostatnieIdKontaktu, idZalogowanegoUzytkownika);
                        ostatnieIdKontaktu=sprawdzOstatnieIdKontaktu();
                    } else if (wyborInstrukcjiPoLogowaniu == '6') {
                        int opcja;
                        cout << "Wybierz opcje: " << endl;
                        cout << "1. Edytuj imie" << endl;
                        cout << "2. Edytuj nazwisko" << endl;
                        cout << "3. Edytuj numer telefonu" << endl;
                        cout << "4. Edytuj email" << endl;
                        cout << "5. Edytuj adres" << endl;
                        cout << "6. Wroc do menu" << endl;
                        cin >> opcja;
                        edytujKontakt(opcja, adresaci);
                        zapiszPlik(adresaci, ostatnieIdKontaktu, idZalogowanegoUzytkownika);
                        ostatnieIdKontaktu=sprawdzOstatnieIdKontaktu();
                    } else if (wyborInstrukcjiPoLogowaniu == '7') {
                        zmianahasla(uzytkownicy, idZalogowanegoUzytkownika);
                    } else if (wyborInstrukcjiPoLogowaniu == '8') {
                        idZalogowanegoUzytkownika=0;
                    }
                }
                }

        } else if (wyborInstrukcji == '2') {
            zarejestruj(uzytkownicy);
        } else if (wyborInstrukcji == '9') {
            exit(0);
        }
    }

    return 0;
}

