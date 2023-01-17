#include <bits/stdc++.h>

/*
 * Cristea Petru-Theodor
 */

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
        is >> temp;
        v.push_back(temp);
    }

    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v){
    os << "Numarul de elemente = " << v.size() << '\n';
    for(int i = 0; i < v.size(); i++)
        os << "Elementul " << i << ":\n" << v[i] << '\n';

    return os;
}

/*
istream &read(istream &is) override {
    IOBase::read(is);

    return is;
}

ostream &write(ostream &os) const override {
    IOBase::write(os);

    return os;
}
 */


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

    int chooseOption(int first, int last) const;

    void readString(istream &, string &);
};

int IOBase::chooseOption(int first, int last) const {
    int optiune = first - 1;
    while(optiune < first || optiune > last){
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < first || optiune > last)
            cout << "Optiune invalida!\n";
    }
    return optiune;
}

void IOBase::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0)
        getline(is, s);
}

class Vizitator : public IOBase {
protected:
    string nume;
    int varsta;

public:
    Vizitator() { }

    Vizitator(const string &n, const int &v) : nume(n), varsta(v) { }

    virtual ~Vizitator() = default;

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Nume:";
        readString(is, nume);
        cout << "Varsta:"; is >> varsta;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Nume:" << nume << '\n';
        os << "Varsta:" << varsta << '\n';

        return os;
    }

    int getVarsta() const {
        return varsta;
    }
};

class Pensionar : public Vizitator {

public:
    Pensionar() { }

    Pensionar(const Vizitator &v) : Vizitator(v) { }

    virtual ~Pensionar() = default;

    istream &read(istream &is) override {
        return Vizitator::read(is);
    }

    ostream &write(ostream &os) const override {
        return Vizitator::write(os);
    }
};

class Student : public Vizitator {

public:
    Student() { }

    Student(const Vizitator &v) : Vizitator(v) { }

    virtual ~Student() = default;

    istream &read(istream &is) override {
        return Vizitator::read(is);
    }

    ostream &write(ostream &os) const override {
        return Vizitator::write(os);
    }
};

class Eveniment : public IOBase{
    vector <shared_ptr<Vizitator> > listaVizitatori;

protected:
    string titlu;
    int pret;

public:
    Eveniment() { }

    Eveniment(const string &t, const int &p) : titlu(t), pret(p) {
        readParticipants();
    }

    virtual ~Eveniment() = default;

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Titlu specific:"; readString(is, titlu);

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Titlu specific:" << titlu << '\n';

        return os;
    }

    void readParticipants();

    void printParticipants() const;

    double getIncasari() const;
};

void Eveniment::readParticipants() {
    int n;
    cout << "Numarul de vizitatori la muzeu:"; cin >> n;
    for(int i = 0; i < n; i++){
        cout << "Selecteaza tipul de vizitator!\n1. Student\n2. Pensionar\n3. Altele\n";
        int optiune = chooseOption(1, 3);

        shared_ptr<Vizitator> temp;
        if(optiune == 1)
            temp = make_shared<Student>();
        else if(optiune == 2)
            temp = make_shared<Pensionar>();
        else if(optiune == 3)
            temp = make_shared<Vizitator>();

        cin >> *temp;
        listaVizitatori.push_back(temp);
    }
}

void Eveniment::printParticipants() const {
    int n = listaVizitatori.size();
    cout << "Numarul de vizitatori la muzeu:"; cin >> n;
    for(int i = 0; i < n; i++)
        cout << "Vizitatorul cu indexul " << i << " este:\n" << *listaVizitatori[i] << '\n';
}

double Eveniment::getIncasari() const {
    double totalSum = 0;
    for(auto it : listaVizitatori){
        Student *tempStudent = dynamic_cast<Student*>(it.get());
        if(tempStudent != nullptr){
            totalSum += pret * 0.75;
            continue;
        }

        Pensionar *tempPensionar = dynamic_cast<Pensionar*>(it.get());
        if(tempPensionar != nullptr){
            totalSum += pret * 0.5;
            continue;
        }

        if(it->getVarsta() >= 7)
            totalSum += pret;
    }

    return totalSum;
}

