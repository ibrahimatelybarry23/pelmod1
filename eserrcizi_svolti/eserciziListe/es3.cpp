
#include <iostream>
#include <stdexcept>
using namespace std;

struct node {
    int val;
    node* next;
};

class mylist {
    public:
        // ══════════════════════════════════════════════════════════════════
        //   COSTRUTTORI / DISTRUTTORE
        // ══════════════════════════════════════════════════════════════════
        mylist();
        mylist(const mylist& other);
        ~mylist();

        // ══════════════════════════════════════════════════════════════════
        //   BASIC OPS (warm-up)
        // ══════════════════════════════════════════════════════════════════
        void push_front(int e);
        void push_back(int e);
        void print() const;
        int  size() const;                  // ricorsivo
        bool is_present(int e) const;
        int&       at(int pos);
        const int& at(int pos) const;

        // ══════════════════════════════════════════════════════════════════
        //   OPERATOR OVERLOAD (tutti)
        // ══════════════════════════════════════════════════════════════════

        // --- Assegnamento ---
        mylist& operator=(const mylist& other);    // copy-assignment

        // --- Confronto ---
        bool operator==(const mylist& other) const;  // uguaglianza elementare (ricorsivo)
        bool operator!=(const mylist& other) const;  // banale: !(a==b)
        bool operator< (const mylist& other) const;  // ordine lessicografico
        //   [1 2 3] < [1 2 4]   → true
        //   [1 2]   < [1 2 3]   → true  (prefisso → minore)
        //   [1 2 3] < [1 2 3]   → false
        //   []      < [1]       → true
        //   [2]     < [1 9 9]   → false
        bool operator<=(const mylist& other) const;
        bool operator> (const mylist& other) const;
        bool operator>=(const mylist& other) const;

        // --- Operazioni insiemistiche / concatenazione ---
        mylist operator+(const mylist& other) const; // concatenazione
        mylist operator-(const mylist& other) const; // differenza (elementi di *this NON in other)
        mylist operator*(const mylist& other) const; // intersezione (senza duplicati)
        mylist operator&(const mylist& other) const; // intersezione CON duplicati (min occorrenze)
        //   [1 1 2 2 3] & [1 2 2 4] → [1 2 2]
        mylist operator|(const mylist& other) const; // unione (set union, senza duplicati)
        //   [1 2 3] | [2 3 4]       → [1 2 3 4]

        // --- Compound assignment ---
        mylist& operator+=(const mylist& other);     // append di other a this
        mylist& operator+=(int e);                   // push_back di un singolo int
        mylist& operator-=(int e);                   // remove prima occorrenza di e
        mylist& operator-=(const mylist& other);     // rimuove tutti gli elementi che stanno in other

        // --- Accesso ---
        int&       operator[](int pos);              // come at ma SENZA check (UB se fuori range)
        const int& operator[](int pos) const;

        // --- Stream ---
        friend ostream& operator<<(ostream& os, const mylist& l); // stampa "[1 2 3]"
        // (la implementi fuori dalla classe)

        // --- Incremento/decremento (interpretazione custom) ---
        mylist& operator++();        // prefix: incrementa ogni valore di 1
        mylist  operator++(int);     // postfix: ritorna copia vecchia, incrementa
        mylist& operator--();        // prefix: decrementa ogni valore di 1
        mylist  operator--(int);     // postfix: ritorna copia vecchia, decrementa

        // --- Unario ---
        mylist operator-() const;    // ritorna una lista con tutti i valori negati
        //   -[1 -2 3] → [-1 2 -3]

        // --- Conversione ---
        explicit operator bool() const;  // true se non vuota
        //   if (lista) { ... }          // vero se lista.size() > 0


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 1 — CONTEGGIO / RICERCA (ricorsivi)
        // ══════════════════════════════════════════════════════════════════

        // 1.1) count(e): conta occorrenze di e. RICORSIVO.
        //   [1 2 3 2 4 2], count(2) → 3
        int count(int e) const;

        // 1.2) count_if_even(): conta quanti nodi hanno valore pari. RICORSIVO.
        //   [1 2 3 4 5] → 2
        int count_if_even() const;

        // 1.3) count_if_negative(): conta quanti valori sono < 0. RICORSIVO.
        //   [-1 2 -3 -4 5] → 3
        int count_if_negative() const;

        // 1.4) find_first(e): ritorna la POSIZIONE (0-based) della prima
        //      occorrenza di e; -1 se assente. RICORSIVO.
        //   [10 20 30 20], find_first(20) → 1
        //   [10 20 30],    find_first(99) → -1
        int find_first(int e) const;

        // 1.5) find_last(e): posizione dell'ULTIMA occorrenza di e; -1 se assente.
        //      Suggerimento: ricorsivo con output parameter, oppure usa size - find su flip.
        //   [10 20 30 20 40], find_last(20) → 3
        int find_last(int e) const;


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 2 — MIN / MAX / AGGREGATI (ricorsivi)
        // ══════════════════════════════════════════════════════════════════

        // 2.1) min(): valore minimo; throw se vuota. RICORSIVO.
        int min() const;

        // 2.2) max(): valore massimo; throw se vuota. RICORSIVO.
        int max() const;

        // 2.3) sum(): somma di tutti i valori. RICORSIVO.
        //   [1 2 3 4] → 10
        //   []        → 0
        int sum() const;

        // 2.4) avg(): media (come double); throw se vuota.
        double avg() const;

        // 2.5) sum_even(): somma dei valori PARI. RICORSIVO.
        //   [1 2 3 4 5] → 6
        int sum_even() const;

        // 2.6) sum_positives(): somma dei valori > 0. RICORSIVO.
        //   [-1 2 -3 4] → 6
        int sum_positives() const;

        // 2.7) product(): prodotto di tutti i valori (1 se vuota). RICORSIVO.
        //   [2 3 4] → 24
        //   []      → 1
        long long product() const;


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 3 — RIMOZIONE CONDIZIONALE
        // ══════════════════════════════════════════════════════════════════

        // 3.1) remove_all(e): rimuove TUTTE le occorrenze di e.
        //   [1 5 2 5 5 3], remove_all(5) → [1 2 3]
        void remove_all(int e);

        // 3.2) remove_even(): rimuove tutti i nodi pari.
        //   [1 2 3 4 5] → [1 3 5]
        void remove_even();

        // 3.3) remove_odd(): rimuove tutti i nodi dispari (occhio ai negativi: -3 è dispari).
        //   [-3 -2 -1 0 1 2 3] → [-2 0 2]
        void remove_odd();

        // 3.4) remove_negative(): rimuove tutti i valori < 0.
        //   [-1 2 -3 4 -5] → [2 4]
        void remove_negative();

        // 3.5) remove_greater_than(int k): rimuove tutti i valori > k.
        //   [1 5 2 8 3], remove_greater_than(4) → [1 2 3]
        void remove_greater_than(int k);

        // 3.6) remove_in_range(int lo, int hi): rimuove i valori v con lo ≤ v ≤ hi.
        //   [1 5 2 8 3], remove_in_range(2, 5) → [1 8]
        void remove_in_range(int lo, int hi);

        // 3.7) remove_at(int pos): rimuove il nodo in posizione pos;
        //      throw std::out_of_range se pos non è valido.
        void remove_at(int pos);

        // 3.8) remove_duplicates(): tiene solo la prima occorrenza di ogni valore.
        //      Non assume lista ordinata.
        //   [1 2 1 3 2 4] → [1 2 3 4]
        void remove_duplicates();

