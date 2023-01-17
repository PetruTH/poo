#include <bits/stdc++.h>

using namespace std;
const int ANULCURENT = 2022;
const int LUNACURENTA = 06;
const int ZIUACURENTA = 06;

/*
 * Cristea Petru-Theodor
 */

template <typename T>
istream& operator>>(istream& is, vector<T> &v){
    int n;
    T temp;
    cout << "Numarul de elemente = ";
    is >> n;
    for(int i = 0; i < n; i++){
        cout << "Elementul " << i << ":";
        is >> *temp;
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
    for(int i = 0; i < v.size(); i++)
        os << "Elementul " << i << ":\n" << v[i];

    return os;
}

class IOBase{
public:

    void readString(istream &, string &);

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

void IOBase::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0)
        getline(is, s);
}

class Produs : public IOBase {
    static int currentID;

protected:
    const int ID = currentID++;
    string nume;
    int pret, cantitate;
    vector<string> sponsori;

public:
    Produs(const string &nume, int pret, int cantitate, const vector<string> &sponsori) : nume(nume), pret(pret),cantitate(cantitate), sponsori(sponsori) {

    }

    Produs() { }

    virtual ~Produs() = default;

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Nume:"; readString(is, nume);
        cout << "Pret:"; is >> pret;
        cout << "Cantitate:"; is >> cantitate;
        cout << "Lista de sponsori:\n"; is >> sponsori;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Nume:" << nume << '\n';
        os << "Pret:" << pret << '\n';
        os << "Cantitate:" << cantitate << '\n';
        os << "Sponsori:\n" << sponsori << '\n';

        return os;
    }

    int getPret() const {
        return pret;
    }

    int getCantitate() const {
        return cantitate;
    }

};

class ProdusCareExpira : public Produs {
protected:
    bool poateExpira = true;
    bool destinateCopiilor;
    int an, luna, zi;

public:
    ProdusCareExpira(const string &nume, int pret, int cantitate, const vector<string> &sponsori,
                     bool poateExpira) : Produs(nume, pret, cantitate, sponsori), poateExpira(poateExpira) { }

    ProdusCareExpira() { }

    virtual ~ProdusCareExpira() = default;

    istream &read(istream &is) override {
        Produs::read(is);
        cout << "Sunt destinate copiilor?(0 - Nu 1 - Da):"; is >> destinateCopiilor;
        cout << "Data la care expira:\nAnul:"; is >> an;
        cout << "Luna:"; is >> luna;
        cout << "Ziua:"; is >> zi;

        return is;
    }

    ostream &write(ostream &os) const override {
        Produs::write(os);
        if(destinateCopiilor)
            os << "Sunt destinate copiilor\n";
        else os << "Sunt destinate adultilor\n";
        os << "Data la care expira:\nAnul:" << an << '\n';
        os << "Luna:" << luna << '\n';
        os << "Ziua:" << zi << '\n';

        return os;
    }

    int getAn() const {
        return an;
    }

    int getLuna() const {
        return luna;
    }

    int getZi() const {
        return zi;
    }

    bool isDestinateCopiilor() const {
        return destinateCopiilor;
    }
};

class ProdusClasic : public ProdusCareExpira {
    vector<string> listaProprietati, listaEfecteAdverse;
    string aroma;
    bool placebo = false;

public:
    ProdusClasic(const string &nume, int pret, int cantitate, const vector<string> &sponsori,
                 bool poateExpira, const vector<string> &listaProprietati, const vector<string> &listaEfecteAdverse,
                 const string &aroma) : ProdusCareExpira(nume, pret, cantitate, sponsori,
                                                                       poateExpira), listaProprietati(listaProprietati),
                                                      listaEfecteAdverse(listaEfecteAdverse), aroma(aroma),
                                                      placebo(placebo) { }

    ProdusClasic() { }

    virtual ~ProdusClasic() = default;

    istream &read(istream &is) override {
        ProdusCareExpira::read(is);
        cout << "Lista de proprietati:\n"; is >> listaProprietati;
        cout << "Lista de efecte adverse:\n"; is >> listaEfecteAdverse;
        cout << "Aroma:"; readString(is, aroma);

        return is;
    }

    ostream &write(ostream &os) const override {
        ProdusCareExpira::write(os);
        os << "Lista de proprietati:\n" << listaProprietati << '\n';
        os << "Lista de efecte adverse:\n" << listaEfecteAdverse << '\n';
        os << "Aroma:" << aroma << '\n';

        return os;
    }
};

