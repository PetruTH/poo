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
        getline(is, temp);
        v.push_back(temp);
    }

    return is;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v){
    os << "Numarul de elemente = " << v.size() << '\n';
    for(int i = 0; i < v.size(); i++){
        os << "Elementul " << i << ":\n" << *v[i] << '\n';
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

class Masina : public IOBase{

protected:
    int anModel;
    string numeModel;
    int vitezaMaxima, greutate;

public:
    Masina() { }

    Masina(int anModel, const string &numeModel, int vitezaMaxima, int greutate) : anModel(anModel),
                                                                                   numeModel(numeModel),
                                                                                   vitezaMaxima(vitezaMaxima),
                                                                                   greutate(greutate) { }

    virtual ~Masina() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Anul de productie:"; is >> anModel;
        cout << "Nume model:"; is >> numeModel;
        cout << "Viteza maxima:"; is >> vitezaMaxima;
        cout << "Greutate:"; is >> greutate;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Anul de productie:" << anModel << '\n';
        os << "Nume model:" << numeModel << '\n';
        os << "Viteza maxima:" << vitezaMaxima << '\n';
        os << "Greutate:" << greutate << '\n';

        return os;
    }

    const string &getNumeModel() const {
        return numeModel;
    }

    int getVitezaMaxima() const {
        return vitezaMaxima;
    }

    void setVitezaMaxima(int vitezaMaxima) {
        Masina::vitezaMaxima = vitezaMaxima;
    }

    virtual double calculeazaAutonomie() const{
        return 0;
    };
};

class MasinaFosil : virtual public Masina {
protected:
    string combustibil;
    int capacitateRezervor;

public:
    MasinaFosil() { }

    MasinaFosil(int anModel, const string &numeModel, int vitezaMaxima, int greutate, const string &combustibil,
                int capacitateRezervor) : Masina(anModel, numeModel, vitezaMaxima, greutate), combustibil(combustibil),
                                          capacitateRezervor(capacitateRezervor) { }

    virtual ~MasinaFosil() {

    }

    istream &read(istream &is) override {
        Masina::read(is);
        while(combustibil != "benzina" && combustibil != "motorina"){
            cout << "Tip combustibil: "; cin >> combustibil;
            if(combustibil != "benzina" && combustibil != "motorina")
                cout << "Tip invalid!\n";
        }
        cout << "Capacitate rezervor:"; is >> capacitateRezervor;

        return is;
    }

    ostream &write(ostream &os) const override {
        Masina::write(os);
        os << "Tip combustibil:" << combustibil << '\n';
        os << "Capacitate rezervor:" << capacitateRezervor << '\n';

        return os;
    }

    double calculeazaAutonomie() const override {
        return (double)capacitateRezervor / sqrt(greutate);
    }
};

class MasinaElectrica : virtual public Masina {
protected:
    int capacitateBaterie;

public:
    MasinaElectrica() { }

    MasinaElectrica(int anModel, const string &numeModel, int vitezaMaxima, int greutate, int capacitateBaterie)
            : Masina(anModel, numeModel, vitezaMaxima, greutate), capacitateBaterie(capacitateBaterie) { }

    virtual ~MasinaElectrica() {

    }

    istream &read(istream &is) override {
        Masina::read(is);
        cout << "Capacitate baterie:"; is >> capacitateBaterie;

        return is;
    }

    ostream &write(ostream &os) const override {
        Masina::write(os);
        os << "Capacitate baterie:" << capacitateBaterie << '\n';

        return os;
    }

    double calculeazaAutonomie() const override {
        return (double)capacitateBaterie / (greutate * greutate);
    }
};

class MasinaHibrid : public MasinaFosil, public MasinaElectrica {

public:
    MasinaHibrid() { }

    MasinaHibrid(int anModel, const string &numeModel, int vitezaMaxima, int greutate, const string &combustibil,
                 int capacitateRezervor, int anModel1, const string &numeModel1, int vitezaMaxima1, int greutate1,
                 int capacitateBaterie) : MasinaFosil(anModel, numeModel, vitezaMaxima, greutate, combustibil,
                                                      capacitateRezervor),
                                          MasinaElectrica(anModel1, numeModel1, vitezaMaxima1, greutate1,
                                                          capacitateBaterie) { }

    virtual ~MasinaHibrid() {

    }

    istream &read(istream &is) override {
        MasinaElectrica::read(is);
        combustibil = "benzina";
        cout << "Capacitate rezervor:"; is >> capacitateRezervor;

        return is;
    }

    ostream &write(ostream &os) const override {
        MasinaElectrica::write(os);
        cout << "Tip combustibil:" << combustibil << '\n';
        cout << "Capacitate rezervor:" << capacitateRezervor << '\n';

        return os;
    }

    double calculeazaAutonomie() const override {
        double autonomieFosil = (double)capacitateRezervor / sqrt(greutate);
        double autonomieElectrica = (double)capacitateBaterie / (greutate * greutate);

        return autonomieFosil + autonomieElectrica;
    }
};

class Tranzactie : public IOBase {
    string numeClient, data;
    vector<shared_ptr<Masina> > listaMasini;

public:
    Tranzactie() { }

    Tranzactie(const string &numeClient, const string &data, const vector<shared_ptr<Masina>> &listaMasini)
            : numeClient(numeClient), data(data), listaMasini(listaMasini) { }

    virtual ~Tranzactie() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Nume client:"; is >> numeClient;
        cout << "Data:"; is >> data;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        cout << "Nume client:" << numeClient << '\n';
        cout << "Data:" << data << '\n';
        cout << "Lista cu masini cumparate:\n" << listaMasini;

        return os;
    }

    void adaugaMasina(shared_ptr<Masina> temp){
        listaMasini.push_back(temp);
    }

    int getSizeListaMasini(){
        return listaMasini.size();
    }

    shared_ptr<Masina> operator[](int idx){
        try{
            if(idx < 0 || idx >= listaMasini.size())
                throw out_of_range("Index invalid!\n");

            return listaMasini[idx];
        } catch (out_of_range) {
            cout << "Index invalid!\n";
        }
    }
};

