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

class Comanda : public IOBase {
    static int currentID;

protected:
    int ID, pretFinal;
    string numeClient, adresaClient;
    string timpLivrare;
    vector<string> listaProduse;
    vector<int> cantitateProduse;

public:
    Comanda() { }

    Comanda(const string &numeClient, const string &adresaClient, const string &timpLivrare,
            const vector<string> &listaProduse, const vector<int> &cantitateProduse, int pretFinal) : numeClient(
            numeClient), adresaClient(adresaClient), timpLivrare(timpLivrare), listaProduse(listaProduse),
                                                                                                      cantitateProduse(
                                                                                                              cantitateProduse),
                                                                                                      pretFinal(
                                                                                                              pretFinal) { ID = currentID; currentID++; }

    virtual ~Comanda();

    void readString(istream &is, string &s){
        getline(is, s);
        if(s.size() == 0) getline(is, s);
    }

    istream &read(istream &is) override {
        IOBase::read(is);
        ID = currentID; currentID++;
        cout << "Nume client:"; readString(is, numeClient);
        cout << "Adresa client:"; readString(is, adresaClient);
        cout << "Pretul final:"; is >> pretFinal;
        cout << "Timp de livrare:"; readString(is, timpLivrare);

        cout << "Denumirea produselor:\n"; is >> listaProduse;
        cout << "Cantitatea produselor:\n"; is >> cantitateProduse;

        return is;
    }



    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "ID" << ID << '\n';
        os << "Nume client: " << numeClient << '\n';
        os << "Adresa client: " << adresaClient << '\n';
        os << "Timp de livrare:" << timpLivrare << '\n';
        os << "Produse: ";
        for(int i = 0; i < listaProduse.size(); i++){
            os << listaProduse[i] << " -> x" << cantitateProduse[i];
            if(i + 1 == listaProduse.size())
                os << '\n';
            else os << ", ";
        }
        os << "Pretul final:" << pretFinal << '\n';

        return os;
    }

    int getId() const {
        return ID;
    }

    const string &getNumeClient() const {
        return numeClient;
    }

    int getPretFinal() const {
        return pretFinal;
    }
};

int Comanda::currentID = 1;

Comanda::~Comanda() {

}

class ComandaMancare : public Comanda {
    string numeLocal;

public:
    ComandaMancare() { }

    ComandaMancare(const string &numeClient, const string &adresaClient, const string &timpLivrare,
                   const vector<string> &listaProduse, const vector<int> &cantitateProduse, int pretFinal,
                   const string &numeLocal) : Comanda(numeClient, adresaClient, timpLivrare, listaProduse,
                                                      cantitateProduse, pretFinal), numeLocal(numeLocal) { }

    virtual ~ComandaMancare() {

    }

    istream &read(istream &is) override {
        Comanda::read(is);
        cout << "Nume local:"; readString(is, numeLocal);

        return is;
    }

    ostream &write(ostream &os) const override {
        Comanda::write(os);
        os << "Nume local:" << numeLocal << '\n';

        return os;
    }
};

class ComandaFastFood : public ComandaMancare {
    int discount;

public:
    ComandaFastFood() {}

    ComandaFastFood(const string &numeClient, const string &adresaClient, const string &timpLivrare,
                    const vector<string> &listaProduse, const vector<int> &cantitateProduse, int pretFinal,
                    const string &numeLocal, int discount) : ComandaMancare(numeClient, adresaClient, timpLivrare,
                                                                            listaProduse, cantitateProduse, pretFinal,
                                                                            numeLocal), discount(discount) { }

    virtual ~ComandaFastFood() {

    }

    istream &read(istream &is) override {
        ComandaMancare::read(is);
        cout << "Discount:"; is >> discount;

        return is;
    }

    ostream &write(ostream &os) const override {
        os << "Comanda mancare, fast-food, ";
        ComandaMancare::write(os);
        os << "Discount:" << discount<< '\n';

        return os;
    }
};

class ComandaRestaurant : public ComandaMancare {
    bool doresteTacamuri;

public:
    ComandaRestaurant() {}

    ComandaRestaurant(const string &numeClient, const string &adresaClient, const string &timpLivrare,
                      const vector<string> &listaProduse, const vector<int> &cantitateProduse, int pretFinal,
                      const string &numeLocal, bool doresteTacamuri) : ComandaMancare(numeClient, adresaClient,
                                                                                      timpLivrare, listaProduse,
                                                                                      cantitateProduse, pretFinal,
                                                                                      numeLocal),
                                                                       doresteTacamuri(doresteTacamuri) { }