class EvenimentGratuit : public Eveniment {
public:
    EvenimentGratuit() { }

    EvenimentGratuit(const string &t) : Eveniment(t, 0) { }

    virtual ~EvenimentGratuit() = default;

    istream &read(istream &is) override {
        Eveniment::read(is);
        pret = 0;
        readParticipants();

        return is;
    }

    ostream &write(ostream &os) const override {
        Eveniment::write(os);
        os << "Pretul de intrare este gratuit!\n";
        printParticipants();

        return os;
    }
};

class EvenimentTemporar : public Eveniment {
    string activitate;
public:
    EvenimentTemporar() { }

    EvenimentTemporar(const string &a, const Eveniment &e) : Eveniment(e), activitate(a) { }

    virtual ~EvenimentTemporar() = default;

    istream &read(istream &is) override {
        Eveniment::read(is);
        cout << "Activitate:"; readString(is, activitate);
        cout << "Pretul de intare:"; is >> pret;
        readParticipants();

        return is;
    }

    ostream &write(ostream &os) const override {
        Eveniment::write(os);
        os << "Activitate:" << activitate << '\n';
        os << "Pretul de intrare:" << pret << '\n';
        printParticipants();

        return os;
    }
};


class EvenimentSpecial : public Eveniment {
    string activitate;
    vector<string> listaParteneri;

public:
    EvenimentSpecial() { }

    EvenimentSpecial(const Eveniment &e) : Eveniment(e) { }

    virtual ~EvenimentSpecial() = default;

    istream &read(istream &is) override {
        Eveniment::read(is);
        cout << "Activitate:"; readString(is, activitate);
        cout << "Pretul de intare:"; is >> pret;
        cout << "Partenerii:\n"; is >> listaParteneri;
        readParticipants();

        return is;
    }

    ostream &write(ostream &os) const override {
        Eveniment::write(os);
        os << "Activitate:" << activitate << '\n';
        os << "Pretul de intrare:" << pret << '\n';
        os << "Partenerii:\n" << listaParteneri;
        printParticipants();

        return os;
    }
};

class Ghid : public IOBase {
    string data;
    int ora, nrPersoane;
    string limba;

    int pret;

public:
    Ghid() { }

    Ghid(const string &d, const int &o, const int &n, const string l) : data(d), ora(o), nrPersoane(n), limba(l) {
        if(nrPersoane > 10)
            pret = 200;
        else pret = 100;
    }

    virtual ~Ghid() = default;

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Data:"; is >> data;
        cout << "Ora:"; is >> ora;
        cout << "Numarul de persoane:"; is >> nrPersoane;
        cout << "Limba:"; is >> limba;
        if(nrPersoane > 10)
            pret = 200;
        else pret = 100;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Data:" << data << '\n';
        os << "Ora:" << ora << '\n';
        os << "Numarul de persoane:" << nrPersoane << '\n';
        os << "Limba:" << limba << '\n';
        os << "Pret:" << pret << '\n';

        return os;
    }
};

class Muzeu : public IOBase {
    string adresa;
    int oraInceperii, oraFinalizarii;
    vector <shared_ptr<Eveniment> > listaEvenimente;
    vector <Ghid> listaGhiduri;
    vector <string> alteServicii;

public:
    Muzeu() { }

    Muzeu(const string &a, const int &i, const int &f, const vector <shared_ptr<Eveniment> > v) : adresa(a), oraInceperii(i), oraFinalizarii(f), listaEvenimente(v) { }

