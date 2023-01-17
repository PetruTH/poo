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
        os << "Elementul " << i << ":\n" << v[i] << '\n';
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

class Vaccin : public IOBase{
protected:
    int pret;
    double temperatura;
    string producator;
    vector<string> listaSubstante;

public:
    Vaccin() { }

    Vaccin(int pret, double temperatura, const string &producator, const vector<string> &listaSubstante) : pret(pret),
                                                                                                             temperatura(
                                                                                                                     temperatura),
                                                                                                             producator(
                                                                                                                     producator),
                                                                                                           listaSubstante(
                                                                                                                   listaSubstante) { }

    virtual ~Vaccin() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Pret:"; is >> pret;
        cout << "Temperatura:"; is >> temperatura;
        cout << "Producator:"; readString(is, producator);
        cout << "Lista cu substante ce le contine:\n"; is >> listaSubstante;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Pret:" << pret << '\n';
        os << "Temperatura:" << temperatura << '\n';
        os << "Producator:" << producator << '\n';
        os << "Lista cu substante ce le contine:\n" << listaSubstante;

        return os;
    }

    const string &getProducator() const {
        return producator;
    }

    int getPret() const {
        return pret;
    }

    void readString(istream &, string &);

    virtual void afisareSchemaVaccinare() const{
        return;
    };
};

class AntiGripal : public Vaccin{
protected:
    string antiTip;
    bool respectaReglementari;

public:
    AntiGripal() { }

    AntiGripal(int pret, double temperatura, const string &producator, const vector<string> &listaSubstante,
               const string &antiTip, const bool &respectaReglementari) : Vaccin(pret, temperatura, producator, listaSubstante), antiTip(antiTip), respectaReglementari(respectaReglementari) { }

    virtual ~AntiGripal() {

    }

    istream &read(istream &is) override {
        Vaccin::read(is);
        int tip = 0;
        while(tip < 1 || tip > 3){
            cout << "1.A-H1N1\n2.A-H3N2\n3.A-California\nTulpina virus(1-3):";
            is >> tip;
            if(tip < 1 || tip > 3)
                cout << "Optiune invalida!\n";
        }
        if(tip == 1)
            antiTip = "A-H1N1";
        else if(tip == 2)
            antiTip = "A-H3N2";
        else if(tip == 3)
            antiTip = "A-California";

        cout << "Respecta reglementarile ONU(0. Nu - 1. Da):"; is >> respectaReglementari;

        return is;
    }

    ostream &write(ostream &os) const override {
        Vaccin::write(os);
        os << "Tulpina virus:" << antiTip << '\n';
        os << "Respecta reglementarile ONU(0. Nu - 1. Da):" << respectaReglementari << '\n';

        return os;
    }

    void afisareSchemaVaccinare() const override {
        cout << "Antigripal se administreaza la adulti o doza de 0.5 ml, iar la copii si adolescenti o doza de 0.3 ml.\n";
    }
};

class AntiHepatita : public Vaccin {
protected:
    string tip, modVaccinare;

public:
    AntiHepatita() {}

    AntiHepatita(int pret, double temperatura, const string &producator, const vector<string> &listaSubstante,
                 const string &tip, const string &modVaccinare) : Vaccin(pret, temperatura, producator, listaSubstante),
                                                                  tip(tip), modVaccinare(modVaccinare) {}

    virtual ~AntiHepatita() {

    }

    istream &read(istream &is) override {
        Vaccin::read(is);
        int optiune = 0;
        while(optiune < 1 || optiune > 3){
            cout << "1.A\n2.B\n3.C\nTip hepatita(1-3):";
            is >> optiune;
            if(optiune < 1 || optiune > 3)
                cout << "Optiune invalida!\n";
        }
        if(optiune == 1)
            tip = "A";
        else if(optiune == 2)
            tip = "B";
        else if(optiune == 3)
            tip = "C";

        cout << "Modul de vaccinare:"; is >> modVaccinare;

        return is;
    }