    virtual ~ComandaRestaurant() {

    }

    istream &read(istream &is) override {
        ComandaMancare::read(is);
        cout << "Doreste tacamuri(0.Nu - 1.Da):"; is >> doresteTacamuri;

        return is;
    }

    ostream &write(ostream &os) const override {
        os << "Comanda mancare, restaurant, ";
        ComandaMancare::write(os);
        cout << "Doreste tacamuri(0.Nu - 1.Da):" << doresteTacamuri << '\n';

        return os;
    }
};

class ComandaMedicamente : public Comanda {
    vector<bool> esteAntibiotic;

public:
    ComandaMedicamente() {}

    ComandaMedicamente(const string &numeClient, const string &adresaClient, const string &timpLivrare,
                       const vector<string> &listaProduse, const vector<int> &cantitateProduse, int pretFinal,
                       const vector<bool> &esteAntibiotic) : Comanda(numeClient, adresaClient, timpLivrare,
                                                                     listaProduse, cantitateProduse, pretFinal),
                                                             esteAntibiotic(esteAntibiotic) {}

    virtual ~ComandaMedicamente() {

    }

    istream &read(istream &is) override {
        Comanda::read(is);
        cout << "Este antibiotic?(0. Nu - 1. Da)\n"; is >> esteAntibiotic;

        return is;
    }

    ostream &write(ostream &os) const override {
        os << "Comanda medicamente, ";
        Comanda::write(os);
        os << "Este antibiotic?(0. Nu - 1. Da)\n" << esteAntibiotic << '\n';

        return os;
    }

    bool contineAntibiotic() const;
};

bool ComandaMedicamente::contineAntibiotic() const {
    bool valueBool = false;
    for(auto it = esteAntibiotic.begin(); it != esteAntibiotic.end(); ++it)
        valueBool |= *it;

    return valueBool;
}

class ComandaTigari : public Comanda {
    vector<bool> tigaraClasica;

public:
    ComandaTigari() {}

    ComandaTigari(const string &numeClient, const string &adresaClient, const string &timpLivrare,
                       const vector<string> &listaProduse, const vector<int> &cantitateProduse, int pretFinal,
                       const vector<bool> &tigaraClasica) : Comanda(numeClient, adresaClient, timpLivrare,
                                                                     listaProduse, cantitateProduse, pretFinal),
                                                             tigaraClasica(tigaraClasica) {}

    virtual ~ComandaTigari() {

    }

    istream &read(istream &is) override {
        Comanda::read(is);
        cout << "Este o tigara clasica?(0. Nu - 1. Da)\n"; is >> tigaraClasica;

        return is;
    }

    ostream &write(ostream &os) const override {
        os << "Comanda tigari, ";
        Comanda::write(os);
        os << "Este o tigara clasica?(0. Nu - 1. Da)\n" << tigaraClasica << '\n';

        return os;
    }
};

class Meniu {
    vector<shared_ptr<Comanda> > listaDeComenzi;

public:
    Meniu() { }

    void readString(istream &, string &);

    void startMeniu();

    int alegeOptiune();

    void adaugaElement();

    void afiseazaLista() const;

    bool cautaID(int, bool = true) const;

    void stergeElementID(int);

    void cautaNume(string) const;

    void sorteazaLista();

    template<class T>
    void cautaDupaTip(T*);

    void gestionareComenzi();
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
             << "1. Citire n comenzi noi\n"
             << "2. Adaugare comanda\n"
             << "3. Afisare comenzi\n"
             << "4. Sterge comanda dupa ID\n"
             << "5. Cauta comanda dupa ID\n"
             << "6. Cauta comanda dupa numele clientului\n"
             << "7. Ordonare comenzi dupa pret in mod descrescator\n"
             << "8. Gestionare comenzi\n";
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < 0 || optiune > 8)
            cout << "Optiune invalida!\n";
    }

    if(optiune == 1){
        listaDeComenzi.clear();
        int n;
        cout << "Numarul de elemente noi citite:"; cin >> n;
        for(int i = 0; i < n; i++)
            adaugaElement();
    } else if(optiune == 2){
        adaugaElement();
    } else if(optiune == 3){
        afiseazaLista();
    } else if(optiune == 4){
        int ID;
        cout << "ID cautat:"; cin >> ID;
        stergeElementID(ID);
    } else if(optiune == 5) {
        int ID;
        cout << "ID cautat:"; cin >> ID;
        cautaID(ID);
    } else if(optiune == 6){
        string  nume;
        cout << "Nume cautat:"; readString(cin, nume);
        cautaNume(nume);
    } else if(optiune == 7){
        sorteazaLista();
    } else if(optiune == 8){
        gestionareComenzi();
    }

    return optiune;
}

