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
        is >> *temp;
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

class Jucarie : public IOBase{
protected:
    string nume;
    int dimensiune;
    string tip;

public:
    Jucarie() { }

    Jucarie(const string &nume, int dimensiune, const string &tip) : nume(nume), dimensiune(dimensiune), tip(tip) {}

    virtual ~Jucarie() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "nume:"; is >> nume;
        cout << "dimensiune:"; is >> dimensiune;
        cout << "tip:"; is >> tip;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "nume:" << nume << '\n';
        os << "dimensiune:" << dimensiune << '\n';
        os << "tip:" << tip << '\n';

        return os;
    }
};

class Clasice : public Jucarie {
protected:
    string material, culoare;

public:
    Clasice() { }

    Clasice(const string &nume, int dimensiune, const string &tip, const string &material, const string &culoare)
            : Jucarie(nume, dimensiune, tip), material(material), culoare(culoare) { }

    virtual ~Clasice() {

    }

    istream &read(istream &is) override {
        Jucarie::read(is);
        cout << "material:"; is >> material;
        cout << "culoare:"; is >> culoare;

        return is;
    }

    ostream &write(ostream &os) const override {
        Jucarie::write(os);
        os << "material:" << material << '\n';
        os << "culoare:" << culoare << '\n';

        return os;
    }
};

class Educative: public virtual Jucarie{
protected:
    string abilitate;

public:
    Educative() {}

    Educative(const string &nume, int dimensiune, const string &tip, const string &abilitate) : Jucarie(nume,
                                                                                                        dimensiune,
                                                                                                        tip),
                                                                                                abilitate(abilitate) { }

    virtual ~Educative() {

    }

    istream &read(istream &is) override {
        Jucarie::read(is);
        cout << "abilitate:"; is >> abilitate;

        return is;
    }

    ostream &write(ostream &os) const override {
        Jucarie::write(os);
        os << "abilitate:" << abilitate << '\n';

        return os;
    }
};

class Electronice : public virtual Jucarie {
protected:
    int nrBaterii;

public:

    virtual ~Electronice() {

    }

    Electronice() { }

    Electronice(const string &nume, int dimensiune, const string &tip, int nrBaterii) : Jucarie(nume, dimensiune, tip),
                                                                                        nrBaterii(nrBaterii) { }

    istream &read(istream &is) override {
        Jucarie::read(is);
        cout << "Numarul de baterii:"; is >> nrBaterii;

        return is;
    }

    ostream &write(ostream &os) const override {
        Jucarie::write(os);
        os << "Numarul de baterii:" << nrBaterii << '\n';

        return os;
    }
};

class Moderne : public Educative, public Electronice{
    string brand, model;

public:
    Moderne(const string &nume, int dimensiune, const string &tip, const string &abilitate, const string &nume1,
            int dimensiune1, const string &tip1, int nrBaterii, const string &brand, const string &model) : Educative(
            nume, dimensiune, tip, abilitate), Electronice(nume1, dimensiune1, tip1, nrBaterii), brand(brand),
                                                                                                            model(model) { }

    Moderne() { }

    virtual ~Moderne() {

    }

    istream &read(istream &is) override {
        Jucarie::read(is);
        cout << "brand:"; is >> brand;
        cout << "model:"; is >> model;
        abilitate = "generala";
        nrBaterii = 1;

        return is;
    }

    ostream &write(ostream &os) const override {
        Jucarie::write(os);
        os << "brand:" << brand << '\n';
        os << "model:" << model << '\n';
        os << "abilitate:" << abilitate << '\n';
        os << "numarul de baterii:" << nrBaterii << '\n';


        return os;
    }
};

class Copii : public  IOBase {
    static int currentID;

protected:
    int ID;
    string nume, prenume, adresa;
    int varsta, nrFapteBune, nrJucariiPrimite;

    vector<shared_ptr<Jucarie>> listaDeJucarii;

public:
    Copii() { }

