#include <bits/stdc++.h>

/*
 * Cristea Petru-Theodor
 */

using namespace std;
const int TotalBacterii = 1e9;
const int TotalFungi = 15 * 1e5;
const int TotalVirusi = 1e8;

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

class Masca : public IOBase{
protected:
    string culoare;
    int nrPliuri;

public:
    Masca() { }

    Masca(const string &culoare, int nrPliuri) : culoare(culoare), nrPliuri(nrPliuri) { }

    virtual ~Masca() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Culoare:"; is.get(); getline(is, culoare);
        cout << "Numarul de pliuri:"; is >> nrPliuri;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Culoare:" << culoare << '\n';
        os << "Numarul de pliuri:" << nrPliuri << '\n';

        return os;
    }

    virtual void getType(){
        cout << "Masca";
    }
};

class MascaChirugicala : public Masca {
protected:
    bool model;
    string tipProtectie;

public:
    MascaChirugicala(const MascaChirugicala &rhs) {
        tipProtectie = rhs.tipProtectie;
        culoare = rhs.culoare;
        nrPliuri = rhs.nrPliuri;
    }

    MascaChirugicala() { }

    MascaChirugicala(const string &culoare, const string &tipProtectie, int nrPliuri) : Masca(culoare, nrPliuri),
                                                                                        tipProtectie(tipProtectie) { }

    virtual ~MascaChirugicala() {

    }

    istream &read(istream &is) override {
        Masca::read(is);
        cout << "Tipul de protectie:"; is.get();
        getline(is, tipProtectie);
        cout << "Imprimare model(0 = Nu ; 1 = Da)"; is >> model;

        return is;
    }

    ostream &write(ostream &os) const override {
        Masca::write(os);
        os << "Tipul de protectie:" << tipProtectie << '\n';

        return os;
    }

    const string &getTipProtectie() const {
        return tipProtectie;
    }

    void getType() override {
        cout << "Chirurgicala";
    }

    bool isModel() const {
        return model;
    }
};

class MascaPolicarbonat : public Masca {
protected:
    string tipPrindere, tipProtectie;

public:
    MascaPolicarbonat() { }

    MascaPolicarbonat(const string &tipPrindere) : tipPrindere(tipPrindere) { }

    MascaPolicarbonat(const string &culoare, const string &tipPrindere, int nrPliuri) : Masca(culoare, nrPliuri),
                                                                                        tipPrindere(tipPrindere) { tipProtectie = "ffp 0"; }

    virtual ~MascaPolicarbonat() {

    }

    istream &read(istream &is) override {
        Masca::read(is);
        cout << "Tipul de prindere:"; is >> tipPrindere;
        tipProtectie = "ffp 0";

        return is;
    }

    ostream &write(ostream &os) const override {
        Masca::write(os);
        os << "Tipul de prindere:" << tipPrindere << '\n';
        os << "Tipul de protectie:" << tipProtectie << '\n';

        return os;
    }

    void getType() override {
        cout << "Policarbonat";
    }
};

class Dezinfectant : public  IOBase {
protected:
    int nrSpeciiUcise;
    double eficientaVal;
    vector<string> ingredinte, tipSuprafataAplicabila;

public:
    Dezinfectant() { }

    Dezinfectant(int nrSpeciiUcise, const vector<string> &ingredinte, const vector<string> &tipSuprafataAplicabila)
            : nrSpeciiUcise(nrSpeciiUcise), ingredinte(ingredinte), tipSuprafataAplicabila(tipSuprafataAplicabila) { }

    virtual ~Dezinfectant() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Numarul de specii ucise:"; is >> nrSpeciiUcise;
        cout << "Ingrediente:\n"; is >> ingredinte;
        cout << "Tipurile de suprafata aplicabila:\n"; is >> tipSuprafataAplicabila;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Numarul de specii ucise:" << nrSpeciiUcise << '\n';
        os << "Ingrediente:\n" << ingredinte << '\n';
        os << "Tipurile de suprafata aplicabila:\n" << tipSuprafataAplicabila << '\n';

        return os;
    }

    virtual void calculeazaEficienta() {
        return;
    }

    double eficienta() const {
        return eficientaVal;
    }
};

class DezinfectantBacterii : public Dezinfectant {
public:
    DezinfectantBacterii() { }

    DezinfectantBacterii(int nrSpeciiUcise, const vector<string> &ingredinte,
                         const vector<string> &tipSuprafataAplicabila) : Dezinfectant(nrSpeciiUcise, ingredinte,
                                                                                     tipSuprafataAplicabila) { calculeazaEficienta(); }