class Meniu {
    vector<shared_ptr<Masina> > listaMasini;
    vector<Tranzactie> listaTranzactii;

public:
    Meniu() { }

    void readString(istream &, string &);

    void startMeniu();

    int alegeOptiune();

    void adaugaMasina();

    void afiseazaListaMasini() const;

    shared_ptr<Masina> returneazaMasinaNoua() const;

    void adaugaTranzactie();

    void modelulCelMaiVandut();

    void afiseazaAutonomieMaxima();

    void cresteVitezaMaxima();

    int cautaModel(const string&) const;
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
    while(optiune < 0 || optiune > 6){
        cout << "0. Exit\n"
             << "1. Adauga un model noua de masina\n"
             << "2. Adauga o tranzactie noua\n"
             << "3. Afiseaza cel mai vandut model\n"
             << "4. Afiseaza modelul cu autonomia cea mai mare\n"
             << "5. Creste viteza unui model cu un anumit procent\n"
             << "6. Afiseaza toate masinile\n";
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < 0 || optiune > 6)
            cout << "Optiune invalida!\n";
    }

    if(optiune == 1)
        adaugaMasina();
    else if(optiune == 2)
        adaugaTranzactie();
    else if(optiune == 3)
        modelulCelMaiVandut();
    else if(optiune == 4)
        afiseazaAutonomieMaxima();
    else if(optiune == 5)
        cresteVitezaMaxima();
    else if(optiune == 6)
        afiseazaListaMasini();

    return optiune;
}

void Meniu::adaugaMasina() {
    listaMasini.push_back(returneazaMasinaNoua());
}

shared_ptr<Masina> Meniu::returneazaMasinaNoua() const {
    int tip = 0;
    while(tip < 1 || tip > 3){
        cout << "1. Masina pe combustibil fosil\n2. Masina electrica\n3. Masina hibrid\nTipul ales:";
        cin >> tip;
        if(tip < 1 || tip > 3)
            cout << "Tipul ales este invalid!\n";
    }

    shared_ptr<Masina> temp;
    if (tip == 1)
        temp = make_shared<MasinaFosil>();
    else if (tip == 2)
        temp = make_shared<MasinaElectrica>();
    else if (tip == 3)
        temp = make_shared<MasinaHibrid>();

    cin >> *temp;

    return temp;
}