    Copii(const string &nume, const string &prenume, const string &adresa, int varsta, int nrFapteBune,
          int nrJucariiPrimite) : nume(nume), prenume(prenume), adresa(adresa), varsta(varsta),
                                  nrFapteBune(nrFapteBune), nrJucariiPrimite(nrJucariiPrimite) { ID = currentID; currentID++; }

    virtual ~Copii() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        ID = currentID; currentID++;
        cout << "nume:"; is >> nume;
        cout << "prenume:"; is >> prenume;
        cout << "adresa:"; is >> adresa;
        cout << "varsta:"; is >> varsta;
        cout << "nrFapteBune:"; is >> nrFapteBune;
        nrJucariiPrimite = nrFapteBune;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "ID:" << ID << '\n';
        os << "nume:" << nume << '\n';
        os << "prenume:" << prenume << '\n';
        os << "adresa:" << adresa << '\n';
        os << "varsta:" << varsta << '\n';
        os << "nrFapteBune:" << nrFapteBune << '\n';
        os << "nrJucariiPrimite:" << nrJucariiPrimite << '\n';

        return os;
    }

    int getTipulDeJucarieCuIndexul(int i){
        try{
            if(i >= listaDeJucarii.size() || i < 0)
                throw out_of_range("Indexul nu exista!");
        } catch(out_of_range) {
            cout << "Indexul cautat nu exista!";

            return -1;
        }

        Clasice *jucarieClasica = dynamic_cast<Clasice*>(listaDeJucarii[i].get());
        if(jucarieClasica != nullptr)
            return 0;

        Educative *jucarieEducativa = dynamic_cast<Educative*>(listaDeJucarii[i].get());
        if(jucarieEducativa != nullptr)
            return 1;

        Electronice *jucarieElectronica = dynamic_cast<Electronice*>(listaDeJucarii[i].get());
        if(jucarieElectronica != nullptr)
            return 2;

        Moderne *jucarieModerna = dynamic_cast<Moderne*>(listaDeJucarii[i].get());
        if(jucarieModerna != nullptr)
            return 3;
    }

    int getNrFapteBune() const;

    int getNrJucariiPrimite() const;

    static int getCurrentId();

    static void incCurrentId();

    const vector<shared_ptr<Jucarie>> &getListaDeJucarii() const;

    void setListaDeJucarii(const vector<shared_ptr<Jucarie>> &listaDeJucarii);

    void adaugaJucarieNoua(const shared_ptr<Jucarie> jucarieNoua){
        listaDeJucarii.push_back(jucarieNoua);
    }

    void printListaDeJucarii();

    const string &getNume() const {
        return nume;
    }

    const string &getPrenume() const;

    int getVarsta() const {
        return varsta;
    }

    void incNrFapteBune(int x){
        nrFapteBune += x;
    }
};

int Copii::currentID = 1;

int Copii::getCurrentId() {
    return currentID;
}

void Copii::incCurrentId() {
    currentID++;
}

const vector<shared_ptr<Jucarie>> &Copii::getListaDeJucarii() const {
    return listaDeJucarii;
}

void Copii::setListaDeJucarii(const vector<shared_ptr<Jucarie>> &listaDeJucarii) {
    Copii::listaDeJucarii = listaDeJucarii;
}

void Copii::printListaDeJucarii() {
    cout << listaDeJucarii;
}

int Copii::getNrFapteBune() const {
    return nrFapteBune;
}

int Copii::getNrJucariiPrimite() const {
    return nrJucariiPrimite;
}

const string &Copii::getPrenume() const {
    return prenume;
}

class CopilCuminte : public Copii {
protected:
    int nrDulciuri;

public:
    CopilCuminte() { }