    virtual ~DezinfectantBacterii() {

    }

    istream &read(istream &is) override {
        Dezinfectant::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        Dezinfectant::write(os);

        return os;
    }

    void calculeazaEficienta() override {
        eficientaVal = (double) nrSpeciiUcise / TotalBacterii * 100;
    }
};

class DezinfectantFungi : public Dezinfectant {
public:
    DezinfectantFungi() { }

    DezinfectantFungi(int nrSpeciiUcise, const vector<string> &ingredinte,
                         const vector<string> &tipSuprafataAplicabila) : Dezinfectant(nrSpeciiUcise, ingredinte,
                                                                                     tipSuprafataAplicabila) { calculeazaEficienta(); }

    virtual ~DezinfectantFungi() {

    }

    istream &read(istream &is) override {
        Dezinfectant::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        Dezinfectant::write(os);

        return os;
    }

    void calculeazaEficienta() override {
        eficientaVal = (double) nrSpeciiUcise / TotalFungi * 100;
    }
};

class DezinfectantVirusuri : public Dezinfectant {
public:
    DezinfectantVirusuri() { }

    DezinfectantVirusuri(int nrSpeciiUcise, const vector<string> &ingredinte,
                         const vector<string> &tipSuprafataAplicabila) : Dezinfectant(nrSpeciiUcise, ingredinte,
                                                                                     tipSuprafataAplicabila) { calculeazaEficienta(); }

    virtual ~DezinfectantVirusuri() {

    }

    istream &read(istream &is) override {
        Dezinfectant::read(is);

        return is;
    }

    ostream &write(ostream &os) const override {
        Dezinfectant::write(os);

        return os;
    }

    void calculeazaEficienta() override {
        eficientaVal = (double) nrSpeciiUcise / TotalVirusi * 100;
    }
};

class Achizitie : public IOBase{
    double totalComanda;
    int zi, luna, an;
    string numeVal;

    vector<shared_ptr<Masca> > listaDeMasti;
    vector<shared_ptr<Dezinfectant> > listaDeDezinfectanti;

public:
    Achizitie() { }

    Achizitie(int zi, int luna, int an, const string &nume) : zi(zi), luna(luna), an(an), numeVal(nume) { }

    virtual ~Achizitie() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Zi:"; is >> zi;
        cout << "Luna:"; is >> luna;
        cout << "An:"; is >> an;
        cout << "Nume:"; is.get();
        getline(is, numeVal);

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Zi:" << zi << '\n';
        os << "Luna:" << luna << '\n';
        os << "An:" << an << '\n';
        os << "Nume:" << numeVal << '\n';

        return os;
    }

    const string &nume() const {
        return numeVal;
    }

    void operator+=(Masca &rhs) {
        Masca *temp = &rhs;
        MascaPolicarbonat *tempMP = dynamic_cast<MascaPolicarbonat*>(temp);

        if(tempMP != nullptr){
            totalComanda += 20;

            shared_ptr<Masca> valueTemp = make_shared<MascaPolicarbonat>(*tempMP);
            listaDeMasti.push_back(valueTemp);
            return;
        }

        MascaChirugicala *tempMC = dynamic_cast<MascaChirugicala*>(temp);
        shared_ptr<Masca> valueTemp = make_shared<MascaChirugicala>(*tempMC);
        listaDeMasti.push_back(valueTemp);
        string tipProtectie = tempMC->getTipProtectie();

        double multiplier = 1;
        if(tempMC->isModel())
            multiplier = 1.5;

        if(tipProtectie == "ffp1")
            totalComanda += 5 * multiplier;
        else if(tipProtectie == "ffp2")
            totalComanda += 10 * multiplier;
        else if(tipProtectie == "ffp3")
            totalComanda += 15 * multiplier;
    }

    void operator+=(const Dezinfectant &rhs) {
        listaDeDezinfectanti.push_back(make_shared<Dezinfectant>(rhs));

        double eficientaVal = listaDeDezinfectanti[ listaDeDezinfectanti.size() - 1]->eficienta();

        if(eficientaVal < 90)
            totalComanda += 10;
        else if(eficientaVal < 95)
            totalComanda += 20;
        else if(eficientaVal < 97.5)
            totalComanda += 30;
        else if(eficientaVal < 99)
            totalComanda += 40;
        else totalComanda += 50;
    }

    bool operator<(const Achizitie &rhs) const {
        if (totalComanda < rhs.totalComanda)
            return true;
        if (rhs.totalComanda < totalComanda)
            return false;
        return totalComanda < rhs.totalComanda;
    }

    bool operator>(const Achizitie &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Achizitie &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Achizitie &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const Achizitie &rhs) const {
        return totalComanda == rhs.totalComanda;
    }

    bool operator!=(const Achizitie &rhs) const {
        return !(rhs == *this);
    }
};