    virtual ~Muzeu() = default;

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Adresa:"; readString(is, adresa);
        cout << "Ora inceperii:"; is >> oraInceperii;
        cout << "Ora finalizarii:"; is >> oraFinalizarii;
        int n;
        cout << "Numarul de evenimente din cadrul muzeului:"; is >> n;
        for(int i = 0; i < n; i++){
            cout << "Selecteaza tipul de eveniment!\n1. Eveniment permanent gratuit\n2. Eveniment temporar\n3. Eveniment special\n";
            int optiune = chooseOption(1, 3);

            shared_ptr<Eveniment> temp;
            if(optiune == 1)
                temp = make_shared<EvenimentGratuit>();
            else if(optiune == 2)
                temp = make_shared<EvenimentTemporar>();
            else if(optiune == 3)
                temp = make_shared<EvenimentSpecial>();

            is >> *temp;
            listaEvenimente.push_back(temp);
        }
        cout << "Servicii de tip ghidaj din cadrul muzeului:\n"; is >> listaGhiduri;
        cout << "Alte servicii din cadrul muzeului:\n"; is >> alteServicii;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Adresa:" << adresa << '\n';
        os << "Ora inceperii:" << oraInceperii << '\n';
        os << "Ora finalizarii:" << oraFinalizarii << '\n';
        int n = listaEvenimente.size();
        os << "Numarul de evenimente din cadrul muzeului:" << n << '\n';
        for(int i = 0; i < n; i++)
            os << "Evenimentul cu indexul " << i << " este:\n" << *listaEvenimente[i];
        os << "Servicii de tip ghidaj din cadrul muzeului:\n" << listaGhiduri;
        os << "Alte servicii din cadrul muzeului:\n" << alteServicii;

        return os;
    }

    double getIncasari() const;
};

double Muzeu::getIncasari() const {
    double totalSum = 0;
    for(auto it : listaEvenimente)
        totalSum += it->getIncasari();

    return totalSum;
}

class BaseMenu {
public:
    virtual void listOptions(int optiune) = 0;

    virtual int chooseOption(int first, int last) const = 0;

    virtual void mainLoop() = 0;
};

class Menu : public BaseMenu {
    vector<Muzeu> listaMuzee;

public:
    void readString(istream &, string &);

    void listOptions(int optiune) override;

    int chooseOption(int first, int last) const override;

    void mainLoop() override;

    void readMuseum();

    void printMuseum();

    void sortMuseum();
};

void Menu::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0)
        getline(is, s);
}

void Menu::listOptions(int optiune) {
    if(optiune == 0)
        return;
    else if(optiune == 1)
        printMuseum();
    else if(optiune == 2)
        sortMuseum();
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
    readMuseum();
    int optiune = -1;
    while(optiune != 0){
        cout << "0. Exit\n"
             << "1. Afisarea vizitatorilor, grupati pe muzee, apoi grupati pe evenimente\n"
             << "2. Afisarea muzeelor in ordinea descrescatoare a incasarilor obtinute\n"
             << "4. \n"
             << "5. \n"
             << "6. \n";
        optiune = chooseOption(0, 6);
        listOptions(optiune);
    }
}

void Menu::readMuseum() {
    int n;
    cout << "Numarul de muzee:"; cin >> n;
    Muzeu temp;
    for(int i = 0; i < n; i++) {
        cout << "Muzeul cu indexul " << i << " este:\n";
        cin >> temp;
        listaMuzee.push_back(temp);
    }
}

void Menu::printMuseum() {
    int n = listaMuzee.size();
    cout << "Numarul de muzee:" << n << '\n';
    for(int i = 0; i < n; i++)
        cout << "Muzeul cu indexul " << i << " este:\n" << listaMuzee[i] << '\n';
}

void Menu::sortMuseum() {
    vector <pair <int, int> > v;
    int i = 0;
    for(auto it : listaMuzee){
        double val = it.getIncasari();
        v.push_back({-val, i});
        i++;
    }
    sort(v.begin(), v.end());
    cout << "Lista muzeelor sortate descrescator dupa incasari este:\n";
    i = 0;
    for(auto it : listaMuzee){
        cout << "Muzeul cu indexul " << v[i].second << " avand incasari de " << v[i].first << " este:\n" << it << '\n';
        i++;
    }
}

int main() {

    Menu meniu;
    meniu.mainLoop();

    return 0;
}