    CopilCuminte(const string &nume, const string &prenume, const string &adresa, int varsta, int nrFapteBune,
                 int nrJucariiPrimite, int nrDulciuri) : Copii(nume, prenume, adresa, varsta, nrFapteBune,
                                                               nrJucariiPrimite), nrDulciuri(nrDulciuri) {}

    virtual ~CopilCuminte() {

    }

    istream &read(istream &is) override {
        Copii::read(is);
        if(nrFapteBune < 10)
            cout << "Numarul de fapte bune trebuie sa fie mai mare sau egal cu 10.\n";
        while(nrFapteBune < 10){
            cout << "nrFapteBune:"; is >> nrFapteBune;
            if(nrFapteBune < 10)
                cout << "Numarul de fapte bune trebuie sa fie mai mare sau egal cu 10.\n";
        }
        nrJucariiPrimite = nrFapteBune;
        cout << "nrDulciuri:"; is >> nrDulciuri;

        return is;
    }

    ostream &write(ostream &os) const override {
        Copii::write(os);
        os << "nrDulciuri:" << nrDulciuri << '\n';

        return os;
    }
};

class CopilObraznic : public Copii{
protected:
    int nrCarbuni;

public:
    CopilObraznic() { }

    CopilObraznic(const string &nume, const string &prenume, const string &adresa, int varsta, int nrFapteBune,
                 int nrJucariiPrimite, int nrDulciuri) : Copii(nume, prenume, adresa, varsta, nrFapteBune,
                                                               nrJucariiPrimite), nrCarbuni(nrCarbuni) {}

    virtual ~CopilObraznic() {

    }

    istream &read(istream &is) override {
        Copii::read(is);
        cout << "nrCarbuni:"; is >> nrCarbuni;

        return is;
    }

    ostream &write(ostream &os) const override {
        Copii::write(os);
        os << "nrCarbuni:" << nrCarbuni << '\n';

        return os;
    }
};

