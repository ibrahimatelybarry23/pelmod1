#include <iostream>
#include <stdexcept>
#include <climits>

using namespace std;

struct nodo {
    int val;
    nodo* next;
};

class list {
    public:
        // ── Costruttori / Distruttore ─────────────────────────────────────
        list();                         // costruttore default (lista vuota)
        list(const list& other);        // copy constructor (deep copy)
        ~list();                         // distruttore

        // ── Basic ops ─────────────────────────────────────────────────────
        void push_front(int e);          // inserimento in testa – O(1)
        void push_back(int e);           // inserimento in coda – O(N)
        void print() const;              // stampa tutti gli elementi
        int  size() const;               // numero di elementi (ricorsivo)
        bool is_present(int e) const;    // vero se e compare almeno una volta

        // ── Operator overload ─────────────────────────────────────────────
        list& operator=(const list& other);          // copy-assignment
        bool  operator==(const list& other) const;   // uguaglianza strutturale
        list  operator+ (const list& other) const;   // concatenazione
        list  operator- (const list& other) const;   // differenza (elementi di *this non in other)
        list  operator* (const list& other) const;   // intersezione (elementi in ENTRAMBE)

        // ── ESERCIZI ──────────────────────────────────────────────────────

          // ── Indexed access ────────────────────────────────────────────────
        
        // at (writable): scorre pos passi da head e ritorna riferimento al valore.
        //   Se pos è fuori range, solleva std::out_of_range.
        //   Esempi:
        //     [10 20 30], at(0) → 10
        //     [10 20 30], at(1) → 20
        //     [10 20 30], at(5) → throw
        //     [], at(0)         → throw
        //   Usabile sia in lettura che in scrittura:
        //     lista.at(1) = 99;   // modifica il secondo elemento
        int&       at(int pos);
        
        // at (read-only): overload const che si usa quando l'oggetto è const.
        //   Stesso comportamento ma ritorna riferimento costante.
        const int& at(int pos) const;

        // 1) Rimuove tutti i nodi pari dalla lista.
        //    Esempi:
        //      [1 2 3 4 5] → [1 3 5]
        //      [2 4 6]     → []
        //      [1 3 5]     → [1 3 5]
        //      []          → []
        void remove_even();

        // 2) Ritorna il MASSIMO valore nella lista. Se vuota, solleva eccezione
        //    std::out_of_range. Implementazione RICORSIVA.
        //    Esempi:
        //      [3 1 7 2 5] → 7
        //      [42]        → 42
        //      []          → throw
        int max() const;

        // 3) Inserisce un nodo con valore v in posizione ordinata (crescente).
        //    Assume la lista già ordinata.
        //    Esempi:
        //      [1 3 5], insert_sorted(4) → [1 3 4 5]
        //      [1 3 5], insert_sorted(0) → [0 1 3 5]
        //      [1 3 5], insert_sorted(9) → [1 3 5 9]
        //      [],      insert_sorted(7) → [7]
        void insert_sorted(int v);
        void remove_prefix_sum(int s);
        // 4) Raddoppia ogni nodo NEGATIVO (inserisce un clone dopo di lui).
        //    Implementazione RICORSIVA.
        //    Esempi:
        //      [-1 2 -3 4]  → [-1 -1 2 -3 -3 4]
        //      [1 2 3]      → [1 2 3]
        //      [-5]         → [-5 -5]
        //      []           → []
        void double_negative();

        // 5) TARGET SUM: Rimuove tutti i nodi del PREFISSO la cui somma cumulata
        //    (dalla testa) è ≤ s. Ferma alla prima volta che la somma supera s.
        //    Esempi:
        //      [1 2 3 4 5], remove_prefix_sum(5) → [3 4 5]
        //        (somma 1+2=3 ≤ 5 → rimuovi; 3+3=6 > 5 → ferma)
        //      [1 2 3], remove_prefix_sum(100) → []     (tutto ≤ 100)
        //      [1 2 3], remove_prefix_sum(0)   → [1 2 3] (già > 0 con il primo)
        void remove_prefix_sum(int s);

        // 6) Conta il numero di elementi PRIMA del primo negativo.
        //    Usa un output parameter per il conteggio.
        //    Ritorna:
        //      true + count = elementi prima del primo negativo
        //      false + count = lunghezza totale (no negativi trovati)
        //    Esempi:
        //      [1 2 -3 4]  → true, count = 2
        //      [1 -1 2 -5] → true, count = 1
        //      [1 2 3]     → false, count = 3
        //      [-1 2 3]    → true, count = 0
        //      []          → false, count = 0
        bool count_before_neg(int& count) const;

