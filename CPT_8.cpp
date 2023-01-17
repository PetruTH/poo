#include <bits/stdc++.h>

//Cristea Petru-Theodor

using namespace std;

template <typename T>
istream& operator>>(istream& is, vector<T> &v){
    int n;
    T temp;
    cout << "Numarul de elemente = ";
    is >> n;
    for(int i = 0; i < n; i++){
        cout << "Elementul " << i << ":";
        is >> temp;
        v.push_back(temp);
    }

    return is;
}

istream& operator>>(istream& is, vector<string> &v){
    int n;
    string temp;
    cout << "Numarul de elemente = ";
    is >> n;
    is.get();
    for(int i = 0; i < n; i++){
        cout << "Elementul " << i << ":";
        getline(is, temp);
        v.push_back(temp);
    }

    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v){
    os << "Numarul de elemente = " << v.size() << '\n';
    for(int i = 0; i < v.size(); i++){
        os << "Elementul " << i << ":" << v[i] << '\n';
    }

    return os;
}

class IOBase{
public:
    virtual istream &read(istream &is){
        return is;
    }

    virtual ostream &write(ostream &os) const{
        return os;
    }

    friend ostream &operator<<(ostream &os, const IOBase &base) {
        return base.write(os);
    }

    friend istream &operator>>(istream &is, IOBase &base) {
        return base.read(is);
    }
};

class Produs : public IOBase{
    static int currentID;

protected:
    int pret, cantitate, ID;

public:
    Produs() { }

    Produs(int pret, int cantitate, int id) : pret(pret), cantitate(cantitate), ID(id) { }

    virtual ~Produs() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Pret:"; is >> pret;
        cout << "Cantitate:"; is >> cantitate;
        ID = currentID; currentID++;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        cout << "ID:" << ID << '\n';
        cout << "Pret:" << pret << '\n';
        cout << "Cantitate:" << cantitate << '\n';

        return os;
    }

    int getPret() const {
        return pret;
    }

    int getCantitate() const {
        return cantitate;
    }

    void readString(istream &, string &);
};

int Produs::currentID = 1;

void Produs::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0) getline(is, s);
}

class Carte : public Produs {
protected:
    string titlu;
    vector<string> autori;
    string editura;

public:
    Carte() { }

    Carte(int pret, int cantitate, int id, const string &titlu, const vector<string> &autori, const string &editura)
            : Produs(pret, cantitate, id), titlu(titlu), autori(autori), editura(editura) { }

    virtual ~Carte() {

    }

    istream &read(istream &is) override {
        Produs::read(is);
        cout << "Titlu:"; readString(is, titlu);
        cout << "Lista de autori:\n"; is >> autori;
        cout << "Editura:"; readString(is, editura);

        return is;
    }

    ostream &write(ostream &os) const override {
        Produs::write(os);
        os << "Titlu:" << titlu << '\n';
        os << "Lista de autori:\n" << autori << '\n';
        os << "Editura:" << editura << '\n';

        return os;
    }

    const string &getTitlu() const {
        return titlu;
    }
};

class DVD : public Produs {
protected:
    int minute;

public:
    DVD() {}

    DVD(int pret, int cantitate, int id, int minute) : Produs(pret, cantitate, id), minute(minute) {}

    virtual ~DVD() {

    }

    istream &read(istream &is) override {
        Produs::read(is);
        cout << "Numarul de minute:"; is >> minute;

        return is;
    }

    ostream &write(ostream &os) const override {
        Produs::write(os);
        os << "Numarul de minute:" << minute << '\n';

        return os;
    }
};

class DVDMuzica : public DVD{
    string numeAlbum;
    vector<string> interpreti;

public:
    DVDMuzica() {}

    DVDMuzica(int pret, int cantitate, int id, int minute, const string &numeAlbum, const vector<string> &interpreti)
            : DVD(pret, cantitate, id, minute), numeAlbum(numeAlbum), interpreti(interpreti) { }

    virtual ~DVDMuzica() {

    }

    istream &read(istream &is) override {
        DVD::read(is);
        cout << "Nume album:"; readString(is, numeAlbum);
        cout << "Lista de interpreti:\n"; is >> interpreti;

        return is;
    }