        // 3.9) remove_duplicates_sorted(): VERSIONE per lista ordinata — O(N).
        //   [1 1 2 3 3 3 4] → [1 2 3 4]
        void remove_duplicates_sorted();


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 4 — PREFIX / SUFFIX SUM (ricorsione che "torna su")
        // ══════════════════════════════════════════════════════════════════

        // 4.1) remove_prefix_sum(int s): rimuove i nodi iniziali (prefisso)
        //      finché la somma cumulata ≤ s. Si ferma appena supererebbe s.
        //   [1 2 3 4 5], rps(5) → [3 4 5]   (1+2=3 ≤ 5 ok; 3+3=6 > 5 stop)
        void remove_prefix_sum(int s);

        // 4.2) remove_suffix_sum(int s): stessa cosa ma dalla CODA. RICORSIVO.
        //   [1 2 3 4 5], rss(9) → [1 2 3 4]  (5 ok; 5+4=9 ok; 9+3=12 > 9 stop)
        void remove_suffix_sum(int s);

        // 4.3) remove_up_to_sum(int s): rimuove ogni nodo il cui SUFFIX-SUM
        //      (somma da lui in poi) è ≤ s. RICORSIVO (vedi file originale).
        //   [3 1 2 4 5], remove_up_to_sum(6) → [3 1 2 4]
        void remove_up_to_sum(int s);

        // 4.4) remove_prefix_product(int p): variante col prodotto invece della somma.
        //   [1 2 3 4], rpp(6) → [3 4]    (1 ok; 1*2=2 ok; 2*3=6 ok; 6*4=24 > 6 stop)
        //      Attenzione: se appare 0, il prodotto resta 0 all'infinito → scelta:
        //      rimuovi anche 0 se 0 ≤ p.
        void remove_prefix_product(int p);

        // 4.5) keep_prefix_sum(int s): tiene solo il prefisso massimo
        //      la cui somma resta ≤ s (dualità di remove_prefix_sum).
        //   [1 2 3 4 5], kps(6) → [1 2 3]
        void keep_prefix_sum(int s);


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 5 — OUTPUT PARAMETER + BOOL DI RITORNO
        // ══════════════════════════════════════════════════════════════════
        // Pattern tipico: il metodo ritorna bool (successo / trovato) e
        // restituisce un conteggio o indice via reference.

        // 5.1) countfrom0(int& count): count = quanti elementi dopo l'ULTIMO 0;
        //      ritorna true se almeno uno 0 esiste, false altrimenti
        //      (in tal caso count = 0 — vedi file originale).
        bool countfrom0(int& count) const;

        // 5.2) count_before_neg(int& count): count = elementi prima del primo
        //      negativo; true se negativo trovato, false + count = size() se no.
        bool count_before_neg(int& count) const;

        // 5.3) count_after_max(int& count): elementi DOPO la prima occorrenza
        //      del valore massimo; true se non vuota, false se vuota.
        //   [1 5 2 5 3]  → true, 3
        //   [1 2 3]      → true, 0
        //   []           → false, 0
        bool count_after_max(int& count) const;

        // 5.4) count_between_zeros(int& count): count = elementi STRETTAMENTE
        //      tra il primo e l'ultimo zero; ritorna true se ci sono almeno
        //      due zeri distinti, false altrimenti.
        //   [1 0 2 3 0 4]   → true, 2
        //   [1 0 2]         → false, 0  (un solo zero)
        //   [0 1 2 3 0]     → true, 3
        //   [1 2 3]         → false, 0
        bool count_between_zeros(int& count) const;

        // 5.5) find_with_index(int e, int& idx): se trova e, setta idx alla
        //      posizione e ritorna true; altrimenti false e idx = -1.
        bool find_with_index(int e, int& idx) const;


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 6 — DUPLICAZIONE / INSERIMENTO RICORSIVO
        // ══════════════════════════════════════════════════════════════════

        // 6.1) double_even(): dopo ogni nodo pari inserisce un clone. RICORSIVO.
        //   [2 7 0 5] → [2 2 7 0 0 5]
        void double_even();

        // 6.2) double_negative(): dopo ogni negativo, un clone. RICORSIVO.
        //   [-1 2 -3 4] → [-1 -1 2 -3 -3 4]
        void double_negative();

        // 6.3) triplica_positivi(): dopo ogni positivo, DUE cloni. RICORSIVO.
        //   [1 -2 3] → [1 1 1 -2 3 3 3]
        void triplica_positivi();

        // 6.4) duplicate_all(): ogni nodo appare due volte. RICORSIVO.
        //   [1 2 3] → [1 1 2 2 3 3]
        void duplicate_all();

        // 6.5) insert_after_each(int v): dopo OGNI nodo inserisce un nodo con valore v.
        //   [1 2 3], insert_after_each(0) → [1 0 2 0 3 0]
        void insert_after_each(int v);

        // 6.6) insert_separator(int v): inserisce v TRA ogni coppia di nodi
        //      adiacenti (non dopo l'ultimo).
        //   [1 2 3], insert_separator(0) → [1 0 2 0 3]
        //   [1]                          → [1]
        //   []                           → []
        void insert_separator(int v);


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 7 — TRASFORMAZIONI STRUTTURALI (ricorsive)
        // ══════════════════════════════════════════════════════════════════

        // 7.1) flip(): reverse in-place. RICORSIVO.
        void flip();

        // 7.2) rotate_left(int k): sposta i primi k elementi in fondo (in ordine).
        //   [1 2 3 4 5], rotate_left(2) → [3 4 5 1 2]
        //   k viene normalizzato modulo size() se maggiore.
        void rotate_left(int k);

        // 7.3) rotate_right(int k): simmetrico.
        //   [1 2 3 4 5], rotate_right(2) → [4 5 1 2 3]
        void rotate_right(int k);

        // 7.4) swap_ends(): scambia valori di primo e ultimo nodo.
        void swap_ends();

        // 7.5) swap_pairs(): scambia gli elementi a coppie (solo valori).
        //   [1 2 3 4 5] → [2 1 4 3 5]
        void swap_pairs();

        // 7.6) swap_pairs_nodes(): come sopra ma manipolando i PUNTATORI
        //      (non i valori). Più tosto. RICORSIVO consigliato.
        void swap_pairs_nodes();

        // 7.7) split_at(int pos, mylist& other): sposta in other i nodi
        //      a partire dalla posizione pos compresa.
        //   [1 2 3 4 5], split_at(2, other)
        //     → this = [1 2],  other = [3 4 5]
        //   pos > size() → throw.
        void split_at(int pos, mylist& other);

        // 7.8) split_even_odd(mylist& evens, mylist& odds) const:
        //      NON modifica *this; popola le due liste.
        //   [1 2 3 4 5] → evens = [2 4], odds = [1 3 5]
        void split_even_odd(mylist& evens, mylist& odds) const;


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 8 — ORDINAMENTO / PROPRIETÀ D'ORDINE
        // ══════════════════════════════════════════════════════════════════

        // 8.1) is_sorted(): crescente non strettamente. RICORSIVO.
        bool is_sorted() const;

        // 8.2) is_sorted_strict(): crescente strettamente (nessun duplicato).
        //   [1 2 3] → true
        //   [1 1 2] → false
        bool is_sorted_strict() const;

        // 8.3) is_palindrome(): stessa sequenza letta avanti o indietro.
        //   [1 2 3 2 1] → true
        //   [1 2]       → false
        //   [7]         → true
        //   []          → true
        bool is_palindrome() const;

