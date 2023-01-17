#include <bits/stdc++.h>

using namespace std;

//Cristea Petru-Theodor

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

class Statie : public IOBase{
    static int currentID;

protected:
    string adresa;
    vector<string> codMijloaceTransport;
    int codStatie;
    string numeStatie, codInternAsociat;

public:
    Statie() { }

    Statie(const string &adresa, const vector<string> &codMijloaceTransport, const string &numeStatie,
           const string &codInternAsociat) : adresa(adresa), codMijloaceTransport(codMijloaceTransport),
                                             numeStatie(numeStatie),
                                             codInternAsociat(codInternAsociat) { codStatie = currentID; currentID++; }

    virtual ~Statie() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Adresa:"; readString(is, adresa);
        cout << "Lista cu codurile asociate mijloacelor de transport:\n"; is >> codMijloaceTransport;
        cout << "Nume statie:"; readString(is, numeStatie);
        cout << "Cod intern asociat:"; is >> codInternAsociat;
        codStatie = currentID; currentID++;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Cod statie:" << codStatie << '\n';
        os << "Adresa:" << adresa << '\n';
        os << "Lista cu codurile asociate mijloacelor de transport:\n" << codMijloaceTransport << '\n';
        os << "Nume statie:" << numeStatie << '\n';
        os << "Cod intern asociat:" << codInternAsociat << '\n';

        return os;
    }

    const string &getAdresa() const {
        return adresa;
    }

    const vector<string> &getCodMijloaceTransport() const {
        return codMijloaceTransport;
    }

    int getCodStatie() const {
        return codStatie;
    }

    const string &getNumeStatie() const {
        return numeStatie;
    }

    const string &getCodInternAsociat() const {
        return codInternAsociat;
    }

    void readString(istream &, string &);

    bool cautaCodAutobuzInLista(string);
};

int Statie::currentID = 1;

void Statie::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0) getline(is, s);
}

bool Statie::cautaCodAutobuzInLista(string val) {
    for(auto it : codMijloaceTransport)
        if(it == val)
            return true;
    return false;
}

class Meniu {
    vector<shared_ptr<Statie> > listaStatii;
    map<string, bool> listaAutobuze;

public:
    Meniu() { }

    void readString(istream &, string &);

    void startMeniu();

    int alegeOptiune();

    void adaugaElement();

    void cautaStatie();

    void afiaseazaStatiiAutobuz();
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
             << "1. Adauga o statie noua\n"
             << "2. Cauta statie folosind numele, adresa sau codul statiei\n"
             << "3. Afisare comenzi\n"
             << "4. Sterge comanda dupa ID\n";
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < 0 || optiune > 8)
            cout << "Optiune invalida!\n";
    }

    if(optiune == 1)
        adaugaElement();
    else if(optiune == 2)
        cautaStatie();

    return optiune;
}

void Meniu::adaugaElement() {
    shared_ptr<Statie> statie = make_shared<Statie>();
    cin >> *statie;
    vector<string> temp = statie->getCodMijloaceTransport();
    for(auto it : temp)
        listaAutobuze[it] = true;
    listaStatii.push_back(statie);
}

void Meniu::cautaStatie() {
    int optiune = -1;
    while(optiune < 0 || optiune > 3){
        cout << "1. Numele statiei\n"
             << "2. Adresa statiei\n"
             << "3. Codul statiei\n";
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < 0 || optiune > 3)
            cout << "Optiune invalida!\n";
    }
    cout << "Valoarea cautata:";
    if(optiune == 3){
        int idx;
        cin >> idx;

        try{
            if(idx < 1 || idx > listaStatii.size())
                throw out_of_range("Index invalid!\n");
            cout << "A fost gasit statia cu codul " << idx << " si detaliile sunt:\n" << *listaStatii[idx - 1];

            return;
        } catch (out_of_range){
            cout << "Index invalid!\n";

            return;
        }
    }
    string tempValue;
    readString(cin,tempValue);

    for(auto it = listaStatii.begin(); it != listaStatii.end(); ++it){
        string temp;
        if(optiune == 1)
            temp = it->get()->getNumeStatie();
        else if(optiune == 2)
            temp = it->get()->getAdresa();
        cout << temp << '\n';
        if(tempValue == temp){
            cout << "A fost gasit statia cu " << ((optiune == 1) ? "numele " : "adresa ") << tempValue << " si detaliile sunt:\n" << *it->get();

            return;
        }
    }

    cout << "Statia cautata nu a fost gastia!\n";
}

void Meniu::afiaseazaStatiiAutobuz() {
    string IDAutobuz;
    cout << "Codul mijlocului de transport cautat:"; readString(cin, IDAutobuz);
    try{
        if(listaAutobuze.find(IDAutobuz) != listaAutobuze.end())
            throw invalid_argument("Nu exista codul cautat!");

        cout << "Autobuzul trece prin statiile:";
        for(auto it : listaStatii){
            if(it.get()->cautaCodAutobuzInLista(IDAutobuz))
                cout << it.get()->getNumeStatie() << ' ';
        }
        cout << '\n';
    } catch (invalid_argument) {
        cout << "Nu exista codul cautat!\n";

        return;
    }
}

int main() {

    Meniu meniu;
    meniu.startMeniu();

    return 0;
}