        // 7) Scambia il primo e l'ultimo elemento della lista (solo i valori).
        //    Se la lista ha 0 o 1 elementi, non fa nulla.
        //    Esempi:
        //      [1 2 3 4 5] → [5 2 3 4 1]
        //      [1 2]       → [2 1]
        //      [1]         → [1]
        //      []          → []
        void swap_ends();
    bool count_before_neg(int& count) const;
    private:
        nodo* head;
        int size_rec(nodo*cur) const;
        int max_rec(nodo * cur) const;
        void double_negative_rec(nodo*&cur);
        // ── Helper privati (li aggiungi tu se servono) ────────────────────
        // Suggerimenti:
        //   - max/size: helper ricorsivi che prendono un nodo* e ritornano int
        //   - double_negative: helper con cell*& e ricorsione
        //   - remove_even, remove_prefix_sum: possono essere iterativi o ricorsivi
        //   - count_before_neg: helper con output parameter (come countfrom0)
        //   - swap_ends: serve trovare l'ultimo nodo
};

// costruttore
list::list(){
    head = nullptr;
}

// copy constructor 

 list::list(const list& other){
    head = nullptr;
    nodo* curr = nullptr;
    nodo* curr_o = other.head;
    while(curr_o != nullptr){
        nodo* nu = new nodo{curr_o->val,nullptr};
        if(head == nullptr){
            head = nu;
            curr = nu;
        }else{
            curr->next = nu;
            curr = curr->next;
        }
        curr_o = curr->next;
    }
 }


list::~list(){
    while(head != nullptr){
        nodo * tmp = head;
        head = head->next,
        delete tmp;
    }
}



 void list:: push_front(int e){
    nodo* nu = new nodo{e,head};
    head = nu;
 }

 void list::push_back(int e){
    nodo* cur = head;
    nodo * nc = new nodo {e,nullptr};
    if(cur == nullptr){
        head = nc; 
    }else{
        while(cur->next != nullptr)
            cur = cur->next;
        cur->next = nc;
    }
 }


void list:: print() const{
    nodo* curr = head;
    while(head != nullptr){
        std::cout<< curr->val<<std::endl;
        curr=curr->next;
    }
}

bool list:: is_present(int e) const{
    nodo * cur = head;
    while(cur != nullptr){
        if(cur->val == e) 
            return true;
        cur = cur->next;
    }
    return false;
}



int list::  size() const{
    size_rec(head);
}
 int list::size_rec(nodo*cur) const{
    if(cur == nullptr) return 0;
    return 1+size_rec(cur->next);
 }

int& list:: at(int pos){
    nodo * cur  = head;
    for(int i = 0; cur != nullptr && i != pos;i++)
        cur = cur->next;
    if(cur==nullptr)
        throw std::out_of_range("OOR Error");
    return cur->val;
}

 const int& list:: at(int pos) const{
    nodo *cur = head;
    for(int i = 0; cur != nullptr &&i != pos;i++)
        cur = cur->next;
    if(cur == nullptr)
        throw std::out_of_range("OOR Error");
    return cur->val;
 }
    void  list::remove_even(){
        while(head != nullptr && head->val%2 == 0){
            nodo*tmp =head;
            head=head->next;
            delete tmp;
        }
        nodo*prev=head;
        while(prev != nullptr && prev->next != nullptr){
            nodo *cur =prev->next;
            if(cur->val %2== 0){
                nodo* tmp = cur;
                prev->next = cur->next;
                delete tmp;
            } else
                    prev = prev->next;
        }
    }





        void list:: double_negative(){
            double_negative_rec(head);
        }

       void list:: double_negative_rec(nodo*&cur){
            if(cur == nullptr)
                return;
            double_negative_rec(cur->next);
            if(cur->val<0){
                cur->next = new nodo{cur->val,cur->next};
            }
                
       }

    int list:: max() const{
        if(head == nullptr)
            throw std::out_of_range("empty list");
        return max_rec(head);
    }
int list::max_rec(nodo* curr) const{
    if(curr->next == nullptr )
        return curr->val;
    int max_val= max_rec(curr->next);
    if(curr->val > max_val)
        max_val = curr->val;
    return max_val;
    
}


void list:: insert_sorted(int v){
        nodo* nuovo = new nodo{v, nullptr};
        if(head == nullptr || v < head->val ){
            nuovo ->next = head;
            head = nuovo; 
            return;
        }
        nodo * prev = head;
        while (prev->next != nullptr && prev->next->val <v)
            prev = prev->next;
        nuovo->next =prev->next;
        prev->next = nuovo;
}



