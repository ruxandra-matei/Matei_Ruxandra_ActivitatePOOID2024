#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Autobuz {

private:
    static int nrAutobuze;
    const int idAutobuz;
    int capacitate;
    int nrPersoaneImbarcate;
    char* producator;
public:
    int getCapacitate() const {
        return capacitate;
    }

    void setCapacitate(int cap) {
        if (cap <= 0) {
            cout << endl << "Capacitatea trebuie sa fie pozitiv?!";
        }
        if (cap < nrPersoaneImbarcate) {
            cout << endl << "Noua capacitate nu poate fi mai mic? decât num?rul actual de persoane!";
        }
        capacitate = cap;
    }

    int getNrPersoaneImbarcate() const {
        return nrPersoaneImbarcate;
    }

    void setNrPersoaneImbarcate(int nr) {
        if (nr < 0) {
            cout << endl << "Num?rul de persoane nu poate fi negativ!";
        }
        if (nr > capacitate) {
            cout << endl << "Num?rul de persoane nu poate dep??i capacitatea!";
        }
        nrPersoaneImbarcate = nr;
    }

    int getId() const {
        return idAutobuz;
    }

    Autobuz() : idAutobuz(++nrAutobuze) {
        capacitate = 40;
        nrPersoaneImbarcate = 0;
        producator = new char[strlen("Solaris") + 1];
        strcpy(producator, "Solaris");
    }

    Autobuz(int cap, int nrPers, const char* prod) : idAutobuz(++nrAutobuze) {
        if (cap <= 0) {
            cout << endl << "Capacitatea trebuie s? fie pozitiv?!";
        }
        capacitate = cap;

        if (nrPers < 0) {
            cout << endl << "Num?rul de persoane nu poate fi negativ!";
        }
        if (nrPers > cap) {
            cout << endl << "Num?rul de persoane nu poate dep??i capacitatea!";
        }
        nrPersoaneImbarcate = nrPers;

        if (prod == nullptr) {
            cout << endl << "Produc?torul nu poate fi null!";
        }
        producator = new char[strlen(prod) + 1];
        strcpy(producator, prod);
    }

    Autobuz(const Autobuz& a) : idAutobuz(++nrAutobuze) {
        this->capacitate = a.capacitate;
        this->nrPersoaneImbarcate = a.nrPersoaneImbarcate;
        this->producator = new char[strlen(a.producator) + 1];
        strcpy(this->producator, a.producator);
    }

    ~Autobuz() {
        delete[] producator;
    }

    Autobuz& operator=(const Autobuz& a) {
        if (this != &a) {
            this->capacitate = a.capacitate;
            this->nrPersoaneImbarcate = a.nrPersoaneImbarcate;
            delete[] this->producator;
            this->producator = new char[strlen(a.producator) + 1];
            strcpy(this->producator, a.producator);
        }
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Autobuz& a) {
        out << a.idAutobuz << "; " << a.capacitate << "; "
            << a.nrPersoaneImbarcate << "; " << a.producator;
        return out;
    }

    int getNumarLocuriLibere() const {
        return capacitate - nrPersoaneImbarcate;
    }

    operator int() const {
        return nrPersoaneImbarcate;
    }

    bool operator>(const Autobuz& a) const {
        return this->capacitate > a.capacitate;
    }
};

int Autobuz::nrAutobuze = 0;

int main() {
    try {
        cout << "Test constructor fara parametri:" << endl;
        Autobuz a1;
        cout << "Autobuz 1: " << a1 << endl;

        cout << "\nTest constructor cu parametri:" << endl;
        Autobuz a2(50, 30, "Mercedes");
        cout << "Autobuz 2: " << a2 << endl;

        cout << "\nTest constructor de copiere:" << endl;
        Autobuz a3 = a2;
        cout << "Autobuz 3 (copie a lui a2): " << a3 << endl;

        cout << "\nTest operator =:" << endl;
        Autobuz a4;
        a4 = a2;
        cout << "Autobuz 4 (dupa atribuirea lui a2): " << a4 << endl;

        cout << "\nTest getteri si setteri:" << endl;
        cout << "Capacitate a2: " << a2.getCapacitate() << endl;
        a2.setCapacitate(60);
        cout << "Capacitate noua a2: " << a2.getCapacitate() << endl;

        cout << "\nTest getNumarLocuriLibere:" << endl;
        cout << "Locuri libere in a2: " << a2.getNumarLocuriLibere() << endl;

        cout << "\nTest operator de conversie la int:" << endl;
        int nrPersoane = (int)a2;
        cout << "Persoane in a2: " << nrPersoane << endl;

        cout << "\nTest operator >:" << endl;
        if (a2 > a1) {
            cout << "Autobuzul 2 are capacitate mai mare decat Autobuzul 1" << endl;
        }

        cout << "\nTest validari:" << endl;
        try {
            Autobuz aInvalid(-10, 5, "Test");
        }
        catch (const invalid_argument& e) {
            cout << "Exceptie prinsa corect: " << e.what() << endl;
        }
    }
    catch (const exception& e) {
        cout << "Eroare: " << e.what() << endl;
    }

    return 0;
}
