#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <cstdio>
#include <stdio.h>

using namespace std;

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};

struct Adresat {
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
    int idUzytkownika;
};

vector<Uzytkownik> wczytajPlikZUzytkownikami(string PlikZUzytkownikami) {
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

int zaloguj(vector<Uzytkownik>& uzytkownicy)
{
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

void zarejestruj(vector<Uzytkownik>& uzytkownicy, string PlikZUzytkownikami)
{
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

    ofstream f(PlikZUzytkownikami, ios::app);
    vector<string> kontaktyDoZapisu;
    string liniaKontaktu;
    liniaKontaktu = to_string(osoba.idUzytkownika)+"|"+osoba.nazwa+"|"+osoba.haslo+"|";
    kontaktyDoZapisu.push_back(liniaKontaktu);

    for(vector<string>::const_iterator i = kontaktyDoZapisu.begin(); i != kontaktyDoZapisu.end(); ++i) {
        f << *i << '\n';
    }
    cout << "Uzytkownik zarejestrowany poprawnie" << endl;
    system("pause");
}

vector<Adresat> wczytajPlik(string nazwaPlikuDoOdczytu, int idZalogowanegoUzytkownika) {
    vector<Adresat> adresaci;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
    int idUzytkownika;
    fstream plikDoOdczytu;
    plikDoOdczytu.open(nazwaPlikuDoOdczytu, ios::in);

    if (plikDoOdczytu.good() == false) {
        cout << "Ksiazka kontaktow nie istnieje" << endl;
        system("pause");
        //exit(0);
    } else {
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

int sprawdzOstatnieIdKontaktu(string nazwaPlikuDoOdczytu) {
    int ostatnieIdKontaktu;
    int idKontaktu;
    fstream plikDoOdczytu;
    plikDoOdczytu.open(nazwaPlikuDoOdczytu, ios::in);

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

void dodajKontakt(vector<Adresat>& adresaci, int idZalogowanegoUzytkownika, int ostatnieIdKontaktu)
{
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
}

void wyszukajPoImieniu(vector<Adresat>& adresaci, string imieDoWyszukania)
{
    for (int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].imie == imieDoWyszukania){
            cout << adresaci[i].idKontaktu << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|";
            cout << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << endl;
        }
    }
    cout << endl;
    system("pause");
}

void wyszukajPoNazwisku(vector<Adresat>& adresaci, string nazwiskoDoWyszukania)
{
    for (int i = 0; i < adresaci.size(); i++) {
        if (adresaci[i].nazwisko == nazwiskoDoWyszukania){
            cout << adresaci[i].idKontaktu << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|";
            cout << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << endl;
        }
    }
    cout << endl;
    system("pause");
}

void wyswietlWszystkich(const vector<Adresat>& adresaci)
{
    for (int i = 0; i < adresaci.size(); i++) {
        cout << adresaci[i].idKontaktu << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|";
        cout << adresaci[i].numerTelefonu << "|" << adresaci[i].email << "|" << adresaci[i].adres << endl;
    }
    cout << endl;
    system("pause");
}

void zapiszPlikZUzytkownikami(string nazwaPlikuDoZapisu, vector<Uzytkownik> &uzytkownicy)
{
    vector<string> uzytkownicyPoZmianie;
    string liniaKontaktu;
    for (int i=0; i<uzytkownicy.size(); i++) {
        liniaKontaktu = to_string(uzytkownicy[i].idUzytkownika)+"|"+uzytkownicy[i].nazwa+"|"+uzytkownicy[i].haslo+"|";
        uzytkownicyPoZmianie.push_back(liniaKontaktu);
    }
    ofstream f(nazwaPlikuDoZapisu);
    for(vector<string>::const_iterator i = uzytkownicyPoZmianie.begin(); i != uzytkownicyPoZmianie.end(); ++i) {
        f << *i << '\n';
    }
}

void zmianahasla(vector<Uzytkownik>& uzytkownicy, int idZalogowanegoUzytkownika, string nazwaPlikuDoZapisu)
{
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

    zapiszPlikZUzytkownikami(nazwaPlikuDoZapisu, uzytkownicy);
}

void zapiszPlik(string nazwaPlikuDoZapisu, string plikDoStworzenia, vector<Adresat> &adresaci, int ostatnieIdKontaktu,
                int idZalogowanegoUzytkownika)
{
    //open the original file, if exists
    vector<Adresat> adresaciOryginalni;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
    int idUzytkownika;
    fstream plikDoOdczytu;
    plikDoOdczytu.open(nazwaPlikuDoZapisu, ios::in);

    if (plikDoOdczytu.good() == false) {
            cout << "if poczatek" << endl;
        vector<string> kontaktyDoZapisu;
        string liniaKontaktu;
        for (int i=0; i<adresaci.size(); i++) {
            liniaKontaktu = to_string(adresaci[i].idKontaktu)+"|"+to_string(adresaci[i].idUzytkownika)+"|"+adresaci[i].imie+"|"+adresaci[i].nazwisko+"|"+adresaci[i].numerTelefonu+"|"+adresaci[i].email+"|"+adresaci[i].adres+"|";
            kontaktyDoZapisu.push_back(liniaKontaktu);
        }
        cout << "po for1" << endl;
        ofstream f(nazwaPlikuDoZapisu);
        for(vector<string>::const_iterator i = kontaktyDoZapisu.begin(); i != kontaktyDoZapisu.end(); ++i) {
            f << *i << '\n';
        }
        cout << "po zapisie" << endl;
    } else {
        cout << "else poczatek" << endl;
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

        cout << "else po while" << endl;

        vector<string> kontaktyPoKonwersji;
        string liniaKontaktu;
        for (int i=0; i<adresaciOryginalni.size(); i++) {
            liniaKontaktu = to_string(adresaciOryginalni[i].idKontaktu)+"|"+to_string(adresaciOryginalni[i].idUzytkownika)+"|"+adresaciOryginalni[i].imie+"|"+adresaciOryginalni[i].nazwisko+"|"+adresaciOryginalni[i].numerTelefonu+"|"+adresaciOryginalni[i].email+"|"+adresaciOryginalni[i].adres+"|";
            kontaktyPoKonwersji.push_back(liniaKontaktu);
        }

        cout << "else po for while" << endl;


        //put there modified contacts
        vector<Adresat> adresaciDoZapisu;

        for (int i=0; i<adresaciOryginalni.size(); i++){
            Adresat kontaktDoZapisu;
            if (adresaci[i].idUzytkownika==idZalogowanegoUzytkownika){
                kontaktDoZapisu.idKontaktu=adresaci[i].idKontaktu;
                kontaktDoZapisu.idUzytkownika=adresaci[i].idUzytkownika;
                kontaktDoZapisu.imie=adresaci[i].imie;
                kontaktDoZapisu.nazwisko=adresaci[i].nazwisko;
                kontaktDoZapisu.numerTelefonu=adresaci[i].numerTelefonu;
                kontaktDoZapisu.email=adresaci[i].email;
                kontaktDoZapisu.adres=adresaci[i].adres;
            } else {
                kontaktDoZapisu.idKontaktu=adresaciOryginalni[i].idKontaktu;
                kontaktDoZapisu.idUzytkownika=adresaciOryginalni[i].idUzytkownika;
                kontaktDoZapisu.imie=adresaciOryginalni[i].imie;
                kontaktDoZapisu.nazwisko=adresaciOryginalni[i].nazwisko;
                kontaktDoZapisu.numerTelefonu=adresaciOryginalni[i].numerTelefonu;
                kontaktDoZapisu.email=adresaciOryginalni[i].email;
                kontaktDoZapisu.adres=adresaciOryginalni[i].adres;
            }
            adresaciDoZapisu.push_back(kontaktDoZapisu);
        }

        cout << "else po for2  while" << endl;

        vector<string> noweKontakty;
        string nowaLinia;
        for (int i=0; i<adresaciDoZapisu.size(); i++) {
            nowaLinia = to_string(adresaciDoZapisu[i].idKontaktu)+"|"+to_string(adresaciDoZapisu[i].idUzytkownika)+"|"+adresaciDoZapisu[i].imie+"|"+adresaciDoZapisu[i].nazwisko+"|"+adresaciDoZapisu[i].numerTelefonu+"|"+adresaciDoZapisu[i].email+"|"+adresaciDoZapisu[i].adres+"|";
            noweKontakty.push_back(nowaLinia);
            cout << nowaLinia <<endl;
        }

        cout << "else po for3 while" << endl;

        fstream tworzonyPlik;
        tworzonyPlik.open(plikDoStworzenia, ios::in);
        ofstream f(plikDoStworzenia);
        for(vector<string>::const_iterator i = noweKontakty.begin(); i != noweKontakty.end(); ++i) {
            f << *i << '\n';
        }
        cout << "przed funckja rename" << endl;
        //remove old file
        plikDoOdczytu.close();
        remove(nazwaPlikuDoZapisu.c_str());
        cout << "przed funckja rename2" << endl;
        //rename file
        Sleep(10000);
        rename(plikDoStworzenia.c_str(), nazwaPlikuDoZapisu.c_str());
        cout << "po funckja rename" << endl;
        //remove temporary file
        remove(plikDoStworzenia.c_str());
        cout << "ostatnia" << endl;
        }
}

void usunKontakt(vector<Adresat>& adresaci, int idDoUsuniecia)
{
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

void edytujKontakt(int opcja, vector<Adresat>& adresaci)
{
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

int main() {

    vector<Uzytkownik> uzytkownicy;
    string PlikZUzytkownikami = "Uzytkownicy.txt";
    string PlikZKontaktamiTymczasowy = "kontaktyTemporary.txt";
    uzytkownicy = wczytajPlikZUzytkownikami(PlikZUzytkownikami);
    int idZalogowanegoUzytkownika;

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
                vector<Adresat> adresaci;
                string nazwaPlikuDoOdczytu = "ksiazkaPoKonwersji.txt";
                adresaci = wczytajPlik(nazwaPlikuDoOdczytu, idZalogowanegoUzytkownika);
                int ostatnieIdKontaktu;
                ostatnieIdKontaktu=sprawdzOstatnieIdKontaktu(nazwaPlikuDoOdczytu);

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
                        dodajKontakt(adresaci, idZalogowanegoUzytkownika, ostatnieIdKontaktu);
                        zapiszPlik(nazwaPlikuDoOdczytu, PlikZKontaktamiTymczasowy, adresaci, ostatnieIdKontaktu, idZalogowanegoUzytkownika);
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
                        int idDoUsuniecia;
                        cout << "Podaj id kontaktu do usuniecia: ";
                        cin >> idDoUsuniecia;
                        usunKontakt(adresaci, idDoUsuniecia);
                        zapiszPlik(nazwaPlikuDoOdczytu, PlikZKontaktamiTymczasowy, adresaci, ostatnieIdKontaktu, idZalogowanegoUzytkownika);;
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
                        zapiszPlik(nazwaPlikuDoOdczytu, PlikZKontaktamiTymczasowy, adresaci, ostatnieIdKontaktu, idZalogowanegoUzytkownika);;
                    } else if (wyborInstrukcjiPoLogowaniu == '7') {
                        zmianahasla(uzytkownicy, idZalogowanegoUzytkownika, PlikZUzytkownikami);
                    } else if (wyborInstrukcjiPoLogowaniu == '8') {
                        idZalogowanegoUzytkownika=0;
                    }
                }
            }


        } else if (wyborInstrukcji == '2') {
            zarejestruj(uzytkownicy, PlikZUzytkownikami);
        } else if (wyborInstrukcji == '9') {
            exit(0);
        }
    }

    return 0;
}