    ostream &write(ostream &os) const override {
        Vaccin::write(os);
        os << "Tip hepatita:" << tip << '\n';
        os << "Modul de vaccinare:" << modVaccinare << '\n';

        return os;
    }

    void afisareSchemaVaccinare() const override {
        cout << "Antihepatita A si B, la copii cu varsta mai mica de 1 an se adminstreaza 2 injectari la un interval de o luna, a treia injectare dupa 6 luni de la prima administrare, la adulti conform schemei de imunizare recomandată de medic; cel Antihepatita C doar la recomandarea medicului";
    }
};

class Sars_Cov2 : public Vaccin {
    vector <string> reactiiAdverse;
    double eficienta;
    vector <string> medicamenteContraindicate;

public:
    Sars_Cov2() { }

    Sars_Cov2(int pret, double temperatura, const string &producator, const vector<string> &listaSubstante,
              const vector<string> &reactiiAdverse, double eficienta, const vector<string> &medicamenteContraindicate)
            : Vaccin(pret, temperatura, producator, listaSubstante), reactiiAdverse(reactiiAdverse),
              eficienta(eficienta), medicamenteContraindicate(medicamenteContraindicate) { }

    virtual ~Sars_Cov2() {

    }

    istream &read(istream &is) override {
        Vaccin::read(is);
        cout << "Lista cu reactii adverse:\n"; is >> reactiiAdverse;
        cout << "Eficienta:"; is >> eficienta;
        cout << "Lista cu medicamente contraindicate:\n"; is >> medicamenteContraindicate;

        return is;
    }

    ostream &write(ostream &os) const override {
        Vaccin::write(os);
        os << "Lista cu reactii adverse:\n" << reactiiAdverse << '\n';
        os << "Eficienta:" << eficienta;
        os << "Lista cu medicamente contraindicate:\n" << medicamenteContraindicate;

        return os;
    }

    void afisareSchemaVaccinare() const override {
        cout << "Sars-Cov2 se administreaza persoanelor cu varsta de peste 16 ani, 2 doze la o perioada de 21 zile.";
    }
};

class Comanda : public IOBase {
    static int currentID;
    int valoareaTotalComanda;
    bool respectaConditiile;

protected:
    int ID;
    string data, numeClient;
    vector<int> listaVaccinuriComandate;
    vector<int> cantitate;

public:
    Comanda() { }

    Comanda(const string &data, const string &numeClient, const vector<int> &listaVaccinuriComandate,
            int cantitate) : data(data), numeClient(numeClient), listaVaccinuriComandate(listaVaccinuriComandate),
                             cantitate(cantitate) { ID = currentID; currentID++; }

    virtual ~Comanda() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        ID = currentID; currentID++;
        cout << "Data:"; cin >> data;
        cout << "Nume client:"; readString(is, numeClient);
        cout << "Lista cu vaccinuri comandate(scrie doar indexul vaccinurile afisate mai sus prezente in stoc):\n"; is >> listaVaccinuriComandate;
        cout << "Cantitatea pentru fiecare vaccin:\n"; is >> cantitate;


        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "ID:" << ID << '\n';
        os << "Data:" << data << '\n';
        os << "Nume client::" << numeClient << '\n';
        os << "Lista cu vaccinuri comandate(doar indexul vaccinurilor prezente in stoc):\n" << listaVaccinuriComandate;
        os << "Cantitatea pentru fiecare vaccin:\n" << cantitate;
        os << "Total valoarea comanda:" << valoareaTotalComanda << '\n';
        os << "Comanda va fi onorata:" << respectaConditiile << '\n';

        return os;
    }

    void setValoareaTotalComanda(int valoareaTotalComanda) {
        Comanda::valoareaTotalComanda = valoareaTotalComanda;
    }

    void setRespectaConditiile(bool respectaConditiile) {
        Comanda::respectaConditiile = respectaConditiile;
    }

    const string &getData() const {
        return data;
    }

    const vector<int> &getListaVaccinuriComandate() const {
        return listaVaccinuriComandate;
    }

    int totalComanda(const vector<shared_ptr<Vaccin> > &) const;

    bool verificaConditiiComanda();

    void readString(istream &, string &);
};