class ProdusComplex : public ProdusCareExpira {
    vector<string> listaProprietati, listaEfecteAdverse;
    string aroma;

public:
    ProdusComplex(const string &nume, int pret, int cantitate, const vector<string> &sponsori,
                 bool poateExpira, const vector<string> &listaProprietati, const vector<string> &listaEfecteAdverse) : ProdusCareExpira(nume, pret, cantitate, sponsori,
                                                         poateExpira), listaProprietati(listaProprietati),
                                        listaEfecteAdverse(listaEfecteAdverse), aroma(aroma) { }

    ProdusComplex() { }

    virtual ~ProdusComplex() = default;

    istream &read(istream &is) override {
        ProdusCareExpira::read(is);
        cout << "Lista de proprietati:\n"; is >> listaProprietati;
        cout << "Lista de efecte adverse:\n"; is >> listaEfecteAdverse;
        cout << "Aroma:"; readString(is, aroma);

        return is;
    }

    ostream &write(ostream &os) const override {
        ProdusCareExpira::write(os);
        os << "Lista de proprietati:\n" << listaProprietati << '\n';
        os << "Lista de efecte adverse:\n" << listaEfecteAdverse << '\n';
        os << "Aroma:" << aroma << '\n';

        return os;
    }
};

class Furnizor : public IOBase {
    vector<shared_ptr<Produs> > listaProduse;
    vector<string> listaSponsori;
    double procentReducere;

public:
    Furnizor(const vector<shared_ptr<Produs>> &listaProduse) : listaProduse(listaProduse) { }

    Furnizor() { }

    virtual ~Furnizor() = default;

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Procentul de reducere:"; is >> procentReducere;
        cout << "Lista de sponsori:\n"; is >> listaSponsori;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Procentul de reducere:" << procentReducere << '\n';
        os << "Lista de sponsori:\n" << listaSponsori << '\n';

        return os;
    }

    void adaugaProdus(shared_ptr<Produs> temp){
        listaProduse.push_back(temp);
    }

    double getProcentReducere() const {
        return procentReducere;
    }
};

int Produs::currentID = 1;

class BaseMenu {
public:
    virtual void listOptions(int optiune) = 0;

    virtual int chooseOption(int first, int last) const = 0;

    virtual void mainLoop() = 0;
};

class Menu : public BaseMenu {
    static Menu *uniqueMenu;

    Menu() { }

    double reducere;
    vector<shared_ptr<Produs> > listaProduseStoc;
    vector<Furnizor> listaFurnizori;

public:
    static Menu *instance(){
        if(uniqueMenu == NULL)
            uniqueMenu = new Menu();
        return uniqueMenu;
    }

    void readString(istream &, string &);

    void listOptions(int optiune) override;

    int chooseOption(int first, int last) const override;

    void mainLoop() override;

    void readProducts();

    void calculateValue() const;

    void readDiscount();

    void chooseKProducts();

    void readCar();
};

Menu* Menu::uniqueMenu = NULL;

void Menu::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0)
        getline(is, s);
}

void Menu::listOptions(int optiune) {
    if(optiune == 0)
        return;
    else if(optiune == 1)
        readProducts();
    else if(optiune == 2)
        calculateValue();
    else if(optiune == 3)
        readDiscount();
    else if(optiune == 4)
        chooseKProducts();
    else if(optiune == 5)
        readCar();
}

int Menu::chooseOption(int first, int last) const {
    int optiune = first - 1;
    while(optiune < first || optiune > last){
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < first || optiune > last)
            cout << "Optiune invalida!\n";
    }
    return optiune;
}

void Menu::mainLoop() {
    int optiune = -1;
    while(optiune != 0){
        cout << "0. Exit\n"
             << "1. Citeste n produse noi\n"
             << "2. Calculeaza suma totala investita\n"
             << "3. Adauga reducere la urmatoarea comanda\n"
             << "4. Alege k produse si afla pretul acestora\n"
             << "5. Citirea unei masini si afisarea preturilor pentru fiecare categorie de produs\n";
        optiune = chooseOption(0, 5);
        listOptions(optiune);
    }
}

void Menu::readProducts() {
    int n;
    cout << "Numarul de produse din stoc:"; cin >> n;
    for(int i = 0; i < n; i++){
        bool expira = false, destinatCopiilor = false, clasic = false;
        shared_ptr<Produs> temp;

        cout << "Produsul expira?(0 - nu 1 - da):"; cin >> expira;
        if(expira) {
            cout << "Este destinat copiilor?(0 - nu 1 - da):"; cin >> destinatCopiilor;
            if(destinatCopiilor){
                cout << "Este un produs de tip clasic?(0 - nu 1 - da):"; cin >> clasic;
                if(clasic)
                    temp = make_shared<ProdusClasic>();
                else {
                    temp = make_shared<ProdusComplex>();
                }
            } else {
                temp = make_shared<ProdusCareExpira>();
            }
        } else {
            temp = make_shared<Produs>();
        }

        cin >> *temp;
        listaProduseStoc.push_back(temp);
    }
}