    ostream &write(ostream &os) const override {
        DVD::write(os);
        os << "Nume album:" << numeAlbum << '\n';
        os << "Lista de interpreti:\n" << interpreti << '\n';

        return os;
    }
};

class DVDFilm : public DVD {
    string numeFilm, genul;

public:
    DVDFilm() {}

    DVDFilm(int pret, int cantitate, int id, int minute, const string &numeFilm, const string &genul) : DVD(pret,
                                                                                                            cantitate,
                                                                                                            id, minute),
                                                                                                        numeFilm(
                                                                                                                numeFilm),
                                                                                                        genul(genul) {}

    virtual ~DVDFilm() {

    }

    istream &read(istream &is) override {
        DVD::read(is);
        cout << "Nume film:"; readString(is, numeFilm);
        cout << "Genul:"; readString(is, genul);

        return is;
    }

    ostream &write(ostream &os) const override {
        DVD::write(os);
        os << "Nume film:" << numeFilm << '\n';
        os << "Genul:" << genul << '\n';

        return os;
    }
};

class ObiectColectie : public Produs {
protected:
    string denumire;

public:
    ObiectColectie() {}

    ObiectColectie(int pret, int cantitate, int id, const string &denumire) : Produs(pret, cantitate, id), denumire(denumire) {}

    virtual ~ObiectColectie() {

    }

    istream &read(istream &is) override {
        Produs::read(is);
        cout << "Denumire:"; readString(is, denumire);

        return is;
    }

    ostream &write(ostream &os) const override {
        Produs::write(os);
        os << "Denumire:" << denumire << '\n';

        return os;
    }
};

class ObiectColectieFigurina : public ObiectColectie {
    string categorie, brand, material;

public:
    ObiectColectieFigurina() { }

    ObiectColectieFigurina(int pret, int cantitate, int id, const string &denumire, const string &categorie,
                           const string &brand, const string &material) : ObiectColectie(pret, cantitate, id, denumire),
                                                                          categorie(categorie), brand(brand),
                                                                          material(material) {}

    virtual ~ObiectColectieFigurina() {

    }

    istream &read(istream &is) override {
        ObiectColectie::read(is);
        cout << "Categorie:"; readString(is, categorie);
        cout << "Brand:"; readString(is, brand);
        cout << "Material:"; readString(is, material);

        return is;
    }

    ostream &write(ostream &os) const override {
        ObiectColectie::write(os);
        os << "Categorie:" << categorie << '\n';
        os << "Brand:" << brand << '\n';
        os << "Material:" << material << '\n';

        return os;
    }
};

class ObiectColectiePoster : public ObiectColectie {
    string format;

public:
    ObiectColectiePoster() {}

    ObiectColectiePoster(int pret, int cantitate, int id, const string &denumire, const string &format)
            : ObiectColectie(pret, cantitate, id, denumire), format(format) {}

    virtual ~ObiectColectiePoster() {

    }

    istream &read(istream &is) override {
        ObiectColectie::read(is);
        cout << "Format:"; is >> format;

        return is;
    }

    ostream &write(ostream &os) const override {
        ObiectColectie::write(os);
        cout << "Format:" << format << '\n';

        return os;
    }
};

class Meniu {
    vector<shared_ptr<Produs> > listaProduse;

public:
    Meniu() { }

    void readString(istream &, string &);

    void startMeniu();

    int alegeOptiune();

    void citesteListaProduse();

    void adaugaElement();

    void afisareListaProduse() const;

    void editareProdus();

    void sorteazaLista();

    void cautaCarte();

    void cautaCantitateaMaxima();
};

void Meniu::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0) getline(is, s);
}

void Meniu::startMeniu() {
    int optiune = -1;
    while(optiune != 0)
        optiune = alegeOptiune();
}