int Comanda::currentID = 1;

void Comanda::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0) getline(is, s);
}

int Comanda::totalComanda(const vector<shared_ptr<Vaccin> > &vaccineInStoc) const {
    int totalComanda = 0;
    for(int i = 0; i < listaVaccinuriComandate.size(); i++){
        auto it = vaccineInStoc[listaVaccinuriComandate[i]];
        totalComanda += it->getPret() * cantitate[i];
    }
    return totalComanda;
}

bool Comanda::verificaConditiiComanda() {
    int luna = int(data[2]) * 10 + int(data[3]);
    if(luna >= 12 || luna <= 2){
        if(valoareaTotalComanda >= 1000)
            respectaConditiile = true;
    } else if(luna >= 6 && luna <= 8){
        if(valoareaTotalComanda >= 10000)
            respectaConditiile = true;
    }
}

void Vaccin::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0) getline(is, s);
}

class Meniu {
    vector<shared_ptr<Vaccin> > listaVaccinuri;
    vector<Comanda> listaComenzi;
    map<string, int> indexComanda;

public:
    Meniu() { }

    void readString(istream &, string &);

    void startMeniu();

    int alegeOptiune();

    void adaugaVaccin();

    void afiseazaVaccinuri();

    void afiseazaNumeProducatori();

    void adaugaComanda();

    void afiseazaComenzi();

    void afiseazaValoareComanda();

    void afiseazaSchemaVaccinare();
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
    while(optiune < 0 || optiune > 7){
        cout << "0. Exit\n"
             << "1. Adauga un vaccin nou in stoc\n"
             << "2. Afiseaza toate vaccinurile din stoc\n"
             << "3. Afiseaza numele producatorilor pentru fiecare vaccin\n"
             << "4. Adauga o comanda noua\n"
             << "5. Afiseaza toate comenzile\n"
             << "6. Afiseaza valoarea comenzilor dintr-o anumita data\n"
             << "7. Afisarea schemei de vaccinare unui vaccin prezent in stoc\n";
        cout << "Optiunea aleasa:"; cin >> optiune;
        if(optiune < 0 || optiune > 7)
            cout << "Optiune invalida!\n";
    }

    if(optiune == 1)
        adaugaVaccin();
    else if(optiune == 2)
        afiseazaVaccinuri();
    else if(optiune == 3)
        afiseazaNumeProducatori();
    else if(optiune == 4)
        adaugaComanda();
    else if(optiune == 5)
        afiseazaComenzi();
    else if(optiune == 6)
        afiseazaValoareComanda();
    else if(optiune == 7)
        afiseazaSchemaVaccinare();

    return optiune;
}

void Meniu::adaugaVaccin() {
    int tip = 0;
    while (tip < 1 || tip > 4) {
        cout << "1. Vaccin antigripal\n2. Vaccin antihepatita\n3. Anti sars-cov2\n";
        cout << "Tipul ales:";
        cin >> tip;
        if (tip < 0 || tip > 4)
            cout << "Tip invalid!\n";
    }
    shared_ptr<Vaccin> temp;
    if (tip == 1)
        temp = make_shared<AntiGripal>();
    else if (tip == 2)
        temp = make_shared<AntiHepatita>();
    else if (tip ==3)
        temp = make_shared<Sars_Cov2>();

    cin >> *temp;
    listaVaccinuri.push_back(temp);
}

void Meniu::afiseazaVaccinuri(){
    cout << "Lista cu vaccinuri disponibile in stoc:\n";
    int i = 0;
    for(auto it : listaVaccinuri) {
        cout << "Vaccinul cu indexul " << i << " este:\n" << *it << '\n';
        ++i;
    }
};