void Menu::calculateValue() const {
    int totalSum = 0;
    for(int i = 0; i < listaProduseStoc.size(); i++){
        totalSum += listaProduseStoc[i]->getPret() * listaProduseStoc[i]->getCantitate();
    }
    cout << "Suma totala investita este:" << totalSum << '\n';
}

void Menu::readDiscount() {
    cout << "Reducerea aplicata pentru urmatoarea comanda:"; cin >> reducere;
}

void Menu::chooseKProducts() {
    int k;
    try {
        cout << "Numarul k de produse:"; cin >> k;
        if(k > listaProduseStoc.size())
            throw invalid_argument("Numarul k este mai mare decat numarul de elemente din stoc!\n");
    } catch (invalid_argument) {
        cout << "Numarul k este mai mare decat numarul de elemente din stoc!\n";
        return;
    }

    int idx;
    map<int, bool> wasAdded;
    double totalSum = 0;
    for(int i = 0; i < k; i++){
        try {
            cout << "Indexul produsului:"; cin >> idx;
            if(idx < 0 || idx >= listaProduseStoc.size())
                throw out_of_range("Indexul nu exista!\n");
            if(wasAdded[idx] == true)
                throw invalid_argument("Elementul a fost deja adaugat!\n");

            totalSum += listaProduseStoc[idx]->getPret() * listaProduseStoc[idx]->getCantitate();
        } catch (out_of_range) {
            cout << "Indexul nu exista!\n";
            i--;
        } catch (invalid_argument) {
            cout << "Elementul a fost deja adaugat!\n";
            i--;
        }
    }
    totalSum = totalSum - totalSum * reducere / (double)100;
    if(totalSum < 0)
        totalSum = 0;
    cout << "Valoarea produselor dupa reducerea aplicata este " << totalSum << '\n';
}

void Menu::readCar(){
    Furnizor temp;
    cout << "Datele despre furnizor\n";
    cin >> temp;

    double totalSumNuExpira = 0, totalSumAdulti = 0, totalSumClasice = 0, totalSumComplexe = 0;

    for(auto it : listaProduseStoc){
        ProdusCareExpira *tempExpira = dynamic_cast<ProdusCareExpira*>(it.get());
        if(tempExpira != nullptr){ // verific daca pot incadra produsul la categoria celor care expira
            bool expirat = false;
            int an = tempExpira->getAn();
            int luna = tempExpira->getLuna();
            int zi = tempExpira->getZi();

            if(an < ANULCURENT)
                expirat = true;
            else if(an == ANULCURENT){
                if(luna < LUNACURENTA)
                    expirat = true;
                else if(luna == LUNACURENTA){
                    if(zi < ZIUACURENTA)
                        expirat = true;
                }
            }

            if(expirat)
                continue;

            if(!tempExpira->isDestinateCopiilor()) // verific daca este destinat copiilor
                totalSumAdulti += tempExpira->getPret() * tempExpira->getCantitate();
            else { // daca nu e destinat copiilor inseamna ca e destinat adultilor
                ProdusClasic *tempClasic = dynamic_cast<ProdusClasic*>(it.get());
                if(tempClasic != nullptr){ // verific daca este un produs de tip clasic
                    totalSumClasice += tempClasic->getPret() * tempClasic->getCantitate();
                } else { // daca nu e un produs de tip clasic, inseamna ca e un produs de tip complex
                    totalSumComplexe += tempExpira->getPret() * tempExpira->getCantitate();
                }
            }
        } else { // produsul nu expira
            totalSumNuExpira += it->getPret() * it->getCantitate();
        }

        temp.adaugaProdus(it);
    }

    listaFurnizori.push_back(temp);
    cout << "Suma totala pentru produsele care nu expira este: " << totalSumNuExpira - totalSumNuExpira * temp.getProcentReducere() / 100 << '\n';
    cout << "Suma totala pentru produsele care sunt destinate adultilor: " << totalSumAdulti - totalSumAdulti * temp.getProcentReducere() / 100 << '\n';
    cout << "Suma totala pentru produsele care sunt destinate copiilor si sunt de tip clasice: " << totalSumClasice - totalSumClasice * temp.getProcentReducere() / 100 << '\n';
    cout << "Suma totala pentru produsele care sunt destinate copiilor si sunt de tip complexe: " << totalSumComplexe - totalSumComplexe * temp.getProcentReducere() / 100 << '\n';
}

int main() {

    Menu *menu = Menu::instance();
    menu->mainLoop();

    return 0;
}