int Meniu::alegeOptiune() {
    int optiune = -1;
    while(optiune < 0 || optiune > 8){
        cout << "0. Exit\n"
             << "1. Citirea n produse noi\n"
             << "2. Afisarea produselor\n"
             << "3. Editarea unui produs dupa index\n"
             << "4. Ordonarea produselor dupa pret in mod crescator\n"
             << "5. Cautarea unei carti dupa titlu\n"
             << "6. Afisarea produsului cu cea mai mare cantitate disponibila\n";
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < 0 || optiune > 6)
            cout << "Optiune invalida!\n";
    }

    if(optiune == 1)
        citesteListaProduse();
    else if(optiune == 2)
        afisareListaProduse();
    else if(optiune == 3)
        editareProdus();
    else if(optiune == 4)
        sorteazaLista();
    else if(optiune == 5)
        cautaCarte();
    else cautaCantitateaMaxima();

    return optiune;
}

void Meniu::citesteListaProduse() {
    int n;
    cout << "Numarul de n produse noi:"; cin >> n;
    listaProduse.clear();
    for(int i = 0; i < n; i++)
        adaugaElement();
}

void Meniu::adaugaElement() {
    int tip = 0;
    while (tip < 1 || tip > 5) {
        cout << "1. Carte\n"
             << "2. DVD Muzica\n"
             << "3. DVD Film\n"
             << "4. Obiect de colectie de tip figurina\n"
             << "5. Obiect de colectie de tip poster\n";
        cout << "Tipul ales:";
        cin >> tip;
        if (tip < 0 || tip > 5)
            cout << "Tip invalid!\n";
    }
    shared_ptr<Produs> temp;
    if (tip == 1)
        temp = make_shared<Carte>();
    else if (tip == 2)
        temp = make_shared<DVDMuzica>();
    else if (tip ==3)
        temp = make_shared<DVDFilm>();
    else if(tip == 4)
        temp = make_shared<ObiectColectieFigurina>();
    else if(tip == 5) temp = make_shared<ObiectColectiePoster>();

    cin >> *temp;
    listaProduse.push_back(temp);
}

void Meniu::afisareListaProduse() const {
    cout << "Lista de produse este:\n";
    for(int i = 0; i < listaProduse.size(); i++)
        cout << "Produsul cu numarul " << i << " este:\n" << *listaProduse[i];
}

void Meniu::editareProdus() {
    afisareListaProduse();
    int idx;
    cout << "Editeaza produsul de pe pozitia:"; cin >> idx;
    try{
        if(idx > listaProduse.size() || idx < 0)
            throw out_of_range("Index invalid!\n");

        cin >> *listaProduse[idx];
    } catch (out_of_range){
        cout << "Index invalid!\n";
    }
}

void Meniu::sorteazaLista() {
    vector< shared_ptr<Produs> > nouaListaDeProduse;
    vector< pair <int, int> > vectorDeSortat;

    for(int i = 0; i < listaProduse.size(); i++){
        pair<int, int> temp = {-listaProduse[i].get()->getPret(), i};
        vectorDeSortat.push_back(temp);
    }

    sort(vectorDeSortat.begin(), vectorDeSortat.end());

    for(int i = 0; i < listaProduse.size(); i++)
        nouaListaDeProduse.push_back(listaProduse[vectorDeSortat[i].second]);

    listaProduse.clear();
    listaProduse = nouaListaDeProduse;

    afisareListaProduse();
}

void Meniu::cautaCarte() {
    string numeCautat;
    cout << "Nume cautat al cartii:";
    readString(cin, numeCautat);
    for(int i = 0; i < listaProduse.size(); i++){
        Carte *cartePointer = dynamic_cast<Carte *>(listaProduse[i].get());
        if(cartePointer != nullptr){
            if(numeCautat == cartePointer->getTitlu()){
                cout << "A fost gasita cartea cu numele " << numeCautat << "\nCartea contine datele:\n" << *cartePointer;
            }
        }
    }
}

void Meniu::cautaCantitateaMaxima() {
    int maxValue = 0, maxIdx = 0;
    for(int i = 0; i < listaProduse.size(); i++){
        int tempValue = listaProduse[i]->getCantitate();
        if(tempValue > maxValue){
            maxValue = tempValue;
            maxIdx = i;
        }
    }
    cout << "Cantitatea maxima a unui produs este " << maxValue << ".\nDatele despre acest produs sunt:" << *listaProduse[maxIdx];
}

int main() {

    Meniu meniu;
    meniu.startMeniu();

    return 0;
}
