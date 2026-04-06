#include <iostream>
#include <vector>

// * ************************************************* * 
// * Classe Foo — esempio di gestione memoria dinamica * 
// * ************************************************* * 

class Foo {
public:
    Foo();                  // costruttore di default
    Foo(const Foo& s);      // copy constructor (deep copy)
    ~Foo();                 // distruttore
    void print() const;     // stampa il valore di *x
    void setX(int a);       // imposta il valore di *x
private:
    int* x;                 // puntatore a int allocato sullo heap
};

//  Costruttore di default 
Foo::Foo() {
    x = new int;
    *x = 0;
    std::cout << "[Costruttore di default] *x = " << *x << std::endl;
}

//  Copy constructor 
// Alloca NUOVA memoria e copia il VALORE (non l'indirizzo).
// Senza questo, il passaggio per valore causerebbe un double-free
// e un conseguente segmentation fault.
Foo::Foo(const Foo& s) {
    x = new int;
    *x = *(s.x);
    std::cout << "[Copy constructor] *x = " << *x << std::endl;
}

//  Distruttore 
// Chiamato automaticamente alla fine dello scope (o con delete).
// Libera la memoria allocata con new per evitare memory leak.
Foo::~Foo() {
    std::cout << "[Distruttore] *x = " << *x << std::endl;
    delete x;
}

//  Metodi 
void Foo::print() const {
    std::cout << "[print] *x = " << *x << std::endl;  // *x = valore, x = indirizzo
}

void Foo::setX(int a) {
    *x = a;
}

// 
//  Passaggio per VALORE:
//  Viene invocato il copy constructor → viene creata una copia locale 'a'.
//  Alla fine della funzione, 'a' esce dallo scope → il suo distruttore
//  viene chiamato e la memoria della COPIA viene liberata.
//  L'oggetto originale rimane intatto grazie alla deep copy.
// 
void funzionePerValore(Foo a) {
    a.print();
}  //  distruttore chiamato su 'a' (la copia), NON sull'originale

// 
//  Passaggio per RIFERIMENTO:
//  'a' è un alias dell'oggetto originale → nessuna copia creata.
//  Il distruttore NON viene chiamato alla fine della funzione.
//  Più efficiente e sicuro quando non serve una copia.
// 
void funzionePerRiferimento(Foo& a) {
    a.print();
}  //  nessun distruttore: 'a' è solo un alias, non un oggetto autonomo

// 
int main() {
    std::cout << " Inizio del programma " << std::endl;

    Foo x;
    x.setX(42);

    std::cout << "\n-- Chiamata per valore (copy ctor + dtor sulla copia) --" << std::endl;
    funzionePerValore(x);

    std::cout << "\n-- Chiamata per riferimento (nessuna copia) --" << std::endl;
    funzionePerRiferimento(x);

    //  Esempi commentati 

    // Array di oggetti: costruttore chiamato 10 volte,
    // distruttore chiamato 10 volte in ordine inverso alla fine dello scope.
    // Foo myv1[10];

    // Oggetto dinamico: distruttore NON chiamato automaticamente,
    // bisogna usare delete esplicitamente.
    // Usa -> perché pf è un puntatore.
    // Foo* pf = new Foo;
    // pf->setX(100);
    // pf->print();
    // delete pf;

    // Vector di 12 oggetti Foo: costruttore chiamato 12 volte.
    // Quando il vector viene distrutto, chiama il distruttore su tutti gli elementi.
    // std::vector<Foo> v(12);

    std::cout << " Fine del programma " << std::endl;
    // x esce dallo scope → distruttore chiamato automaticamente
    return 0;
}