int main() {

    vector<shared_ptr<Copii>> listaDeCopii;

    int optiune = -1;
    while(optiune != 0){
        while(optiune < 0 || optiune > 7) {
            cout << "0: Exit.\n"
                 << "1: Citirea si afisarea a n copii.\n"
                 << "2. Citirea si afisarea a m jucarii pentru fiecare copil.\n"
                 << "3. Gasirea unui copil dupa nume.\n"
                 << "4. Ordonarea copiilor dupa varsta.\n"
                 << "5. Ordonarea copiilor dupa numarul de fapte bune.\n"
                 << "6. Gasirea unui copil dupa ID.\n"
                 << "7. Afisarea raportului pentru toate jucariile.\n";
            cout << "Optiunea aleasa:";
            cin >> optiune;

            if(optiune < 0 || optiune > 7)
                cout << "Nu a fost introdusa o optiune valida!";
        }

        if(optiune == 1){
            listaDeCopii.clear();
            int n;
            cout << "Numarul de copii:"; cin >> n;
            for(int i = 0; i < n; i++){
                int tip = 0;
                while(tip < 1 || tip > 2) {
                    cout << "1. Copil cuminte\n2.Copil obraznic\nTipul de copil:";
                    cin >> tip;
                    if(tip < 1 || tip > 2)
                        cout << "Tipul introdus nu este valid!\n";
                }

                shared_ptr<Copii> temp;
                if(tip == 1){
                    temp = make_shared<CopilCuminte>();
                    cin >> *temp;
                    listaDeCopii.push_back(temp);
                } else if(tip == 2){
                    temp = make_shared<CopilObraznic>();
                    cin >> *temp;
                    listaDeCopii.push_back(temp);
                }
            }

            cout << listaDeCopii;
        } else if(optiune == 2){
            for(int i = 0; i < listaDeCopii.size(); i++){
                for(int j = 0; j < listaDeCopii[i]->getNrJucariiPrimite(); j++) {
                    int tip = 0;
                    while (tip < 1 || tip > 4) {
                        cout << "1. Clasice\n2.Educativa\n3.Electronica\n4.Moderna\nTipul de jucarie:";
                        cin >> tip;
                        if (tip < 1 || tip > 4)
                            cout << "Tipul introdus nu este valid!\n";
                    }

                    shared_ptr<Jucarie> temp;
                    if (tip == 1) {
                        temp = make_shared<Clasice>();
                    } else if (tip == 2) {
                        temp = make_shared<Educative>();
                    } else if (tip == 3) {
                        temp = make_shared<Electronice>();
                    } else if (tip == 4) {
                        temp = make_shared<Moderne>();
                    }

                    cin >> *temp;
                    listaDeCopii[i]->adaugaJucarieNoua(temp);
                }
            }

            for(int i = 0; i < listaDeCopii.size(); i++){
                listaDeCopii[i]->printListaDeJucarii();
            }
        } else if(optiune == 3){
            string numeCautat;
            cout << "Numele cautat:"; cin >> numeCautat;
            for(int i = 0; i < listaDeCopii.size(); i++){
                string numeComplet = listaDeCopii[i]->getNume() + " " + listaDeCopii[i]->getPrenume();

                bool wasFound = false;
                int idx = 0;
                for(int i = 0; i < numeComplet.size(); i++){
                    if(numeComplet[i] == numeCautat[idx]){
                        idx++;
                        if(idx >= numeCautat.size())
                            wasFound = true;
                    } else idx = 0;
                }

                if(wasFound)
                    cout << "A fost gasit: " << numeComplet << '\n';
            }
        } else if(optiune == 4){
            vector<pair <int, int> > listaDupaVarsta;

            for(int i = 0; i < listaDeCopii.size(); i++){
                pair <int, int> temp = {listaDeCopii[i]->getVarsta(), i};
                listaDupaVarsta.push_back(temp);
            }

            sort(listaDupaVarsta.begin(), listaDupaVarsta.end());

            for(int i = 0; i < listaDeCopii.size(); i++){
                cout << *listaDeCopii[listaDupaVarsta[i].second];
            }
        } else if(optiune == 5){
            vector<pair <int, int> > listaDupaFapteBune;

            for(int i = 0; i < listaDeCopii.size(); i++){
                pair <int, int> temp = {listaDeCopii[i]->getNrFapteBune(), i};
                listaDupaFapteBune.push_back(temp);
            }

            sort(listaDupaFapteBune.begin(), listaDupaFapteBune.end());

            for(int i = 0; i < listaDeCopii.size(); i++){
                cout << *listaDeCopii[listaDupaFapteBune[i].second];
            }
        } else if(optiune == 6){
            int ID;
            cout << "ID cautat:"; cin >> ID;
            try{
                if(ID > listaDeCopii.size() || ID < 0)
                    throw out_of_range("ID-ul nu exista!\n");
                ID--;
                int X;
                cout << "Creste numarul de fapte bune cu:"; cin >> X;
                listaDeCopii[ID]->incNrFapteBune(X);
            } catch(out_of_range) {
                cout << "ID-UL cautat nu exista!\n";
            }
        } else if(optiune == 7){
            int tipuri[4] = {0, 0, 0, 0};
            for(int i = 0; i < listaDeCopii.size(); i++){
                for(int j = 0; j < listaDeCopii[i]->getNrJucariiPrimite(); j++){
                    tipuri[listaDeCopii[i]->getTipulDeJucarieCuIndexul(j)]++;
                }
            }

            cout << "Numarul total de jucarii este " << tipuri[0] + tipuri[1] + tipuri[2] + tipuri[3]
                 << "din care " << tipuri[0] << " sunt jucarii clasice, "
                 << tipuri[1] << " sunt jucarii educative, "
                 << tipuri[2] << " sunt jucarii electronice si "
                 << tipuri[3] << " sunt jucarii moderne.\n";
        }

        optiune = -1;
    }

    return 0;
}