void list:: swap_ends(){
    if(head == nullptr || head->next == nullptr)
        return; 
        nodo *ultimo = head;
        while(ultimo ->next!= nullptr)
            ultimo = ultimo->next;
        int tmp = head->val;
        head->val = ultimo->val;
        ultimo->val = tmp;
}

void list::remove_prefix_sum(int s){
    int sum = 0; 
    while(head != nullptr && sum +head->val <= s){
        sum += head->val;

        nodo* tmp = head; 
        head = head->next; 
        delete tmp; 
    }
}
void list::remove_prefix_sum(int s){
    int sum = 0; 
    while(head != nullptr && sum +head->val <= s){
        sum += head->val;

        nodo* tmp = head; 
        head = head->next; 
        delete tmp; 
    }
}
void list::remove_prefix_sum(int s){
    int sum = 0; 
    while(head != nullptr && sum +head->val <= s){
        sum += head->val;

        nodo* tmp = head; 
        head = head->next; 
        delete tmp; 
    }
}
bool list::count_before_neg(int& count) const{
    count = 0; 
    bool f = false; 
    nodo *cur =head;
    while(cur!= nullptr && !f){
        if(cur->val <0)
            f= true;
        else{
            count++;
            cur=cur->next;
        }
    }
    return f; 
}



list& list::operator=(const list& other){
   if(this == &other ) return *this;
    while(head != nullptr){
        nodo * tmp = head;
        head=head->next;
        delete tmp;
    }
    head = nullptr;
    nodo * cur = head;
    nodo * cur_o = other.head;
    while(cur_o != nullptr){
        nodo * nu = new nodo{cur_o->val,nullptr};
        if(head == nullptr){
            head = nu; 
            cur = nu;
        } else{
            cur->next = nu; 
            cur = cur->next;
        }
        cur_o = cur_o->next;
    }
    return *this;
}




  bool  list::operator==(const list& other) const{
    if(this == &other) return true;
    nodo* cur = this->head;
    nodo* cur_O = other.head;

    while(cur!= nullptr && cur_O != nullptr){
        if(cur->val != cur_O->val )
             return false;
        else{
            cur = cur->next;
            cur_O = cur_O->next;
        }
    }
    return cur ==cur_O;
  }

list  list::operator+ (const list& other) const{
    list res(*this);
    nodo* cur  =  other.head;
    while(cur != nullptr){
        res.push_back(cur->val);
        cur = cur->next;
    }
    return res;
}


list list:: operator- (const list& other) const{
    list res;
    nodo * cur = head;
    while(cur != nullptr){
        if(!other.is_present(cur->val)){
            res.push_back(cur->val);
        }
        cur = cur->next;
    }
    return res;
}

