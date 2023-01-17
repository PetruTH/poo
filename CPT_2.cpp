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

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &v){
    os << "Numarul de elemente = " << v.size() << '\n';
    for(int i = 0; i < v.size(); i++)
        os << "Elementul " << i << ":\n" << *v[i] << '\n';

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

class Curs : public IOBase {
protected:
    static int currentID;
    string ID;
    int pret;
    string denumire;
    int an, luna, zi;

public:
    Curs() { }

    Curs(string denumire, int pret, int an, int luna, int zi) : denumire(denumire), pret(pret), an(an), luna(luna), zi(zi) { }

    virtual ~Curs(){

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Denumire:"; is >> denumire;
        cout << "Pret:"; is >> pret;
        cout << "Durata cursului\nAni:"; is >> an;
        cout << "Luni:"; is >> luna;
        cout << "Zile:"; is >> zi;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Denumire:" << denumire << '\n';
        os << "Pret:" << pret << '\n';
        os << "Durata\nAni:" << an << "\nLuni:" << luna << "\nZile:" << zi << '\n';

        return os;
    }

    int getAn(){
        return an;
    }

    int getLuna(){
        return luna;
    }

    int getZi(){
        return zi;
    }

    int getPret(){
        return pret;
    }
};

int Curs::currentID = 1;

class CursCalificare : public Curs {
public:
    CursCalificare() { }

    CursCalificare(const Curs &curs) : Curs(curs) { }

    istream &read(istream &is) override {
        Curs::read(is);
        ID = "C_" + to_string(currentID);
        currentID++;

        return is;
    }

    ostream &write(ostream &os) const override {
        os << "ID:" << ID << '\n';
        Curs::write(os);

        return os;
    }
};

class CursInitiere : public Curs {
public:
    CursInitiere() { }

    CursInitiere(const Curs &curs) : Curs(curs) { }

    istream &read(istream &is) override {
        Curs::read(is);
        ID = "I_" + to_string(currentID);
        currentID++;

        return is;
    }

    ostream &write(ostream &os) const override {
        os << "ID:" << ID << '\n';
        Curs::write(os);

        return os;
    }
};

class CursPerfectionare : public Curs {
public:
    CursPerfectionare() { }

    CursPerfectionare(const Curs &curs) : Curs(curs) { }

    istream &read(istream &is) override {
        Curs::read(is);
        ID = "P_" + to_string(currentID);
        currentID++;

        return is;
    }

    ostream &write(ostream &os) const override {
        os << "ID:" << ID << '\n';
        Curs::write(os);

        return os;
    }
};

class Participant : public IOBase {
protected:
    vector<shared_ptr<Curs> > cursuriUrmate;
    string nume;

public:
    Participant() { }

    Participant(string nume) : nume(nume) { }

    virtual ~Participant() {

    }

    istream &read(istream &is) override {
        IOBase::read(is);
        cout << "Nume:"; is >> nume;

        return is;
    }

    ostream &write(ostream &os) const override {
        IOBase::write(os);
        os << "Nume:" << nume << '\n';

        return os;
    }

    shared_ptr<Curs> & operator [] (int idx) {
        try{
            if(idx < 0 || idx >= cursuriUrmate.size())
                throw out_of_range("Index invalid!\n");
            return cursuriUrmate[idx];
        } catch (out_of_range) {
            cout << "Index invalid!\n";
        }
    }

    void adaugaCursNou(shared_ptr<Curs> c){
        cursuriUrmate.push_back(c);
    }

    int getSizeOfList(){
        return cursuriUrmate.size();
    }

    bool checkDurata(int idx);

    void printCursuriUrmate();

    virtual int getCursInitiereProfit(int val){
        return 0;
    }

    virtual int getCursCalificareProfit(int val){
        return 0;
    }

    virtual int getCursPerfectionareProfit(int val){
        return 0;
    }

    virtual int getVechime(){
        return 0;
    }
};

bool Participant::checkDurata(int idx) {
    int an = 1;
}

void Participant::printCursuriUrmate() {
    cout << cursuriUrmate;
}

class Student : public Participant {
    string universitate;
    int anulStudii;

public:
    Student() { }

    Student(const string &u, const int &a) : universitate(u), anulStudii(a) { }

    virtual ~Student() {

    }

    istream &read(istream &is) override {
        Participant::read(is);
        cout << "Universitate:"; is >> universitate;
        cout << "Anul de studii:"; is >> anulStudii;

        return is;
    }

    ostream &write(ostream &os) const override {
        Participant::write(os);
        os << "Universitate:" << universitate << '\n';
        os << "Anul de studii:" << anulStudii << '\n';

        return os;
    }

    int getAnulStudii(){
        return anulStudii;
    }

    int getCursInitiereProfit(int val) override {
        return val * 0.5;
    }

    int getCursCalificareProfit(int val) override {
        return val * 0.5;
    }

    int getCursPerfectionareProfit(int val) override {
        return 0;
    }

    int getVechime() override {
        return 0;
    }
};

class Angajat : public Participant {
    bool contract;
    int vechime;

public:
    Angajat() { }

    Angajat(const bool &b, const int &v) : contract(b), vechime(v) { }

    virtual ~Angajat() {

    }

    istream &read(istream &is) override {
        Participant::read(is);
        cout << "Contractul este pe perioada determinata? (0. Nu 1. Da):"; is >> contract;
        cout << "Vechime:"; is >> vechime;

        return is;
    }

    ostream &write(ostream &os) const override {
        Participant::write(os);
        os << "Contractul este pe perioada determinata? (0. Nu 1. Da):" << contract << '\n';
        os << "Vechime:" << vechime << '\n';

        return os;
    }

    int getVechime() override {
        return vechime;
    }

    bool getContract() const {
        return contract;
    }

    int getCursInitiereProfit(int val) override {
        return val;
    }

    int getCursCalificareProfit(int val) override {
        return val;
    }

    int getCursPerfectionareProfit(int val) override {
        return val;
    }
};

class Somer : public Participant {
    string ultimulLocDeMunca;
    int vechime;

public:
    Somer() { };

    Somer(const string &u, const int &v) : ultimulLocDeMunca(u), vechime(v) { }

    virtual ~Somer() {

    }

    istream &read(istream &is) override {
        Participant::read(is);
        cout << "Ultimul loc de munca:"; is >> ultimulLocDeMunca;
        cout << "Vechime:"; is >> vechime;

        return is;
    }

    ostream &write(ostream &os) const override {
        Participant::write(os);
        os << "Ultimul loc de munca:" << ultimulLocDeMunca << '\n';
        os << "Vechime:" << vechime << '\n';

        return os;
    }

    int getVechime() override {
        return vechime;
    }

    int getCursInitiereProfit(int val) override {
        return 0;
    }

    int getCursCalificareProfit(int val) override {
        return val * 0.5;
    }

    int getCursPerfectionareProfit(int val) override {
        return val * 0.5;
    }
};

class BaseMenu {
public:
    virtual void listOptions(int optiune) = 0;

    virtual int chooseOption(int first, int last) const = 0;

    virtual void mainLoop() = 0;
};

class Menu : public BaseMenu {
    vector<shared_ptr <Participant> > listaParticipanti;

public:
    void readString(istream &, string &);

    void listOptions(int optiune) override;

    int chooseOption(int first, int last) const override;

    void mainLoop() override;

    void readParticipants();

    void printParticipants();

    void maximDouaLuni();

    void grupareCursuri();

    template <typename T>
    void cautaDupaClasa();

    void calculeazaProfit();
};

void Menu::readString(istream &is, string &s){
    getline(is, s);
    if(s.size() == 0)
        getline(is, s);
}

void Menu::readParticipants() {
    int n;
    cout << "Numarul de participanti:"; cin >> n;
    for(int i = 0; i < n; i++){
        cout << "Alege tipul participantului:\n1. Student\n2. Angajat\n3. Somer\n";
        int optiune = chooseOption(1, 3);

        shared_ptr<Participant> tempParticipant;
        if(optiune == 1)
            tempParticipant = make_shared<Student>();
        else if(optiune == 2)
            tempParticipant = make_shared<Angajat>();
        else if(optiune == 3)
            tempParticipant = make_shared<Somer>();

        cin >> *tempParticipant;

        int m;
        cout << "Numarul de cursuri pe care acesta le-a urmat:"; cin >> m;
        for(int j = 0; j < m; j++){
            cout << "Alege tipul de curs pe care participantul l-a urmat:\n1. Initiere\n2. Calificare\n3. Perfectionare\n";
            int tip = chooseOption(1, 3);

            shared_ptr<Curs> tempCurs;
            if(tip == 1)
                tempCurs = make_shared<CursInitiere>();
            else if(tip == 2)
                tempCurs = make_shared<CursCalificare>();
            else if(tip == 3) {
                tempCurs = make_shared<CursPerfectionare>();

                try {
                    if(tempParticipant->getVechime() < 3)
                        throw invalid_argument("Acest participant nu poate urma acest curs!\n");
                } catch (invalid_argument) {
                    cout << "Acest participant nu poate urma acest curs!\n";
                    j--;
                    continue;
                }
            }

            cin >> *tempCurs;
            tempParticipant->adaugaCursNou(tempCurs);
        }
        listaParticipanti.push_back(tempParticipant);
    }
}


void Menu::printParticipants() {
    for(int i = 0; i < listaParticipanti.size(); i++){
        cout << "Participantul cu numarul " << i << " este:\n" << *listaParticipanti[i];
        cout << "Participantul a urmat cursurile:\n";
        listaParticipanti[i]->printCursuriUrmate();
    }
}

void Menu::maximDouaLuni() {
    for(int i = 0; i < listaParticipanti.size(); i++){
        Student *tempStudent = dynamic_cast<Student *>(listaParticipanti[i].get());
        if (tempStudent == nullptr)
            continue;
        if(tempStudent->getAnulStudii() < 2 || tempStudent->getAnulStudii() > 3)
            continue;

        int n = tempStudent->getSizeOfList();
        for(int j = 0; j < n; j++){
            int an = tempStudent->operator[](j)->getAn();
            int luna = tempStudent->operator[](j)->getLuna();
            int zi = tempStudent->operator[](j)->getZi();

            if(an > 0 || luna > 3)
                continue;
            if(luna >= 2 && zi > 0)
                continue;

            cout << "A fost gasit cursul:\n" << *tempStudent->operator[](j);
        }
    }
}

template <typename T>
void Menu::cautaDupaClasa() {
    for(int i = 0; i < listaParticipanti.size(); i++){
        Student *tempStudent = dynamic_cast<Student *>(listaParticipanti[i].get());
        if (tempStudent != nullptr)
            continue;

        Angajat *tempAngajat = dynamic_cast<Angajat *>(listaParticipanti[i].get());
        if(tempAngajat != nullptr){
            if(!tempAngajat->getContract())
                continue;
        }

        int n = listaParticipanti[i]->getSizeOfList();
        bool wasFound = false;
        for(int j = 0; j < n; j++){
            T *temp = dynamic_cast<T*>(listaParticipanti[i]->operator[](j).get());

            if(temp != nullptr){
                wasFound = true;
                break;
            }
        }
        if(wasFound)
            cout << "A fost gasit participantul:\n" << *listaParticipanti[i] << '\n';
    }
}

void Menu::grupareCursuri() {
    cout << "Participantii care s-au inscris la cel putin un curs de initiere sunt:\n";
    cautaDupaClasa<CursInitiere>();

    cout << "Participantii care s-au inscris la cel putin un curs de calificare sunt:\n";
    cautaDupaClasa<CursCalificare>();

    cout << "Participantii care s-au inscris la cel putin un curs de perfectionare sunt:\n";
    cautaDupaClasa<CursPerfectionare>();
}

void Menu::calculeazaProfit() {
    int totalProfit = 0;
    for(int i = 0; i < listaParticipanti.size(); i++){
        int n = listaParticipanti[i]->getSizeOfList();
        for(int j = 0; j < n; j++){
            shared_ptr<Curs> temp = listaParticipanti[i]->operator[](j);

            CursInitiere *tempInitiere = dynamic_cast<CursInitiere*>(temp.get());
            if(tempInitiere != nullptr){
                totalProfit += listaParticipanti[i]->getCursInitiereProfit(temp->getPret());
                continue;
            }

            CursCalificare *tempCalificare = dynamic_cast<CursCalificare*>(temp.get());
            if(tempCalificare != nullptr){
                totalProfit += listaParticipanti[i]->getCursInitiereProfit(temp->getPret());
                continue;
            }

            CursPerfectionare *tempPerfectionare = dynamic_cast<CursPerfectionare*>(temp.get());
            if(tempPerfectionare != nullptr){
                totalProfit += listaParticipanti[i]->getCursPerfectionareProfit(temp->getPret());
                continue;
            }
        }
    }

    cout << "Profitul total este:" << totalProfit << '\n';
}

void Menu::listOptions(int optiune) {
    if(optiune == 0)
        return;
    else if(optiune == 1)
        printParticipants();
    else if(optiune == 2)
        maximDouaLuni();
    else if(optiune == 3)
        grupareCursuri();
    else if(optiune == 4)
        calculeazaProfit();
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
        cout << "1. Afiseaza toti participantii cu toate informatiile acestora\n"
             << "2. Afiseaza toate cursurile care se termina in maxim 2 luni, urmate de studentii din anul 2 sau 3\n"
             << "3. Afiseaza toti angajatii pe perioada determinata si somerii, grupati dupa cursuri\n"
             << "4. Calculeaza profitul organizatiei pana in prezent\n";
        optiune = chooseOption(0, 4);
        listOptions(optiune);
    }
}

int main() {

    Menu meniu;
    meniu.readParticipants();
    meniu.mainLoop();

    return 0;
}