void Meniu::afiseazaNumeProducatori() {
    cout << "Lista cu numele producatorilor pentru fiecare vaccin:\n";
    int i = 0;
    for(auto it : listaVaccinuri)
        cout << "Numele producatorului pentru vaccinul cu indexul " << i << " este: " << it->getProducator() << '\n';
}

void Meniu::adaugaComanda() {
    Comanda temp;
    afiseazaVaccinuri();
    cin >> temp;

    int totalComanda = temp.totalComanda(listaVaccinuri);
    temp.setValoareaTotalComanda(totalComanda);
    temp.verificaConditiiComanda();
    listaComenzi.push_back(temp);

    if(indexComanda.find(temp.getData()) != indexComanda.end())
        indexComanda[temp.getData()] += totalComanda;
    else indexComanda[temp.getData()] = totalComanda;
}

void Meniu::afiseazaComenzi() {
    cout << "Lista comenzilor:\n";
    int i = 0;
    for(auto it : listaComenzi) {
        cout << "Comanda cu indexul " << i << "este:\n" << it << '\n';
        i++;
    }
}

void Meniu::afiseazaValoareComanda() {
    string data;
    cout << "Data cautata:"; cin >> data;
    try{
        if(indexComanda.find(data) == indexComanda.end())
            throw invalid_argument("Data nu exista!\n");
        cout << "Valoarea comenzilor din acea zi este:" << indexComanda[data] << '\n';
    } catch(invalid_argument){
        cout << "Data nu exista!\n";
    }
}

void Meniu::afiseazaSchemaVaccinare(){
    int idx;
    cout << "Indexul vaccinului prezent in stoc:"; cin >> idx;
    try{
        if(idx < 0 || idx >= listaVaccinuri.size())
            throw out_of_range("Indexul nu exista!\n");

        const AntiGripal *tempAntigripal = dynamic_cast<AntiGripal *>(listaVaccinuri[idx].get());
        if(tempAntigripal != nullptr) {
            tempAntigripal->afisareSchemaVaccinare();
            return;
        }

        const AntiHepatita *tempAntihepatita = dynamic_cast<AntiHepatita *>(listaVaccinuri[idx].get());
        if(tempAntigripal != nullptr) {
            tempAntihepatita->afisareSchemaVaccinare();
            return;
        }

        const Sars_Cov2 *tempSars_Cov2 = dynamic_cast<Sars_Cov2 *>(listaVaccinuri[idx].get());
        if(tempSars_Cov2 != nullptr) {
            tempSars_Cov2->afisareSchemaVaccinare();
            return;
        }
    } catch (out_of_range){
        cout << "Indexul nu exista!\n";
    }
}

class ListaComenzi {
    vector<int> listaVaccinuri;

public:
    ListaComenzi() { }

    ListaComenzi(const vector<int> &listaVaccinuri) : listaVaccinuri(listaVaccinuri) { }

    ListaComenzi operator+(const Comanda &com){
        vector <int> tempNewList;
        vector <int> tempAnotherList = com.getListaVaccinuriComandate();

        for(auto it : listaVaccinuri)
            tempNewList.push_back(it);
        for(auto it : tempAnotherList)
            tempNewList.push_back(it);

        ListaComenzi nouaListaComenzi(tempNewList);

        return nouaListaComenzi;
    }

    void operator=(const ListaComenzi &rhs){
        listaVaccinuri = rhs.listaVaccinuri;
    }

    int operator[](int idx){
        try{
            if(idx < 0 || idx >= listaVaccinuri.size())
                throw out_of_range("Out of range!\n");
            return listaVaccinuri[idx];
        } catch (out_of_range) {
            cout << "Out of range!\n";
        }
    }

};

int main() {

    Comanda com1("20-12-2020", "SpitalX", {1}, 20);
    ListaComenzi lista;
    lista=lista+com1;
    cout<< "Element: " << lista[0] << '\n';


    Meniu meniu;
    meniu.startMeniu();

    return 0;
}
