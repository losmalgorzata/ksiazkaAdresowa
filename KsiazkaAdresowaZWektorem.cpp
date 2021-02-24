#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iterator>

using namespace std;

struct Adresat {
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
};

vector<Adresat> wczytajPlik(string nazwaPlikuDoOdczytu) {
    vector<Adresat> adresaci;
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int idKontaktu;
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
            kontakt.imie=imie;
            kontakt.nazwisko=nazwisko;
            kontakt.numerTelefonu=numerTelefonu;
            kontakt.email=email;
            kontakt.adres=adres;

            adresaci.push_back(kontakt);
            numerLinii++;
        }

        cout << endl << "Ksiazka kontaktow zaczytana poprawnie" << endl;
        system("pause");
    }
    return adresaci;
}

void dodajKontakt(vector<Adresat>& adresaci, string nazwaPlikuDoZapisu)
{
    string imie;
    string nazwisko;
    string numerTelefonu;
    string email;
    string adres;
    int dlugoscWektora = adresaci.size();
    int idKontaktu;

    if (dlugoscWektora==0){
        idKontaktu = 0;
    } else {
        idKontaktu=adresaci[dlugoscWektora-1].idKontaktu+1;
    }

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
    kontakt.imie=imie;
    kontakt.nazwisko=nazwisko;
    kontakt.numerTelefonu=numerTelefonu;
    kontakt.email=email;
    kontakt.adres=adres;

    adresaci.push_back(kontakt);

    //dodaj kontakt do pliku
    ofstream f(nazwaPlikuDoZapisu, ios::app);
    vector<string> kontaktyDoZapisu;
    string liniaKontaktu;
    liniaKontaktu = to_string(kontakt.idKontaktu)+"|"+kontakt.imie+"|"+kontakt.nazwisko+"|"+kontakt.numerTelefonu+"|"+kontakt.email+"|"+kontakt.adres+"|";
    kontaktyDoZapisu.push_back(liniaKontaktu);

    for(vector<string>::const_iterator i = kontaktyDoZapisu.begin(); i != kontaktyDoZapisu.end(); ++i) {
        f << *i << '\n';
    }

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

void zapiszPlik(string nazwaPlikuDoZapisu, vector<Adresat> &adresaci)
{
    vector<string> kontaktyPoKonwersji;
    string liniaKontaktu;
    for (int i=0; i<adresaci.size(); i++) {
        liniaKontaktu = to_string(adresaci[i].idKontaktu)+"|"+adresaci[i].imie+"|"+adresaci[i].nazwisko+"|"+adresaci[i].numerTelefonu+"|"+adresaci[i].email+"|"+adresaci[i].adres+"|";
        kontaktyPoKonwersji.push_back(liniaKontaktu);
    }
    ofstream f(nazwaPlikuDoZapisu);
    for(vector<string>::const_iterator i = kontaktyPoKonwersji.begin(); i != kontaktyPoKonwersji.end(); ++i) {
        f << *i << '\n';
    }
}

void usunKontakt(vector<Adresat>& adresaci, string nazwaPliku, int idDoUsuniecia)
{
    char potwierdzenie;
    cout << "Czy na pewno chcesz usunac kontakt? [t/n]: ";
    cin >> potwierdzenie;
    int pozycjaKontaktu;

    if (potwierdzenie == 't'){
        for (int i=0; i<adresaci.size(); i++) {
            if (adresaci[i].idKontaktu == idDoUsuniecia) {
                pozycjaKontaktu=i;
                adresaci.erase(adresaci.begin()+pozycjaKontaktu);
                zapiszPlik(nazwaPliku, adresaci);
                cout << endl;
            }
        }
    } else {
        cout << "Usuniecie kontaktu przerwane" << endl;
    }
    system("pause");
}

void edytujKontakt(int opcja, vector<Adresat>& adresaci, string nazwaPliku)
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
    zapiszPlik(nazwaPliku, adresaci);
}

int main() {

    vector<Adresat> adresaci;
    string nazwaPlikuDoOdczytu = "ksiazkaPoKonwersji.txt";

    adresaci = wczytajPlik(nazwaPlikuDoOdczytu);
    char wyborInstrukcji;

    while (1) {
        system ("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;

        cout << endl << "Twoj wybor: ";
        cin >> wyborInstrukcji;
        cout << endl;

        if (wyborInstrukcji == '1') {
            dodajKontakt(adresaci, nazwaPlikuDoOdczytu);
        } else if (wyborInstrukcji == '2') {
            string imieDoWyszukania;
            cout << "Podaj imie kontaktu: ";
            cin >> imieDoWyszukania;
            cout << endl;
            wyszukajPoImieniu(adresaci, imieDoWyszukania);
        } else if (wyborInstrukcji == '3') {
            string nazwiskoDoWyszukania;
            cout << "Podaj nazwisko kontaktu: ";
            cin >> nazwiskoDoWyszukania;
            cout << endl;
            wyszukajPoNazwisku(adresaci, nazwiskoDoWyszukania);
        } else if (wyborInstrukcji == '4') {
            wyswietlWszystkich(adresaci);
        } else if (wyborInstrukcji == '5') {
            int idDoUsuniecia;
            cout << "Podaj id kontaktu do usuniecia: ";
            cin >> idDoUsuniecia;
            usunKontakt(adresaci, nazwaPlikuDoOdczytu, idDoUsuniecia);
        } else if (wyborInstrukcji == '6') {
            int opcja;
            cout << "Wybierz opcje: " << endl;
            cout << "1. Edytuj imie" << endl;
            cout << "2. Edytuj nazwisko" << endl;
            cout << "3. Edytuj numer telefonu" << endl;
            cout << "4. Edytuj email" << endl;
            cout << "5. Edytuj adres" << endl;
            cout << "6. Wroc do menu" << endl;
            cin >> opcja;

            edytujKontakt(opcja, adresaci, nazwaPlikuDoOdczytu);
        } else if (wyborInstrukcji = '9') {
            exit(0);
        }
    }

    return 0;
}