void Meniu::afiseazaListaMasini() const {
    cout << "Lista cu masini este:\n";
    int i = 0;
    for(auto it : listaMasini) {
        cout << "Masina cu indexul " << i << " este:\n" << *it;
        i++;
    }
}

void Meniu::adaugaTranzactie() {
    Tranzactie temp;
    int n, idx;
    afiseazaListaMasini();
    cout << "\nPentru cumpararea unei masini, introduce indexul corespondent masinii din stoc.\n";
    cout << "Numarul de masini cumparate:"; cin >> n;
    for(int i = 0; i < n; i++) {
        try {
            cout << "Indexul masinii " << i + 1 << " este: ";
            cin >> idx;

            if(idx < 0 || idx >= listaMasini.size())
                throw out_of_range("Index invalid!\n");

            temp.adaugaMasina(listaMasini[idx]);
        } catch (out_of_range) {
            cout << "Index invalid!\n";
            i--;
        }
    }

    listaTranzactii.push_back(temp);
}

void Meniu::modelulCelMaiVandut() {
    map<string, int> frecvModel;

    for(auto it : listaTranzactii){
        int n = it.getSizeListaMasini();
        for(int i = 0; i < n; i++){
            string numeModel = it[i]->getNumeModel();
            if(frecvModel.find(numeModel) == frecvModel.end())
                frecvModel[numeModel] = 0;
            frecvModel[numeModel]++;
        }
    }

    int cnt = 0;
    string numeModel;
    for(auto it : frecvModel)
        if(it.second > cnt){
            cnt = it.second;
            numeModel = it.first;
        }

    cout << "Modelul cel mai vandut este ";
    int idx = cautaModel(numeModel);

    MasinaFosil *tempFosil = dynamic_cast<MasinaFosil *>(listaMasini[idx].get());
    if(tempFosil != nullptr)
        cout << "o masina pe combustibil fosil";

    MasinaElectrica *tempElectrica = dynamic_cast<MasinaElectrica *>(listaMasini[idx].get());
    if(tempElectrica != nullptr)
        cout << "o masina electrica";

    MasinaHibrid *tempHibrid = dynamic_cast<MasinaHibrid *>(listaMasini[idx].get());
    if(tempHibrid != nullptr)
        cout << "o masina hibrid";

    cout << " iar numele modelului este "<< numeModel << '\n';
}

void Meniu::afiseazaAutonomieMaxima() {
    string numeModel;
    double maxAutonomie = 0;
    for(auto it : listaMasini){
        if(it->calculeazaAutonomie() > maxAutonomie){
            maxAutonomie = it->calculeazaAutonomie();
            numeModel = it->getNumeModel();
        }
    }
    cout << "Modelul cu autonomia cea mai mare este " << numeModel << '\n';
}

int Meniu::cautaModel(const string &numeModel) const {
    int idx = 0;
    for(auto it : listaMasini) {
        if (it->getNumeModel() == numeModel)
            return idx;
        idx++;
    }
    return -1;
}

void Meniu::cresteVitezaMaxima() {
    string numeModel;
    double procent;
    cout << "Procentul cu care va creste este:"; cin >> procent;
    cout << "Modelul pentru care se doreste sa creasca viteza este:"; cin >> numeModel;
    try{
        int idx = cautaModel(numeModel);
        if(idx == -1)
            throw invalid_argument("Modelul nu exista!\n");

        int vitezaMaximaCurenta = listaMasini[idx]->getVitezaMaxima();
        vitezaMaximaCurenta += int(vitezaMaximaCurenta * procent / 100);
        listaMasini[idx]->setVitezaMaxima(vitezaMaximaCurenta);

    } catch (invalid_argument){
        cout << "Modelul nu exista!\n";
        return;
    }
}

int main() {

    Meniu meniu;
    meniu.startMeniu();

    return 0;
}
