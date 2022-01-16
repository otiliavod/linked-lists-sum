/* Să se implementeze operaţiile de adunare a două numere mari,
 * folosind liste simplu inlantuite (fiecare cifră cifre a unui
 * număr mare se va reţine într-o celulă).*/

#include <iostream>
using namespace std;

struct Element{
    int cifra;          // structura unei celule din lista
    Element* next;
};

int transport = 0;  // pentru adunare
void citire(long &nr1, long &nr2);
void inserareCifra(long n, Element*& l);
void inserareLaInceput(Element*& l, int x);
void inserareLaFinal(Element*& l, int x);
void adunare(int nr1, int nr2, Element*& listaRez, int& transport);
void adunareListe(Element*& l1, Element*& l2, Element*& listaRez, int& transport);
void afisare(Element*& l);

int main()
{
    long n1, n2;
    Element* headL1 = new Element;
    Element* headL2 = new Element;
    Element* headRezultat = new Element;

    citire(n1,n2);

    if(n1 > n2) {
        inserareCifra(n1, headL1);
        inserareCifra(n2, headL2);
    }
    else {
        inserareCifra(n2, headL1);
        inserareCifra(n1, headL2);
    }

    adunareListe(headL1, headL2, headRezultat, transport);
    afisare(headRezultat);

    return 0;
}

// functie citire numere
void citire(long &nr1, long &nr2) {

    cout<<"Introduceti primul numar mare: "; cin>>nr1;
    cout<<"Introduceti al doilea numar mare: "; cin>>nr2;
    cout<<endl;

}

// functie pentru inserarea cifrelor numerelor in liste in ordine inversa
void inserareCifra(long n, Element*& l) {

    int c = 0;

    while(n) {

        c = n % 10;
        inserareLaFinal(l, c);
        n/= 10;
    }
}

// inserarea cifrelor rezultatului in lista finala
void inserareLaInceput(Element*& l, int x) {

    Element* elementNou = new Element;
    elementNou -> cifra = x;
    elementNou -> next = l -> next;
    l -> next = elementNou;
}

void inserareLaFinal(Element*& l, int x) {

    Element* elementNou = new Element;
    Element* p = l;

    // p folosit pentru a cauta adresa ultimului element
    while(p -> next != NULL) {
        p = p -> next;
    }

    elementNou -> cifra = x;
    elementNou -> next = NULL;
    p -> next = elementNou;
}

void adunare(int nr1, int nr2, Element*& listaRez, int& transport) {
    int sumaCifre = nr1 + transport, cifraRez = 0;

    if(nr2) {
        sumaCifre+= nr2;
    }

    if(sumaCifre > 9) {
        cifraRez = sumaCifre % 10;
        transport = 1;
    }
    else if(sumaCifre <= 9) {
        cifraRez = sumaCifre;
        transport = 0;
    }

    inserareLaInceput(listaRez,cifraRez);
}

void adunareListe(Element*& l1, Element*& l2, Element*& listaRez, int& transport) {

    // initializarea capetelor listelor cu primele elemente
    l1 = l1 -> next;
    l2 = l2 -> next;

    //l1 va fi mereu >= l2 ca si dimensiune
    while(l1) {
        int nr1 = l1 -> cifra;
        int nr2 = 0;

        if(l2){
            nr2 = l2 -> cifra;
        }

        adunare(nr1, nr2, listaRez, transport);
        l1 = l1 -> next;

        if(l2){
            l2 = l2 -> next;
        }
    }

    // daca dupa ce s-au adunat toate cifrele ramane transport 1, se va adauga 1 la inceputul listei finale
    if(transport == 1) {
        adunare(listaRez -> cifra, NULL, listaRez, transport);
    }
}

void afisare(Element*& l) {

    // initializare cap lista cu primul element al listei
    l = l -> next;
    cout<<"Rezultatul adunarii este: ";
    while(l) {

        cout<<l -> cifra;
        l = l -> next;
    }
}