void Meniu::adaugaElement() {
    int tip = 0;
    while (tip < 1 || tip > 4) {
        cout << "Tipul ales:";
        cin >> tip;
        if (tip < 0 || tip > 4)
            cout << "Tip invalid!\n";
    }
    shared_ptr<Comanda> temp;
    if (tip == 1)
        temp = make_shared<ComandaFastFood>();
    else if (tip == 2)
        temp = make_shared<ComandaRestaurant>();
    else if (tip ==3)
        temp = make_shared<ComandaMedicamente>();
    else temp = make_shared<ComandaTigari>();

    cin >> *temp;
    listaDeComenzi.push_back(temp);
}

void Meniu::afiseazaLista() const {
    for(int i = 0; i < listaDeComenzi.size(); i++){
        cout << "Comanda numarul " << i << ":\n" << *listaDeComenzi[i] << '\n';
    }
}

bool Meniu::cautaID(int ID, bool printIsOk) const {
    try {
        if(ID > listaDeComenzi.size() || ID < 1)
            throw out_of_range("ID-ul nu a fost gasit!\n");
        ID--;
        if(printIsOk)
            cout << "Comanda a fost gasit cu succes!\n" << *listaDeComenzi[ID] << '\n';

        return true;
    } catch (out_of_range) {
        cout << "ID-ul nu a fost gasit!\n";

        return false;
    }
}

void Meniu::stergeElementID(int ID) {
    if(!cautaID(ID, false))
        return;

    for(auto it = listaDeComenzi.begin(); it != listaDeComenzi.end(); it++){
        int tempID = it->get()->getId();
        if(tempID == ID){
            listaDeComenzi.erase(it, it + 1);
            break;
        }
    }

    afiseazaLista();
}

void Meniu::cautaNume(string nume) const {
    for(auto it = listaDeComenzi.begin(); it != listaDeComenzi.end(); it++){
        string tempNume = it->get()->getNumeClient();
        if(tempNume == nume)
            cout << "A fost gasita o comanda pe numele " << nume << ":\n" << *it;
    }
}

void Meniu::sorteazaLista() {
    vector< shared_ptr<Comanda> > nouaListaDeComenzi;
    vector< pair <int, int> > vectorDeSortat;

    for(int i = 0; i < listaDeComenzi.size(); i++){
        pair<int, int> temp = {-listaDeComenzi[i].get()->getPretFinal(), i};
        vectorDeSortat.push_back(temp);
    }

    sort(vectorDeSortat.begin(), vectorDeSortat.end());

    for(int i = 0; i < listaDeComenzi.size(); i++)
        nouaListaDeComenzi.push_back(listaDeComenzi[vectorDeSortat[i].second]);

    listaDeComenzi.clear();
    listaDeComenzi = nouaListaDeComenzi;

    afiseazaLista();
}

template<class T>
void Meniu::cautaDupaTip(T *temp) {
    bool wasFound = false;
    cout << "Lista comenzilor de tipul fast food:\n";
    for(auto it = listaDeComenzi.begin(); it != listaDeComenzi.end(); ++it){
        temp = dynamic_cast<T *>(it->get());
        if(temp != nullptr){
            cout << *temp;
            wasFound = true;
        }
    }
    if(!wasFound)
        cout << "Nu exista!\n";
}

void Meniu::gestionareComenzi() {
    ComandaFastFood *coamndaFastFood;
    cautaDupaTip(coamndaFastFood);

    ComandaRestaurant *coamndaRestaurant;
    cautaDupaTip(coamndaRestaurant);

    ComandaMedicamente *comandaMedicamente;
    cautaDupaTip(comandaMedicamente);

    ComandaTigari *comandaTigari;
    cautaDupaTip(comandaTigari);

    bool wasFound = false;
    cout << "Lista comenzilor de tipul medicamente care contin un antibiotic:\n";
    for(auto it = listaDeComenzi.begin(); it != listaDeComenzi.end(); ++it){
        ComandaMedicamente *comandaMedicamente = dynamic_cast<ComandaMedicamente *>(it->get());
        if(comandaMedicamente != nullptr){
            if(comandaMedicamente->contineAntibiotic()) {
                cout << *comandaMedicamente;
                wasFound = true;
            }
        }
    }
    if(!wasFound)
        cout << "Nu exista!\n";
}

int main() {

    Meniu meniuCRUD;

    meniuCRUD.startMeniu();

    return 0;
}