list  list::operator* (const list& other) const{
    list res; 
    if(head == nullptr || other.head ==nullptr )
        return res;

    nodo *cur = head;
     while(cur != nullptr){
        if(other.is_present(cur->val) && !res.is_present(cur->val)){
            res.push_back(cur->val);
        }
        cur = cur->next;
    }
    return res;
}
int main() {
    cout << "========== TEST list.cpp ==========" << endl << endl;

    // Test 1: push_front/push_back/print/size
    cout << "--- Test 1: base ops ---" << endl;
    list l;
    l.push_back(1); l.push_back(2); l.push_back(3);
    l.push_front(0);
    cout << "Atteso: 0 1 2 3 - Ottenuto: "; l.print();
    cout << "Size atteso 4, ottenuto: " << l.size() << endl;
    cout << endl;

    // Test 2: copy constructor + ==
    cout << "--- Test 2: copy + == ---" << endl;
    list lc(l);
    cout << "Copia: "; lc.print();
    cout << "(l == lc) atteso 1, ottenuto: " << (l == lc) << endl;
    lc.push_back(99);
    cout << "Dopo modifica copia, originale: "; l.print();
    cout << endl;

    // Test 3: operator=
    cout << "--- Test 3: operator= ---" << endl;
    list l2;
    l2.push_back(999);
    l2 = l;
    cout << "Dopo l2 = l, l2: "; l2.print();
    l2 = l2;
    cout << "Self-assignment, l2: "; l2.print();
    cout << endl;

    // Test 4: is_present
    cout << "--- Test 4: is_present ---" << endl;
    cout << "is_present(2) atteso 1, ottenuto: " << l.is_present(2) << endl;
    cout << "is_present(99) atteso 0, ottenuto: " << l.is_present(99) << endl;
    cout << endl;

    // Test 5: remove_even
    cout << "--- Test 5: remove_even ---" << endl;
    list re;
    re.push_back(1); re.push_back(2); re.push_back(3); re.push_back(4); re.push_back(5);
    re.remove_even();
    cout << "[1 2 3 4 5] remove_even, atteso: 1 3 5 - Ottenuto: "; re.print();
    list re2;
    re2.push_back(2); re2.push_back(4); re2.push_back(6);
    re2.remove_even();
    cout << "[2 4 6] remove_even, atteso: (vuota) - Ottenuto: "; re2.print();
    cout << endl;

    // Test 6: max
    cout << "--- Test 6: max ---" << endl;
    list m;
    m.push_back(3); m.push_back(1); m.push_back(7); m.push_back(2); m.push_back(5);
    cout << "max atteso 7, ottenuto: " << m.max() << endl;
    list m2;
    m2.push_back(42);
    cout << "[42] max atteso 42, ottenuto: " << m2.max() << endl;
    try {
        list m3;
        m3.max();
    } catch (std::out_of_range& e) {
        cout << "[] max -> throw: " << e.what() << endl;
    }
    cout << endl;

    // Test 7: insert_sorted
    cout << "--- Test 7: insert_sorted ---" << endl;
    list is;
    is.push_back(1); is.push_back(3); is.push_back(5);
    is.insert_sorted(4);
    cout << "[1 3 5] + 4, atteso: 1 3 4 5 - Ottenuto: "; is.print();
    is.insert_sorted(0);
    cout << "Dopo +0, atteso: 0 1 3 4 5 - Ottenuto: "; is.print();
    is.insert_sorted(9);
    cout << "Dopo +9, atteso: 0 1 3 4 5 9 - Ottenuto: "; is.print();
    list is2;
    is2.insert_sorted(7);
    cout << "[] + 7, atteso: 7 - Ottenuto: "; is2.print();
    cout << endl;

    // Test 8: double_negative
    cout << "--- Test 8: double_negative ---" << endl;
    list dn;
    dn.push_back(-1); dn.push_back(2); dn.push_back(-3); dn.push_back(4);
    dn.double_negative();
    cout << "Atteso: -1 -1 2 -3 -3 4 - Ottenuto: "; dn.print();
    list dn2;
    dn2.push_back(1); dn2.push_back(2); dn2.push_back(3);
    dn2.double_negative();
    cout << "[1 2 3] atteso: 1 2 3 - Ottenuto: "; dn2.print();
    list dn3;
    dn3.push_back(-5);
    dn3.double_negative();
    cout << "[-5] atteso: -5 -5 - Ottenuto: "; dn3.print();
    cout << endl;

    // Test 9: remove_prefix_sum
    cout << "--- Test 9: remove_prefix_sum ---" << endl;
    list rp;
    rp.push_back(1); rp.push_back(2); rp.push_back(3); rp.push_back(4); rp.push_back(5);
    rp.remove_prefix_sum(5);
    cout << "[1 2 3 4 5] rps(5) atteso: 3 4 5 - Ottenuto: "; rp.print();
    list rp2;
    rp2.push_back(1); rp2.push_back(2); rp2.push_back(3);
    rp2.remove_prefix_sum(100);
    cout << "[1 2 3] rps(100) atteso: (vuota) - Ottenuto: "; rp2.print();
    list rp3;
    rp3.push_back(1); rp3.push_back(2); rp3.push_back(3);
    rp3.remove_prefix_sum(0);
    cout << "[1 2 3] rps(0) atteso: 1 2 3 - Ottenuto: "; rp3.print();
    cout << endl;

    // Test 10: count_before_neg
    cout << "--- Test 10: count_before_neg ---" << endl;
    int c;
    list cb;
    cb.push_back(1); cb.push_back(2); cb.push_back(-3); cb.push_back(4);
    bool r = cb.count_before_neg(c);
    cout << "[1 2 -3 4] atteso: 1, 2 - Ottenuto: " << r << ", " << c << endl;
    list cb2;
    cb2.push_back(1); cb2.push_back(-1); cb2.push_back(2); cb2.push_back(-5);
    r = cb2.count_before_neg(c);
    cout << "[1 -1 2 -5] atteso: 1, 1 - Ottenuto: " << r << ", " << c << endl;
    list cb3;
    cb3.push_back(1); cb3.push_back(2); cb3.push_back(3);
    r = cb3.count_before_neg(c);
    cout << "[1 2 3] atteso: 0, 3 - Ottenuto: " << r << ", " << c << endl;
    list cb4;
    cb4.push_back(-1); cb4.push_back(2); cb4.push_back(3);
    r = cb4.count_before_neg(c);
    cout << "[-1 2 3] atteso: 1, 0 - Ottenuto: " << r << ", " << c << endl;
    cout << endl;

    // Test 11: swap_ends
    cout << "--- Test 11: swap_ends ---" << endl;
    list se;
    se.push_back(1); se.push_back(2); se.push_back(3); se.push_back(4); se.push_back(5);
    se.swap_ends();
    cout << "[1 2 3 4 5] swap, atteso: 5 2 3 4 1 - Ottenuto: "; se.print();
    list se2;
    se2.push_back(1); se2.push_back(2);
    se2.swap_ends();
    cout << "[1 2] swap, atteso: 2 1 - Ottenuto: "; se2.print();
    list se3;
    se3.push_back(1);
    se3.swap_ends();
    cout << "[1] swap, atteso: 1 - Ottenuto: "; se3.print();
    cout << endl;

    // Test 12: operator+
    cout << "--- Test 12: operator+ ---" << endl;
    list p1, p2;
    p1.push_back(1); p1.push_back(2);
    p2.push_back(3); p2.push_back(4);
    list conc = p1 + p2;
    cout << "[1 2] + [3 4] atteso: 1 2 3 4 - Ottenuto: "; conc.print();
    cout << endl;

    // Test 13: operator- (differenza)
    cout << "--- Test 13: operator- ---" << endl;
    list d1, d2;
    d1.push_back(1); d1.push_back(2); d1.push_back(3); d1.push_back(4);
    d2.push_back(2); d2.push_back(4);
    list diff = d1 - d2;
    cout << "[1 2 3 4] - [2 4] atteso: 1 3 - Ottenuto: "; diff.print();
    list d3;
    d3.push_back(1); d3.push_back(1); d3.push_back(2); d3.push_back(2); d3.push_back(3);
    list d4;
    d4.push_back(2);
    list diff2 = d3 - d4;
    cout << "[1 1 2 2 3] - [2] atteso: 1 1 3 - Ottenuto: "; diff2.print();
    list d5;
    d5.push_back(1); d5.push_back(2); d5.push_back(3);
    list vuota;
    list diff3 = d5 - vuota;
    cout << "[1 2 3] - [] atteso: 1 2 3 - Ottenuto: "; diff3.print();
    cout << endl;

    // Test 14: operator* (intersezione)
    cout << "--- Test 14: operator* ---" << endl;
    list i1, i2;
    i1.push_back(1); i1.push_back(2); i1.push_back(3); i1.push_back(4);
    i2.push_back(2); i2.push_back(4);
    list inter = i1 * i2;
    cout << "[1 2 3 4] * [2 4] atteso: 2 4 - Ottenuto: "; inter.print();
    list i3;
    i3.push_back(1); i3.push_back(1); i3.push_back(2); i3.push_back(2); i3.push_back(3);
    list i4;
    i4.push_back(2);
    list inter2 = i3 * i4;
    cout << "[1 1 2 2 3] * [2] atteso: 2 2 - Ottenuto: "; inter2.print();
    list i5;
    i5.push_back(1); i5.push_back(2); i5.push_back(3);
    list inter3 = i5 * vuota;
    cout << "[1 2 3] * [] atteso: (vuota) - Ottenuto: "; inter3.print();
    cout << endl;



    // Test 15: at (writable e const)
    cout << "--- Test 15: at ---" << endl;
    list a1;
    a1.push_back(10); a1.push_back(20); a1.push_back(30);
    cout << "at(0) atteso: 10, ottenuto: " << a1.at(0) << endl;
    cout << "at(1) atteso: 20, ottenuto: " << a1.at(1) << endl;
    cout << "at(2) atteso: 30, ottenuto: " << a1.at(2) << endl;
    
    // Usato in scrittura
    a1.at(1) = 99;
    cout << "Dopo at(1) = 99, atteso: 10 99 30 - Ottenuto: "; a1.print();
    
    // Out of range
    try {
        a1.at(100);
    } catch (std::out_of_range& e) {
        cout << "at(100) -> throw: " << e.what() << endl;
    }
    try {
        list vuota2;
        vuota2.at(0);
    } catch (std::out_of_range& e) {
        cout << "at(0) su [] -> throw: " << e.what() << endl;
    }
    
    // Test della versione const
    const list& a_const = a1;
    cout << "at(0) const atteso: 10, ottenuto: " << a_const.at(0) << endl;
    // a_const.at(0) = 5;  // ← questa riga NON compilerebbe: giusto!
    cout << endl;

    cout << "========== FINE TEST ==========" << endl;
    return 0;
}