        // 8.4) insert_sorted(int v): inserisce in posizione ordinata
        //      (assume lista già ordinata).
        void insert_sorted(int v);

        // 8.5) merge_sorted(const mylist& other) const: ritorna NUOVA lista
        //      ordinata unendo *this e other (entrambe ordinate).
        mylist merge_sorted(const mylist& other) const;

        // 8.6) sort(): ordina la lista in-place (qualsiasi algoritmo; per linked
        //      list, insertion sort o bubble sul valore sono i più semplici).
        void sort();


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 9 — CONFRONTO DI LISTE (ricorsivi)
        // ══════════════════════════════════════════════════════════════════

        // 9.1) equal(const mylist& other) const: uguaglianza elementare. RICORSIVO.
        bool equal(const mylist& other) const;

        // 9.2) is_prefix_of(const mylist& other) const: *this è prefisso di other?
        //   [1 2] is_prefix_of [1 2 3 4] → true
        //   [1 3] is_prefix_of [1 2 3]   → false
        //   []    is_prefix_of [qualsiasi] → true
        bool is_prefix_of(const mylist& other) const;

        // 9.3) is_suffix_of(const mylist& other) const: *this è suffisso?
        //   [3 4] is_suffix_of [1 2 3 4] → true
        bool is_suffix_of(const mylist& other) const;

        // 9.4) contains_sublist(const mylist& sub) const: la sottosequenza sub
        //      compare contigua in *this?
        //   [1 2 3 4 5] contains [2 3 4] → true
        //   [1 2 3 4 5] contains [2 4]   → false (non contigui)
        bool contains_sublist(const mylist& sub) const;


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 10 — "SUGLI INDICI PARI/DISPARI" (classici esame)
        // ══════════════════════════════════════════════════════════════════

        // 10.1) sum_even_positions(): somma dei valori in posizione 0, 2, 4, …
        //   [10 20 30 40 50] → 10 + 30 + 50 = 90
        int sum_even_positions() const;

        // 10.2) remove_odd_positions(): rimuove i nodi in posizione 1, 3, 5, …
        //   [10 20 30 40 50] → [10 30 50]
        void remove_odd_positions();

        // 10.3) reverse_from(int pos): inverte SOLO il suffisso che parte da pos.
        //   [1 2 3 4 5], reverse_from(2) → [1 2 5 4 3]
        void reverse_from(int pos);


        // ══════════════════════════════════════════════════════════════════
        //   PATTERN 11 — MIX / COMBO (esercizi "cattivi")
        // ══════════════════════════════════════════════════════════════════

        // 11.1) shift_values(int k): somma k a ogni valore.
        //   [1 2 3], shift_values(10) → [11 12 13]
        void shift_values(int k);

        // 11.2) abs_values(): sostituisce ogni valore col suo valore assoluto.
        //   [-1 2 -3] → [1 2 3]
        void abs_values();

        // 11.3) compact_zeros(): sostituisce ogni run di zeri consecutivi
        //       con UN solo zero.
        //   [1 0 0 0 2 0 3 0 0] → [1 0 2 0 3 0]
        void compact_zeros();

        // 11.4) second_max() const: ritorna il secondo valore più grande
        //       (valori DISTINTI: se max è 7 e la lista è [7 7 3], second_max = 3).
        //       Throw se meno di due valori distinti.
        //   [3 1 7 2 5]   → 5
        //   [7 7 7]       → throw
        //   [7 3]         → 3
        int second_max() const;

        // 11.5) kth_smallest(int k) const: k-esimo valore più piccolo
        //       (k 0-based, con duplicati che contano).
        //   [3 1 4 1 5 9 2 6], kth_smallest(0) → 1
        //                      kth_smallest(1) → 1
        //                      kth_smallest(2) → 2
        //       Throw se k fuori range.
        int kth_smallest(int k) const;

        // 11.6) move_zeros_to_end(): sposta tutti gli zeri in coda,
        //       preservando l'ordine relativo dei non-zero.
        //   [1 0 2 0 3] → [1 2 3 0 0]
        void move_zeros_to_end();

        // 11.7) partition(int pivot): riorganizza la lista in modo che prima
        //       vengano tutti i valori < pivot, poi ≥ pivot; ordine relativo
        //       preservato dentro ogni gruppo.
        //   [3 1 4 1 5 9 2 6], partition(4)
        //     → [3 1 1 2 | 4 5 9 6]  (la barra è solo illustrativa)
        void partition(int pivot);


    private:
        node* head;
        int size_rec(const node*cur) const;
        bool is_equal(const node* p1, const node* p2) const;
        int rss_helper(node*& cur, int s);
        int ruts_helper(node*& cur, int s);
        // ── Helper privati: li aggiungi tu. Suggerimenti ───────────────────
        // Ricorsivi con node* e basta:
        //   size_rec, count_rec, sum_rec, max_rec, min_rec, is_sorted_rec,
        //   is_palindrome_rec (serve anche un puntatore "da destra"),
        //   count_if_even_rec, count_if_negative_rec, find_first_rec,
        //   equal_rec, is_prefix_of_rec
        //
        // Ricorsivi con node*& (modificano la struttura):
        //   flip_rec, double_even_rec, double_negative_rec,
        //   triplica_positivi_rec, duplicate_all_rec, insert_after_each_rec,
        //   remove_all_rec, swap_pairs_nodes_rec
        //
        // Ricorsivi che ritornano un accumulatore (pattern "torna su"):
        //   remove_up_to_sum_rec(int s, node*& cur) → int (suffix sum)
        //   remove_suffix_sum_rec(int s, node*& cur) → int
        //
        // Con output parameter:
        //   countfrom0_rec(node*, int&) → bool
        //   count_before_neg (iterativo va bene)
        //   count_after_max: trova il max, poi scansiona
        //
        // Utility che aiutano:
        //   node* find_last_node() const; // ultimo nodo
        //   node* node_at(int pos) const; // nodo in posizione pos (o nullptr)
};
/*======big 3 ======*/ 
  mylist::mylist(){
    head = nullptr;
  }
  mylist::~mylist(){
    while(head != nullptr){
        node*tmp = head; 
        head = head->next;
        delete tmp;
    }
  }

  mylist::mylist(const mylist& other){
    head = nullptr; 
    node* cur = nullptr;
    node * cur_other = other.head;
    while(cur_other !=nullptr){
        node * nuova = new node{cur_other->val,nullptr};
        if(head == nullptr){
                head = nuova;
                cur = nuova;
        }
            else{
                cur->next = nuova;
                cur = cur->next;
            }
            cur_other = cur_other->next;
    } 
  }




/*======operazioni manipolazione=======*/ 
void mylist::push_front(int e){
    node * nuova = new node {e,nullptr};
    head = nuova;
}


void mylist::push_back(int e){
    node* nuovo = new node{e,nullptr};
    if(head == nullptr){
        head = nuovo;
    }else{

    node * cur = head;
    while(cur ->next!= nullptr){
        cur = cur->next;
    }
    cur->next = nuovo;
}
}


   void mylist:: print() const{
    node* cur = head; 
    while(cur!= nullptr){
        std::cout<< cur->val<<std::endl;
        cur = cur->next;
    }
   }

   int mylist::size() const{
        size_rec(head);
   }
   int mylist::size_rec(const node*cur) const{
        if(cur == nullptr)
            return 0;
        else 
            return 1 +size_rec(cur->next);
   }

   int mylist::size_rec(const node*cur) const{
        if(cur == nullptr)
            return 0;
        else 
            return 1 +size_rec(cur->next);
   }