class Afacere{
protected:
    vector<shared_ptr<Masca> > listaDeMasti;
    vector<shared_ptr<Dezinfectant> > listaDeDezinfectante;
    vector<shared_ptr<Achizitie> > listaDeAchizitii;

public:
    void adaugaMasca(const shared_ptr<Masca> rhs){
        listaDeMasti.push_back(rhs);
    }

    void adaugaDezinfectant(const shared_ptr<Dezinfectant> rhs){
        listaDeDezinfectante.push_back(rhs);
    }

    void adaugaAchizitie(const shared_ptr<Achizitie> rhs){
        listaDeAchizitii.push_back(rhs);
    }
};

int main() {

    MascaChirugicala mc1, mc2("ffp2", "verde brotăcel", 55), mc3(mc1), mc4, mc5;
    mc4 = mc2;
    std::cout << mc1 << mc2;
    MascaPolicarbonat* mp1=new MascaPolicarbonat(), * mp2=new MascaPolicarbonat();

    MascaPolicarbonat* mp3 = new MascaPolicarbonat("elastic");
    std::cin >> *mp1;
    std::cout << *mp3;


    Dezinfectant* d1 = new DezinfectantBacterii(100000000, std::vector<string>({"sulfati non-ionici", "sulfati cationici", "parfumuri", "Linalool", "Metilpropanol butilpentil"}),
                                                std::vector<string>({"lemn, sticla, metal, ceramica, marmura"}));
    Dezinfectant* d2 = new DezinfectantVirusuri(50000000, std::vector<string>({"Alkil Dimetilm Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}),
                                                std::vector<string>({"lemn, sticla, ceramica, marmura"}));
    Dezinfectant* d3 = new DezinfectantFungi(1400000, std::vector<string>({"Alkil Etil Benzil Crlorura de amoniu", "parfumuri", "Butilpentil metilpropinal"}),
                                             std::vector<string>({"sticla, plastic"}));
    std::cout << d1->eficienta() << " " << d2->eficienta() << " " << d3->eficienta() << "\n";


    Achizitie* a1 = new Achizitie(26, 5, 2020, "PlushBio SRL");
    *a1 += *mp1; //se adauga masca de policarbonat mp1 in lista de masti achizitionate
    *a1 += *(&mc1); //se adauga masca chirugicala mc1 in lista
    *a1 += *d3; // se adauga dezinfectantu de fungi d3 in lista de dezinfectanti achizitionati
    Achizitie* a2 = new Achizitie(25, 5, 2020, "Gucci");
    *a2 += *d1;
    *a2 += *d2;
    *a2 += *d2;

    Achizitie a3, a4(*a1);
    a3 = *a2;
    if(*a1 < *a2) {
        std::cout << a1->nume() << " are valoarea facturii mai mica.\n";
    }else if (*a1 == *a2) {
        std::cout << a1->nume() << " si " << a2->nume() << " au aceasi valoare a facturii.\n";
    } else {
        std::cout << a2->nume() << " are valoarea facturii mai mica.\n";
    }

    Afacere afacere;
    int optiune = -1;
    while(optiune != 0){
        optiune = -1;
        cout << "Optiunea aleasa:"; cin >> optiune;

        if(optiune == 1){
            int tip;
            cout << "Tipul aleasa:"; cin >> tip;

            shared_ptr<Masca> temp;
            if(tip == 1){
                temp = make_shared<MascaChirugicala>();
            } else {
                temp = make_shared<MascaPolicarbonat>();
            }

            cin >> *temp;
            afacere.adaugaMasca(temp);
        } else if(optiune == 2){
            int tip;
            cout << "Tipul aleasa:"; cin >> tip;

            shared_ptr<Dezinfectant> temp;
            if(tip == 1){
                temp = make_shared<DezinfectantBacterii>();
            } else if(tip == 2) {
                temp = make_shared<DezinfectantFungi>();
            } else {
                temp = make_shared<DezinfectantVirusuri>();
            }

            cin >> *temp;
            afacere.adaugaDezinfectant(temp);
        } else if(optiune == 3){
            shared_ptr<Achizitie> temp;

            cin >> *temp;
            afacere.adaugaAchizitie(temp);
        }
    }

    return 0;
}