int&  mylist::at(int pos){
    node * cur = head; 
    for(int i = 0; cur != nullptr;i++)
        cur = cur->next;
    if(cur == nullptr)
        throw std::out_of_range("OOR ERROR");
    return cur->val;        
 }

const int&  mylist::at(int pos) const{
    node * cur = head; 
    for(int i = 0; cur != nullptr;i++)
        cur = cur->next;
    if(cur == nullptr)
        throw std::out_of_range("OOR ERROR");
    return cur->val;        
 }







/*====operatori====*/ 
 mylist& mylist::operator=(const mylist& other){
    if(this == &other) return *this;
    while(head != nullptr){
        node * tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    node* cur = head; 
    node* cur_o = other.head;

    while(cur_o != nullptr){
        node * nuovo = new node{cur_o->val,nullptr};
        if(head == nullptr){
            head = nuovo; 
            cur = nuovo; 
        }else{
            cur->next = nuovo;
            cur = cur->next;
        }
        cur_o = cur_o->next;
    }
    return *this;
 }






  bool mylist::operator==(const mylist& other) const{
    return is_equal(this->head,other.head);
  }



bool mylist::is_equal(const node* p1, const node* p2) const{
    if(p1== nullptr && p2==nullptr)
        return  true; 
    else 
        if(p1== nullptr || p2==nullptr)
            return false;
        else 
            if(p1->val != p2->val)
                return false;
            return is_equal(p1->next,p2->next);
}



bool mylist:: operator!=(const mylist& other) const{
return!(*this == other);
}






void mylist::remove_greater_than(int k){
    while(head != nullptr && head->val>k){
         node *tmp = head;
         head = head->next;
         delete tmp;
    }
    if(head != nullptr){
        node * prev = head;
        while(prev->next != nullptr){
            if(prev->val > k){
                node * tmp = prev->next;
                prev->next= tmp->next;
                delete tmp;
            } else{

                prev = prev->next;
            }
        }
    }
}

        // 3.6) remove_in_range(int lo, int hi): rimuove i valori v con lo ≤ v ≤ hi.
        //   [1 5 2 8 3], remove_in_range(2, 5) → [1 8]
void mylist::remove_in_range(int lo, int hi){
    while(head != nullptr &&  head->val >= lo && head->val <= hi){
        node * tmp = head;
        head = head->next;
        delete tmp;
    }
    if(head!= nullptr){
        node * prev = head;
        while(prev->next != nullptr){
            if(prev->next->val >= lo&& prev->next->val <= hi){
                    node * tmp = prev->next;
                    prev->next = tmp->next;
                    delete tmp;
            } else{
                prev = prev->next;
            }

        }
    }
}

void mylist::remove_prefix_sum(int s){
    int cur_s= 0 ; 
    while(head != nullptr && (cur_s+head->val)<=s){
        cur_s += head->val;
        node * tmp = head;
        head = head->next;
        delete tmp;
    }
}

void mylist::remove_suffix_sum(int s){
    rss_helper(head, s);
}

int mylist:: rss_helper (node*& cur, int s){
    if(cur == nullptr) return 0;
    int suffix_s = rss_helper(cur->next,s);

    if(cur->next == nullptr && (suffix_s+cur->val)<= s) {
        int val = cur->val;
        delete cur;
        cur = nullptr;
        return suffix_s+val;
    }
    return suffix_s+cur->val;
}



void mylist::remove_up_to_sum(int s){
ruts_helper(head,s);
}


int mylist::ruts_helper(node*& cur, int s){
    if(cur== nullptr) return 0; 
    int sum_after = ruts_helper(cur->next,s);
    int my_suffix_s = cur->val +sum_after;

    if(my_suffix_s <=s){
        node *tmp = cur; 
        cur = cur->next;
        delete tmp;
    }
    return my_suffix_s; 
}


int mylist::count_if_even() const {
    // Passo la 'head' all'helper privato
    return count_if_even_helper(head); 
}

int mylist::count_if_negative() const {
    return count_if_negative_helper(head);
}

int mylist::find_first(int e) const {
    // Passo la testa, il valore da cercare e l'indice di partenza (0)
    return find_first_helper(head, e, 0);
}

int mylist::find_last(int e) const {
    // Anche qui parto da 0, la logica "ultimo" verrà gestita dal ritorno dell'helper
    return find_last_helper(head, e, 0);
}

// 1.4 FIND FIRST
int find_first_helper(node* cur, int e, int index) const {
    if (cur == nullptr) return -1;
    if (cur->val == e) return index;
    return find_first_helper(cur->next, e, index + 1);
}

// 1.5 FIND LAST (Versione Backtracking)
int find_last_helper(node* cur, int e, int index) const {
    if (cur == nullptr) return -1;

    // Vai avanti fino alla fine
    int res_after = find_last_helper(cur->next, e, index + 1);

    // Se qualcuno dopo di me l'ha trovato, quella è l'ultima posizione
    if (res_after != -1) return res_after;

    // Altrimenti, controlla se sono io l'ultima spiaggia
    if (cur->val == e) return index;

    return -1;
}





// --- Trasformazioni Strutturali ---

void mylist::flip() {
    if (!head || !head->next) return;
    node* res = flip_helper(head);
    head->next = nullptr; // La vecchia testa ora è la coda
    head = res;
}
mylist::node* mylist::flip_helper(node* cur) {
    if (!cur->next) return cur;
    node* new_head = flip_helper(cur->next);
    cur->next->next = cur;
    return new_head;
}


void mylist::rotate_left(int k) {
    int n = size();
    if (n == 0 || (k % n) == 0) return;
    k %= n;
    node* cur = head;
    for (int i = 0; i < k - 1; ++i) cur = cur->next;
    node* new_head = cur->next;
    node* tail = new_head;
    cur->next = nullptr;
    while (tail->next) tail = tail->next;
    tail->next = head;
    head = new_head;
}

void mylist::swap_ends() {
    if (!head || !head->next) return;
    node* cur = head;
    while (cur->next) cur = cur->next;
    int tmp = head->val;
    head->val = cur->val;
    cur->val = tmp;
}


void mylist::swap_pairs_nodes() { head = spn_helper(head); }
mylist::node* mylist::spn_helper(node* f) {
    if (!f || !f->next) return f;
    node* s = f->next;
    f->next = spn_helper(s->next);
    s->next = f;
    return s;
}

void mylist::split_at(int pos, mylist& other) {
    if (pos == 0) { other.~mylist(); other.head = head; head = nullptr; return; }
    node* cur = head;
    for (int i = 0; i < pos - 1 && cur; ++i) cur = cur->next;
    if (!cur) throw std::out_of_range("Posizione non valida");
    other.~mylist();
    other.head = cur->next;
    cur->next = nullptr;
}

void mylist::split_even_odd(mylist& evens, mylist& odds) const {
    evens.~mylist(); odds.~mylist();
    node* cur = head;
    while (cur) {
        if (cur->val % 2 == 0) evens.push_back(cur->val);
        else odds.push_back(cur->val);
        cur = cur->next;
    }
}






  // ═══════════════════════════════════════════════════════════════════════════
//   MAIN DI TEST per la classe `mylist`
//   ---------------------------------------------------------------
//   Come usarlo:
//     1) Incolla sopra questo main la tua implementazione di `mylist`
//        (con i metodi/operatori definiti nella consegna).
//     2) Compila: g++ -std=c++17 -Wall -Wextra -o mylist mylist.cpp
//     3) Esegui:  ./mylist
//
//   Suggerimento: se non hai implementato ANCORA tutti i metodi, commenta
//   i blocchi di test relativi (sono separati da ───── linee ─────).
// ═══════════════════════════════════════════════════════════════════════════


// #include "mylist.h"   // oppure incolla qui la classe

// Helper per costruire rapidamente liste nei test
mylist make_list(std::initializer_list<int> xs) {
    mylist l;
    for (int x : xs) l.push_back(x);
    return l;
}

// Helper per stampare un header di sezione
void section(const string& name) {
    cout << "\n═══════════════════════════════════════════════════════════════\n";
    cout << "   " << name << "\n";
    cout << "═══════════════════════════════════════════════════════════════\n";
}

int main() {
    cout << "############ TEST mylist ############\n";

    // ═══════════════════════════════════════════════════════════════════════
    //   BASIC OPS
    // ═══════════════════════════════════════════════════════════════════════
    section("BASIC OPS: push_front / push_back / print / size / is_present / at");
    {
        mylist l;
        l.push_back(1); l.push_back(2); l.push_back(3);
        l.push_front(0);
        cout << "Atteso: 0 1 2 3\nOttenuto: "; l.print();
        cout << "size() atteso 4, ottenuto: " << l.size() << "\n";
        cout << "is_present(2) atteso 1, ottenuto: " << l.is_present(2) << "\n";
        cout << "is_present(99) atteso 0, ottenuto: " << l.is_present(99) << "\n";
        cout << "at(0) atteso 0, ottenuto: " << l.at(0) << "\n";
        cout << "at(3) atteso 3, ottenuto: " << l.at(3) << "\n";
        l.at(1) = 99;
        cout << "Dopo at(1)=99, atteso: 0 99 2 3\nOttenuto: "; l.print();
        try { l.at(100); }
        catch (std::out_of_range& e) { cout << "at(100) -> throw OK: " << e.what() << "\n"; }

        mylist vuota;
        cout << "size() vuota atteso 0, ottenuto: " << vuota.size() << "\n";
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   OPERATOR OVERLOAD
    // ═══════════════════════════════════════════════════════════════════════
    section("OPERATOR: copy ctor / operator=");
    {
        mylist a = make_list({1,2,3,4});
        mylist b(a);                      // copy ctor
        cout << "a: "; a.print();
        cout << "b (copia): "; b.print();
        b.push_back(99);
        cout << "Dopo push su b, a invariata: "; a.print();
        cout << "b: "; b.print();

        mylist c;
        c.push_back(1000);
        c = a;                            // operator=
        cout << "Dopo c = a, c: "; c.print();
        c = c;                            // self-assignment
        cout << "Dopo c = c, c: "; c.print();
    }

    section("OPERATOR: == != < <= > >=");
    {
        mylist a = make_list({1,2,3});
        mylist b = make_list({1,2,3});
        mylist c = make_list({1,2,4});
        mylist d = make_list({1,2});     // prefisso di a
        mylist v;                          // vuota

        cout << "[1 2 3] == [1 2 3] atteso 1, ottenuto " << (a == b) << "\n";
        cout << "[1 2 3] != [1 2 4] atteso 1, ottenuto " << (a != c) << "\n";
        cout << "[1 2 3] <  [1 2 4] atteso 1, ottenuto " << (a <  c) << "\n";
        cout << "[1 2]   <  [1 2 3] atteso 1, ottenuto " << (d <  a) << "\n";
        cout << "[1 2 3] <= [1 2 3] atteso 1, ottenuto " << (a <= b) << "\n";
        cout << "[1 2 4] >  [1 2 3] atteso 1, ottenuto " << (c >  a) << "\n";
        cout << "[] < [1] atteso 1, ottenuto " << (v < d) << "\n";
        cout << "[2] < [1 9 9] atteso 0, ottenuto " << (make_list({2}) < make_list({1,9,9})) << "\n";
    }

    section("OPERATOR: + - * & |");
    {
        mylist a = make_list({1,2,3,4});
        mylist b = make_list({3,4,5,6});
        (a + b).print();  cout << "  (atteso: 1 2 3 4 3 4 5 6 — concatenazione)\n";
        (a - b).print();  cout << "  (atteso: 1 2 — differenza)\n";
        (a * b).print();  cout << "  (atteso: 3 4 — intersezione set)\n";

        mylist x = make_list({1,1,2,2,3});
        mylist y = make_list({1,2,2,4});
        (x & y).print();  cout << "  (atteso: 1 2 2 — intersezione con molteplicita')\n";

        mylist p = make_list({1,2,3});
        mylist q = make_list({2,3,4});
        (p | q).print();  cout << "  (atteso: 1 2 3 4 — unione set)\n";
    }

    section("OPERATOR: += -=");
    {
        mylist a = make_list({1,2,3});
        mylist b = make_list({10,20});
        a += b;
        cout << "[1 2 3] += [10 20] atteso: 1 2 3 10 20\nOttenuto: "; a.print();

        mylist c = make_list({1,2,3});
        c += 99;
        cout << "[1 2 3] += 99 atteso: 1 2 3 99\nOttenuto: "; c.print();

        mylist d = make_list({1,2,3,2,4});
        d -= 2;
        cout << "[1 2 3 2 4] -= 2 (prima occ.) atteso: 1 3 2 4\nOttenuto: "; d.print();

        mylist e = make_list({1,2,3,4,5});
        mylist tog = make_list({2,4});
        e -= tog;
        cout << "[1 2 3 4 5] -= [2 4] atteso: 1 3 5\nOttenuto: "; e.print();
    }

    section("OPERATOR: [] (senza check)");
    {
        mylist a = make_list({10,20,30});
        cout << "a[0] atteso 10, ottenuto " << a[0] << "\n";
        cout << "a[2] atteso 30, ottenuto " << a[2] << "\n";
        a[1] = 77;
        cout << "Dopo a[1]=77, atteso: 10 77 30\nOttenuto: "; a.print();
    }

    section("OPERATOR: << (stream)");
    {
        mylist a = make_list({1,2,3});
        cout << "Atteso: [1 2 3]\nOttenuto: " << a << "\n";
        mylist v;
        cout << "Atteso (vuota): []\nOttenuto: " << v << "\n";
    }

    section("OPERATOR: ++ -- (prefix e postfix)");
    {
        mylist a = make_list({1,2,3});
        ++a;
        cout << "Dopo ++a atteso: 2 3 4\nOttenuto: "; a.print();
        mylist old = a++;
        cout << "Dopo a++, old atteso: 2 3 4\nOttenuto: "; old.print();
        cout << "a atteso: 3 4 5\nOttenuto: "; a.print();
        --a;
        cout << "Dopo --a atteso: 2 3 4\nOttenuto: "; a.print();
    }

    section("OPERATOR: - unario, operator bool");
    {
        mylist a = make_list({1,-2,3});
        (-a).print();  cout << "  (atteso: -1 2 -3)\n";

        mylist v;
        if (a)  cout << "if(a) vero OK\n";
        if (!v) cout << "if(!v) vero OK (lista vuota)\n";
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 1 — CONTEGGIO / RICERCA
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 1: count / count_if_even / count_if_negative / find_first / find_last");
    {
        mylist a = make_list({1,2,3,2,4,2});
        cout << "[1 2 3 2 4 2] count(2) atteso 3, ottenuto " << a.count(2) << "\n";
        cout << "count(99) atteso 0, ottenuto " << a.count(99) << "\n";
        mylist v;
        cout << "[] count(5) atteso 0, ottenuto " << v.count(5) << "\n";

        mylist b = make_list({1,2,3,4,5});
        cout << "count_if_even atteso 2, ottenuto " << b.count_if_even() << "\n";

        mylist c = make_list({-1,2,-3,-4,5});
        cout << "count_if_negative atteso 3, ottenuto " << c.count_if_negative() << "\n";

        mylist d = make_list({10,20,30,20});
        cout << "find_first(20) atteso 1, ottenuto " << d.find_first(20) << "\n";
        cout << "find_first(99) atteso -1, ottenuto " << d.find_first(99) << "\n";
        cout << "find_last(20)  atteso 3, ottenuto "  << d.find_last(20)  << "\n";
        cout << "find_last(99)  atteso -1, ottenuto " << d.find_last(99) << "\n";
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 2 — AGGREGATI
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 2: min / max / sum / avg / sum_even / sum_positives / product");
    {
        mylist a = make_list({3,1,7,2,5});
        cout << "min atteso 1, ottenuto " << a.min() << "\n";
        cout << "max atteso 7, ottenuto " << a.max() << "\n";
        cout << "sum atteso 18, ottenuto " << a.sum() << "\n";
        cout << "avg atteso 3.6, ottenuto " << a.avg() << "\n";

        try { mylist v; v.min(); }
        catch (std::out_of_range& e) { cout << "min su [] -> throw OK: " << e.what() << "\n"; }
        try { mylist v; v.max(); }
        catch (std::out_of_range& e) { cout << "max su [] -> throw OK: " << e.what() << "\n"; }

        mylist b = make_list({1,2,3,4,5});
        cout << "sum_even atteso 6, ottenuto " << b.sum_even() << "\n";

        mylist c = make_list({-1,2,-3,4});
        cout << "sum_positives atteso 6, ottenuto " << c.sum_positives() << "\n";

        mylist d = make_list({2,3,4});
        cout << "product atteso 24, ottenuto " << d.product() << "\n";
        mylist v;
        cout << "product [] atteso 1, ottenuto " << v.product() << "\n";
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 3 — RIMOZIONE CONDIZIONALE
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 3: remove_all / remove_even / remove_odd / remove_negative");
    {
        mylist a = make_list({1,5,2,5,5,3});
        a.remove_all(5);
        cout << "[1 5 2 5 5 3] remove_all(5) atteso: 1 2 3\nOttenuto: "; a.print();

        mylist b = make_list({5,5,5});
        b.remove_all(5);
        cout << "[5 5 5] remove_all(5) atteso: (vuota)\nOttenuto: "; b.print();

        mylist c = make_list({1,2,3,4,5});
        c.remove_even();
        cout << "[1 2 3 4 5] remove_even atteso: 1 3 5\nOttenuto: "; c.print();

        mylist d = make_list({-3,-2,-1,0,1,2,3});
        d.remove_odd();
        cout << "[-3 -2 -1 0 1 2 3] remove_odd atteso: -2 0 2\nOttenuto: "; d.print();

        mylist e = make_list({-1,2,-3,4,-5});
        e.remove_negative();
        cout << "[-1 2 -3 4 -5] remove_negative atteso: 2 4\nOttenuto: "; e.print();
    }

    section("PATTERN 3: remove_greater_than / remove_in_range / remove_at");
    {
        mylist a = make_list({1,5,2,8,3});
        a.remove_greater_than(4);
        cout << "remove_greater_than(4) atteso: 1 2 3\nOttenuto: "; a.print();

        mylist b = make_list({1,5,2,8,3});
        b.remove_in_range(2,5);
        cout << "remove_in_range(2,5) atteso: 1 8\nOttenuto: "; b.print();

        mylist c = make_list({10,20,30,40});
        c.remove_at(0);
        cout << "remove_at(0) atteso: 20 30 40\nOttenuto: "; c.print();
        c.remove_at(1);
        cout << "remove_at(1) atteso: 20 40\nOttenuto: "; c.print();
        try { c.remove_at(99); }
        catch (std::out_of_range& e) { cout << "remove_at(99) -> throw OK\n"; }
    }

    section("PATTERN 3: remove_duplicates / remove_duplicates_sorted");
    {
        mylist a = make_list({1,2,1,3,2,4});
        a.remove_duplicates();
        cout << "remove_duplicates atteso: 1 2 3 4\nOttenuto: "; a.print();

        mylist b = make_list({5,5,5,5});
        b.remove_duplicates();
        cout << "[5 5 5 5] dup atteso: 5\nOttenuto: "; b.print();

        mylist c = make_list({1,1,2,3,3,3,4});
        c.remove_duplicates_sorted();
        cout << "remove_duplicates_sorted atteso: 1 2 3 4\nOttenuto: "; c.print();
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 4 — PREFIX / SUFFIX SUM
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 4: remove_prefix_sum / remove_suffix_sum / remove_up_to_sum");
    {
        mylist a = make_list({1,2,3,4,5});
        a.remove_prefix_sum(5);
        cout << "[1 2 3 4 5] rps(5) atteso: 3 4 5\nOttenuto: "; a.print();

        mylist b = make_list({1,2,3});
        b.remove_prefix_sum(100);
        cout << "[1 2 3] rps(100) atteso: (vuota)\nOttenuto: "; b.print();

        mylist c = make_list({1,2,3});
        c.remove_prefix_sum(0);
        cout << "[1 2 3] rps(0) atteso: 1 2 3\nOttenuto: "; c.print();

        mylist d = make_list({1,2,3,4,5});
        d.remove_suffix_sum(9);
        cout << "[1 2 3 4 5] rss(9) atteso: 1 2 3 4\nOttenuto: "; d.print();

        mylist e = make_list({3,1,2,4,5});
        e.remove_up_to_sum(6);
        cout << "[3 1 2 4 5] r_up_to_sum(6) atteso: 3 1 2 4\nOttenuto: "; e.print();

        mylist f = make_list({1,2,3});
        f.remove_up_to_sum(100);
        cout << "[1 2 3] r_up_to_sum(100) atteso: (vuota)\nOttenuto: "; f.print();
    }

    section("PATTERN 4: remove_prefix_product / keep_prefix_sum");
    {
        mylist a = make_list({1,2,3,4});
        a.remove_prefix_product(6);
        cout << "[1 2 3 4] rpp(6) atteso: 3 4\nOttenuto: "; a.print();

        mylist b = make_list({1,2,3,4,5});
        b.keep_prefix_sum(6);
        cout << "[1 2 3 4 5] kps(6) atteso: 1 2 3\nOttenuto: "; b.print();

        mylist c = make_list({10,20,30});
        c.keep_prefix_sum(5);
        cout << "[10 20 30] kps(5) atteso: (vuota)\nOttenuto: "; c.print();
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 5 — OUTPUT PARAMETER
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 5: countfrom0 / count_before_neg / count_after_max / count_between_zeros / find_with_index");
    {
        int cnt;
        mylist a = make_list({3,0,5,2});
        cout << "[3 0 5 2] countfrom0 atteso: 1, 2 — ottenuto: "
             << a.countfrom0(cnt) << ", " << cnt << "\n";

        mylist b = make_list({1,0,2,0,7});
        cout << "[1 0 2 0 7] countfrom0 atteso: 1, 1 — ottenuto: "
             << b.countfrom0(cnt) << ", " << cnt << "\n";

        mylist c = make_list({1,2,3});
        cout << "[1 2 3] countfrom0 atteso: 0, 3 — ottenuto: "
             << c.countfrom0(cnt) << ", " << cnt << "\n";

        mylist d = make_list({1,2,-3,4});
        cout << "[1 2 -3 4] count_before_neg atteso: 1, 2 — ottenuto: "
             << d.count_before_neg(cnt) << ", " << cnt << "\n";

        mylist e = make_list({-1,2,3});
        cout << "[-1 2 3] count_before_neg atteso: 1, 0 — ottenuto: "
             << e.count_before_neg(cnt) << ", " << cnt << "\n";

        mylist f = make_list({1,2,3});
        cout << "[1 2 3] count_before_neg atteso: 0, 3 — ottenuto: "
             << f.count_before_neg(cnt) << ", " << cnt << "\n";

        mylist g = make_list({1,5,2,5,3});
        cout << "[1 5 2 5 3] count_after_max atteso: 1, 3 — ottenuto: "
             << g.count_after_max(cnt) << ", " << cnt << "\n";

        mylist h = make_list({1,2,3});
        cout << "[1 2 3] count_after_max atteso: 1, 0 — ottenuto: "
             << h.count_after_max(cnt) << ", " << cnt << "\n";

        mylist vv;
        cout << "[] count_after_max atteso: 0, 0 — ottenuto: "
             << vv.count_after_max(cnt) << ", " << cnt << "\n";

        mylist i = make_list({1,0,2,3,0,4});
        cout << "[1 0 2 3 0 4] count_between_zeros atteso: 1, 2 — ottenuto: "
             << i.count_between_zeros(cnt) << ", " << cnt << "\n";

        mylist j = make_list({1,0,2});
        cout << "[1 0 2] count_between_zeros atteso: 0, 0 — ottenuto: "
             << j.count_between_zeros(cnt) << ", " << cnt << "\n";

        mylist k = make_list({10,20,30,40});
        int idx;
        cout << "find_with_index(30) atteso: 1, 2 — ottenuto: "
             << k.find_with_index(30, idx) << ", " << idx << "\n";
        cout << "find_with_index(99) atteso: 0, -1 — ottenuto: "
             << k.find_with_index(99, idx) << ", " << idx << "\n";
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 6 — DUPLICAZIONE / INSERIMENTO
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 6: double_even / double_negative / triplica_positivi / duplicate_all");
    {
        mylist a = make_list({2,7,0,5});
        a.double_even();
        cout << "[2 7 0 5] double_even atteso: 2 2 7 0 0 5\nOttenuto: "; a.print();

        mylist b = make_list({-1,2,-3,4});
        b.double_negative();
        cout << "[-1 2 -3 4] double_negative atteso: -1 -1 2 -3 -3 4\nOttenuto: "; b.print();

        mylist c = make_list({1,-2,3});
        c.triplica_positivi();
        cout << "[1 -2 3] triplica_positivi atteso: 1 1 1 -2 3 3 3\nOttenuto: "; c.print();

        mylist d = make_list({0,1});
        d.triplica_positivi();
        cout << "[0 1] triplica_positivi atteso: 0 1 1 1\nOttenuto: "; d.print();

        mylist e = make_list({1,2,3});
        e.duplicate_all();
        cout << "[1 2 3] duplicate_all atteso: 1 1 2 2 3 3\nOttenuto: "; e.print();
    }

    section("PATTERN 6: insert_after_each / insert_separator");
    {
        mylist a = make_list({1,2,3});
        a.insert_after_each(0);
        cout << "[1 2 3] insert_after_each(0) atteso: 1 0 2 0 3 0\nOttenuto: "; a.print();

        mylist b = make_list({1,2,3});
        b.insert_separator(0);
        cout << "[1 2 3] insert_separator(0) atteso: 1 0 2 0 3\nOttenuto: "; b.print();

        mylist c = make_list({1});
        c.insert_separator(0);
        cout << "[1] insert_separator(0) atteso: 1\nOttenuto: "; c.print();

        mylist v;
        v.insert_separator(0);
        cout << "[] insert_separator(0) atteso: (vuota)\nOttenuto: "; v.print();
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 7 — TRASFORMAZIONI STRUTTURALI
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 7: flip / rotate_left / rotate_right / swap_ends / swap_pairs");
    {
        mylist a = make_list({1,2,3,4,5});
        a.flip();
        cout << "[1 2 3 4 5] flip atteso: 5 4 3 2 1\nOttenuto: "; a.print();

        mylist b = make_list({1,2,3,4,5});
        b.rotate_left(2);
        cout << "[1 2 3 4 5] rotate_left(2) atteso: 3 4 5 1 2\nOttenuto: "; b.print();

        mylist c = make_list({1,2,3,4,5});
        c.rotate_right(2);
        cout << "[1 2 3 4 5] rotate_right(2) atteso: 4 5 1 2 3\nOttenuto: "; c.print();

        mylist d = make_list({1,2,3,4,5});
        d.swap_ends();
        cout << "[1 2 3 4 5] swap_ends atteso: 5 2 3 4 1\nOttenuto: "; d.print();

        mylist e = make_list({1,2,3,4,5});
        e.swap_pairs();
        cout << "[1 2 3 4 5] swap_pairs atteso: 2 1 4 3 5\nOttenuto: "; e.print();

        mylist f = make_list({1,2,3,4,5,6});
        f.swap_pairs_nodes();
        cout << "[1 2 3 4 5 6] swap_pairs_nodes atteso: 2 1 4 3 6 5\nOttenuto: "; f.print();
    }

    section("PATTERN 7: split_at / split_even_odd");
    {
        mylist a = make_list({1,2,3,4,5});
        mylist other;
        a.split_at(2, other);
        cout << "split_at(2): this atteso: 1 2\nOttenuto: "; a.print();
        cout << "              other atteso: 3 4 5\nOttenuto: "; other.print();

        mylist b = make_list({1,2,3,4,5});
        mylist evens, odds;
        b.split_even_odd(evens, odds);
        cout << "split_even_odd: evens atteso 2 4, ottenuto: "; evens.print();
        cout << "                odds  atteso 1 3 5, ottenuto: "; odds.print();
        cout << "                this invariata: "; b.print();
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 8 — ORDINAMENTO
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 8: is_sorted / is_sorted_strict / is_palindrome / insert_sorted / merge_sorted / sort");
    {
        cout << "[1 2 3 5] is_sorted atteso 1, ottenuto " << make_list({1,2,3,5}).is_sorted() << "\n";
        cout << "[1 1 2 3] is_sorted atteso 1, ottenuto " << make_list({1,1,2,3}).is_sorted() << "\n";
        cout << "[1 3 2]   is_sorted atteso 0, ottenuto " << make_list({1,3,2}).is_sorted()   << "\n";
        cout << "[]        is_sorted atteso 1, ottenuto " << mylist().is_sorted() << "\n";

        cout << "[1 2 3]   is_sorted_strict atteso 1, ottenuto " << make_list({1,2,3}).is_sorted_strict() << "\n";
        cout << "[1 1 2]   is_sorted_strict atteso 0, ottenuto " << make_list({1,1,2}).is_sorted_strict() << "\n";

        cout << "[1 2 3 2 1] is_palindrome atteso 1, ottenuto " << make_list({1,2,3,2,1}).is_palindrome() << "\n";
        cout << "[1 2]       is_palindrome atteso 0, ottenuto " << make_list({1,2}).is_palindrome() << "\n";
        cout << "[7]         is_palindrome atteso 1, ottenuto " << make_list({7}).is_palindrome() << "\n";
        cout << "[]          is_palindrome atteso 1, ottenuto " << mylist().is_palindrome() << "\n";

        mylist s = make_list({1,3,5});
        s.insert_sorted(4);
        cout << "[1 3 5] + 4 atteso: 1 3 4 5\nOttenuto: "; s.print();
        s.insert_sorted(0);
        cout << "poi +0 atteso: 0 1 3 4 5\nOttenuto: "; s.print();
        s.insert_sorted(9);
        cout << "poi +9 atteso: 0 1 3 4 5 9\nOttenuto: "; s.print();

        mylist p = make_list({1,3,5});
        mylist q = make_list({2,4,6});
        mylist m = p.merge_sorted(q);
        cout << "merge_sorted [1 3 5],[2 4 6] atteso: 1 2 3 4 5 6\nOttenuto: "; m.print();

        mylist r = make_list({3,1,4,1,5,9,2,6});
        r.sort();
        cout << "sort [3 1 4 1 5 9 2 6] atteso: 1 1 2 3 4 5 6 9\nOttenuto: "; r.print();
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 9 — CONFRONTO DI LISTE
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 9: equal / is_prefix_of / is_suffix_of / contains_sublist");
    {
        mylist a = make_list({1,2,3});
        mylist b = make_list({1,2,3});
        mylist c = make_list({1,2});
        mylist d = make_list({1,2,3,4,5});

        cout << "equal atteso 1, ottenuto " << a.equal(b) << "\n";
        cout << "equal diverso atteso 0, ottenuto " << a.equal(c) << "\n";

        cout << "[1 2] is_prefix_of [1 2 3 4 5] atteso 1, ottenuto " << c.is_prefix_of(d) << "\n";
        cout << "[1 3] is_prefix_of [1 2 3]   atteso 0, ottenuto "
             << make_list({1,3}).is_prefix_of(a) << "\n";
        cout << "[]    is_prefix_of [1 2 3]   atteso 1, ottenuto "
             << mylist().is_prefix_of(a) << "\n";

        cout << "[4 5] is_suffix_of [1 2 3 4 5] atteso 1, ottenuto "
             << make_list({4,5}).is_suffix_of(d) << "\n";
        cout << "[3 5] is_suffix_of [1 2 3 4 5] atteso 0, ottenuto "
             << make_list({3,5}).is_suffix_of(d) << "\n";

        cout << "[2 3 4] in [1 2 3 4 5] atteso 1, ottenuto "
             << d.contains_sublist(make_list({2,3,4})) << "\n";
        cout << "[2 4]   in [1 2 3 4 5] atteso 0, ottenuto "
             << d.contains_sublist(make_list({2,4})) << "\n";
        cout << "[]      in [1 2 3]     atteso 1, ottenuto "
             << a.contains_sublist(mylist()) << "\n";
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 10 — POSIZIONI PARI/DISPARI
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 10: sum_even_positions / remove_odd_positions / reverse_from");
    {
        mylist a = make_list({10,20,30,40,50});
        cout << "sum_even_positions atteso 90, ottenuto " << a.sum_even_positions() << "\n";

        mylist b = make_list({10,20,30,40,50});
        b.remove_odd_positions();
        cout << "remove_odd_positions atteso: 10 30 50\nOttenuto: "; b.print();

        mylist c = make_list({1,2,3,4,5});
        c.reverse_from(2);
        cout << "reverse_from(2) atteso: 1 2 5 4 3\nOttenuto: "; c.print();

        mylist d = make_list({1,2,3,4,5});
        d.reverse_from(0);
        cout << "reverse_from(0) atteso: 5 4 3 2 1\nOttenuto: "; d.print();
    }

    // ═══════════════════════════════════════════════════════════════════════
    //   PATTERN 11 — MIX
    // ═══════════════════════════════════════════════════════════════════════
    section("PATTERN 11: shift_values / abs_values / compact_zeros");
    {
        mylist a = make_list({1,2,3});
        a.shift_values(10);
        cout << "shift_values(10) atteso: 11 12 13\nOttenuto: "; a.print();

        mylist b = make_list({-1,2,-3});
        b.abs_values();
        cout << "abs_values atteso: 1 2 3\nOttenuto: "; b.print();

        mylist c = make_list({1,0,0,0,2,0,3,0,0});
        c.compact_zeros();
        cout << "compact_zeros atteso: 1 0 2 0 3 0\nOttenuto: "; c.print();

        mylist d = make_list({0,0,0});
        d.compact_zeros();
        cout << "[0 0 0] compact_zeros atteso: 0\nOttenuto: "; d.print();

        mylist e = make_list({1,2,3});
        e.compact_zeros();
        cout << "[1 2 3] compact_zeros atteso: 1 2 3\nOttenuto: "; e.print();
    }

    section("PATTERN 11: second_max / kth_smallest");
    {
        mylist a = make_list({3,1,7,2,5});
        cout << "second_max atteso 5, ottenuto " << a.second_max() << "\n";

        mylist b = make_list({7,7,7,3});
        cout << "[7 7 7 3] second_max atteso 3, ottenuto " << b.second_max() << "\n";

        try {
            mylist c = make_list({7,7,7});
            c.second_max();
        } catch (std::out_of_range& e) {
            cout << "[7 7 7] second_max -> throw OK: " << e.what() << "\n";
        }

        mylist d = make_list({3,1,4,1,5,9,2,6});
        cout << "kth_smallest(0) atteso 1, ottenuto " << d.kth_smallest(0) << "\n";
        cout << "kth_smallest(1) atteso 1, ottenuto " << d.kth_smallest(1) << "\n";
        cout << "kth_smallest(2) atteso 2, ottenuto " << d.kth_smallest(2) << "\n";
        cout << "kth_smallest(7) atteso 9, ottenuto " << d.kth_smallest(7) << "\n";
        try { d.kth_smallest(99); }
        catch (std::out_of_range& e) { cout << "kth_smallest(99) -> throw OK\n"; }
    }

    section("PATTERN 11: move_zeros_to_end / partition");
    {
        mylist a = make_list({1,0,2,0,3});
        a.move_zeros_to_end();
        cout << "move_zeros_to_end atteso: 1 2 3 0 0\nOttenuto: "; a.print();

        mylist b = make_list({0,0,0});
        b.move_zeros_to_end();
        cout << "[0 0 0] atteso: 0 0 0\nOttenuto: "; b.print();

        mylist c = make_list({1,2,3});
        c.move_zeros_to_end();
        cout << "[1 2 3] atteso: 1 2 3\nOttenuto: "; c.print();

        mylist d = make_list({3,1,4,1,5,9,2,6});
        d.partition(4);
        cout << "partition(4) atteso: 3 1 1 2 4 5 9 6 (< prima, >= dopo, ordine stabile)\n";
        cout << "Ottenuto: "; d.print();

        mylist e = make_list({5,5,5});
        e.partition(5);
        cout << "[5 5 5] partition(5) atteso: 5 5 5 (tutti >=)\nOttenuto: "; e.print();

        mylist f = make_list({1,2,3});
        f.partition(10);
        cout << "[1 2 3] partition(10) atteso: 1 2 3 (tutti <)\nOttenuto: "; f.print();
    }

    cout << "\n############ FINE TEST ############\n";
    return 0;
}