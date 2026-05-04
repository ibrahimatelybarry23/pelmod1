#include <iostream>
#include <stdexcept>

using namespace std;

// A single node of the singly-linked list.
struct cell {
    int   value;  // data
    cell* next;   // link: pointer to the next node (nullptr if last)
};

class ll {
    public:
        ll();                    // default constructor
        ll(const ll& other);     // copy constructor
        ~ll();                   // destructor

        void prepend(int e);            // O(1) – insert at head
        void append(int e);             // O(N) – insert at tail
        void print() const;             // forward print
        void print_rev() const;         // reverse print (recursive)
        bool is_present(int e) const;   // true if e appears at least once

        int&       at(int pos);         // writable  indexed access; throws out_of_range
        const int& at(int pos) const;   // read-only indexed access; throws out_of_range

        void remove     (int e);        // remove first  occurrence of e
        void remove_last(int e);        // remove last   occurrence of e

        // ── Exercise methods ─────────────────────────────────────────────────

        int  sum() const;               // sum of all elements (recursive)
        void remove_all (int e);        // remove all    occurrences of e
        void remove_up_to_sum(int s);   // remove nodes whose suffix-sum is <= s
        void flip();                          // reverse the list in place (recursive)
        void double_even();                   // insert a copy after every even node (recursive)
        bool equal(const ll& other) const;    // recursive element-wise equality
        bool countfrom0(int& count) const;    // count elements after the last 0

        bool operator==(const ll& other) const;  // element-wise equality
        ll   operator+ (const ll& other) const;  // concatenation (new list)
        ll&  operator= (const ll& other);         // copy-assignment
    private:
        cell* head;  // pointer to the first node; nullptr when the list is empty

        // ── Private helpers ──────────────────────────────────────────────────
        void print_rev_rec(cell* curr) const;
        int  sum_rec(cell* curr) const;
        bool remove_last_rec(int e, cell* curr, cell* previous);  // version 1 (with prev ptr)
        bool remove_last_rec2(int e, cell*& curr);                // version 2 (ref-to-ptr)
        void remove_all_rec(int e, cell*& curr);
        int  remove_up_to_sum_rec(int s, cell*& curr);
        bool equal    (cell* head,  cell* head_other)  const;  // iterative equality
        bool equal_rec(cell* curr,  cell* curr_other)  const;  // recursive equality
        void flip_rec        (cell*& curr);
        void double_even_rec (cell*& curr);
        bool countfrom0_rec  (cell* curr, int& count) const;
};

// Default constructor: initialise an empty list.
ll::ll(){
    head = nullptr;
}

// Copy constructor: deep copy of other, preserving element order.
ll::ll(const ll& other){
    head = nullptr;
    cell* curr = nullptr;
    cell* curr_other = other.head;
    while(curr_other != nullptr){
        cell* nc = new cell{curr_other->value, nullptr};
        if(head == nullptr){
            head = nc;
            curr = nc;
        }else{
            curr->next = nc;
            curr = curr->next;
        }
        curr_other = curr_other->next;
    }
}

// Destructor: free every node iteratively.
ll::~ll(){
    while(head != nullptr){
        cell* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// prepend: insert e at the front – O(1).
void ll::prepend(int e){
    cell* nc = new cell{e, head};
    head = nc;
}

// append: insert e at the tail – O(N).
void ll::append(int e){
    cell* curr = head;
    cell* nc = new cell{e, nullptr};
    if(curr == nullptr){
        head = nc;
    } else {
        while(curr->next != nullptr){
            curr = curr->next;
        }
        curr->next = nc;
    }
}

// print: iterate and print each value.
void ll::print() const{
    cell* curr = head;
    while(curr != nullptr){
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl;
}

// is_present: linear scan.
bool ll::is_present(int e) const{
    cell* curr = head;
    while(curr != nullptr){
        if(curr->value == e)
            return true;
        curr = curr->next;
    }
    return false;
}

// at (writable)
int& ll::at(int pos){
    cell* curr = head;
    for(int i = 0; curr != nullptr && i != pos; i++){
        curr = curr->next;
    }
    if(curr == nullptr){
        throw std::out_of_range("OOR Error");
    }
    return curr->value;
}

// at (read-only)
const int& ll::at(int pos) const{
    cell* curr = head;
    for(int i = 0; curr != nullptr && i != pos; i++){
        curr = curr->next;
    }
    if(curr == nullptr){
        throw std::out_of_range("OOR Error");
    }
    return curr->value;
}

// remove: remove the FIRST occurrence of n.
void ll::remove(int n){
    cell* curr = head;
    cell* previous = nullptr;
    while(curr != nullptr && curr->value != n){
        previous = curr;
        curr = curr->next;
    }
    if (curr != nullptr){
        if(previous == nullptr)
            head = curr->next;
        else
            previous->next = curr->next;
        delete curr;
    }
}

// print_rev: public wrapper.
void ll::print_rev() const{
    print_rev_rec(head);
    cout << endl;
}

void ll::print_rev_rec(cell* curr) const{
    if (curr != nullptr){
        print_rev_rec(curr->next);
        cout << curr->value << " ";
    }
}

// remove_last: public wrapper.
void ll::remove_last(int e){
    remove_last_rec2(e, head);
}

// remove_last_rec (version 1, with explicit prev pointer)
bool ll::remove_last_rec(int e, cell* curr, cell* previous){
    if (curr == nullptr){
        return false;
    }
    bool removed = remove_last_rec(e, curr->next, curr);
    if(!removed && curr->value == e){
        if(previous == nullptr)
            head = curr->next;
        else
            previous->next = curr->next;
        delete curr;
        return true;
    }
    return removed;
}

// remove_last_rec (version 2, reference-to-pointer)
bool ll::remove_last_rec2(int e, cell*& curr){
    if(curr == nullptr)
        return false;
    bool rem = remove_last_rec2(e, curr->next);
    if(!rem && curr->value == e){
        cell* tmp = curr;
        curr = curr->next;
        delete tmp;
        return true;
    }
    return rem;
}

// ─── operator== e equal ─────────────────────────────────────────────────────
bool ll::operator==(const ll& other) const{
    return equal_rec(head, other.head);
}

bool ll::equal(cell* h, cell* h_other) const{
    bool uguali = true;
    while(h != nullptr && h_other != nullptr && uguali){
        if(h->value != h_other->value)
            uguali = false;
        h = h->next;
        h_other = h_other->next;
    }
    return uguali && (h == nullptr && h_other == nullptr);
}

bool ll::equal_rec(cell* curr, cell* curr_other) const{
    if(curr == nullptr && curr_other == nullptr)
        return true;
    else
        if(curr == nullptr || curr_other == nullptr)
            return false;
        else
            if(curr->value != curr_other->value)
                return false;
    return equal_rec(curr->next, curr_other->next);
}

// ─── operator+ ───────────────────────────────────────────────────────────────
ll ll::operator+(const ll& other) const{
    ll res(*this);
    cell* cur = other.head;
    while (cur != nullptr){
        res.append(cur->value);
        cur = cur->next;
    }
    return res;
}

// ─── operator= ───────────────────────────────────────────────────────────────
ll& ll::operator=(const ll& other){
    if(this == &other) return *this;

    while(head != nullptr){
        cell* tmp = head;
        head = head->next;
        delete tmp;
    }
    head = nullptr;
    cell* cur = nullptr;
    cell* cur_o = other.head;
    while (cur_o != nullptr){
        cell* nu = new cell{cur_o->value, nullptr};
        if(head == nullptr){
            head = nu;
            cur = nu;
        } else {
            cur->next = nu;
            cur = cur->next;
        }
        cur_o = cur_o->next;
    }
    return *this;
}

// ─── sum ─────────────────────────────────────────────────────────────────────
int ll::sum() const{
    return sum_rec(head);
}

int ll::sum_rec(cell* curr) const{
    if (curr == nullptr)
        return 0;
    else
        return curr->value + sum_rec(curr->next);
}

// ─── remove_all ──────────────────────────────────────────────────────────────
void ll::remove_all(int e){
    while(head != nullptr && head->value == e){
        cell* tmp = head;
        head = head->next;
        delete tmp;
    }
    cell* prev = head;
    while(prev != nullptr && prev->next != nullptr){
        cell* cur = prev->next;
        if(cur->value == e){
            prev->next = cur->next;
            delete cur;
        } else {
            prev = prev->next;
        }
    }
}

// Bonus: versione ricorsiva
void ll::remove_all_rec(int e, cell*& curr){
    if(curr == nullptr) return;
    else
        if(curr->value == e){
            cell* tmp = curr;
            curr = curr->next;
            delete tmp;
            remove_all_rec(e, curr);
        } else {
            remove_all_rec(e, curr->next);
        }
}

// ─── remove_up_to_sum ────────────────────────────────────────────────────────
void ll::remove_up_to_sum(int s){
    remove_up_to_sum_rec(s, head);
}

int ll::remove_up_to_sum_rec(int s, cell*& curr){
    if(curr == nullptr)
        return 0;
    int sum_d = remove_up_to_sum_rec(s, curr->next);
    int sum_suffix = curr->value + sum_d;
    if(sum_suffix <= s){
        cell* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    return sum_suffix;
}

// ─── flip ────────────────────────────────────────────────────────────────────
void ll::flip(){
    flip_rec(head);
}

void ll::flip_rec(cell*& curr){
    if(curr == nullptr || curr->next == nullptr)
        return;
    cell* next_n = curr->next;
    flip_rec(curr->next);
    cell* new_h = curr->next;
    next_n->next = curr;
    curr->next = nullptr;
    curr = new_h;
}

// ─── double_even ─────────────────────────────────────────────────────────────
void ll::double_even(){
    double_even_rec(head);
}

void ll::double_even_rec(cell*& curr){
    if(curr == nullptr)
        return;
    double_even_rec(curr->next);
    if(curr->value % 2 == 0){
        cell* clone = new cell{curr->value, curr->next};
        curr->next = clone;
    }
}

// ─── equal pubblica ──────────────────────────────────────────────────────────
bool ll::equal(const ll& other) const{
    return equal_rec(head, other.head);
}

// ─── countfrom0 ──────────────────────────────────────────────────────────────
bool ll::countfrom0(int& count) const{
    return countfrom0_rec(head, count);
}

bool ll::countfrom0_rec(cell* curr, int& count) const{
    bool res;
    if(curr == nullptr){
        count = 0;
        res = false;
    } else {
        bool f = countfrom0_rec(curr->next, count);
        if(curr->value == 0)
            res = true;
        else {
            if(!f) count++;
            res = f;
        }
    }
    return res;
}

///// MAIN /////

int main(){
    cout << "========== TEST ll.cpp ==========" << endl << endl;

    // ─── Test 1: prepend, append, print ──────────────────────────────
    cout << "--- Test 1: prepend/append/print ---" << endl;
    ll l1;
    l1.append(1); l1.append(2); l1.append(3);
    l1.prepend(0);
    cout << "Atteso: 0 1 2 3" << endl;
    cout << "Output: "; l1.print();
    cout << endl;

    // ─── Test 2: sum ─────────────────────────────────────────────────
    cout << "--- Test 2: sum ---" << endl;
    cout << "Lista [0 1 2 3], sum atteso = 6, ottenuto = " << l1.sum() << endl;
    ll l_vuota;
    cout << "Lista [], sum atteso = 0, ottenuto = " << l_vuota.sum() << endl;
    cout << endl;

    // ─── Test 3: copy constructor ─────────────────────────────────────
    cout << "--- Test 3: copy constructor ---" << endl;
    ll l_copia(l1);
    cout << "Originale: "; l1.print();
    cout << "Copia:     "; l_copia.print();
    l_copia.append(99);
    cout << "Dopo aver modificato la copia aggiungendo 99:" << endl;
    cout << "Originale: "; l1.print();
    cout << "Copia:     "; l_copia.print();
    cout << endl;

    // ─── Test 4: operator= ────────────────────────────────────────────
    cout << "--- Test 4: operator= ---" << endl;
    ll l_assegn;
    l_assegn.append(999); l_assegn.append(888);
    cout << "Prima: l_assegn: "; l_assegn.print();
    l_assegn = l1;
    cout << "Dopo l_assegn = l1: "; l_assegn.print();
    cout << "l1 (invariata):    "; l1.print();
    l_assegn = l_assegn;
    cout << "Dopo self-assignment: "; l_assegn.print();
    cout << endl;

    // ─── Test 5: operator== e equal ────────────────────────────────────
    cout << "--- Test 5: operator== / equal ---" << endl;
    ll a, b, c;
    a.append(1); a.append(2); a.append(3);
    b.append(1); b.append(2); b.append(3);
    c.append(1); c.append(2); c.append(9);
    cout << "[1 2 3] == [1 2 3]: atteso 1, ottenuto " << (a == b) << endl;
    cout << "[1 2 3] == [1 2 9]: atteso 0, ottenuto " << (a == c) << endl;
    ll vuota1, vuota2;
    cout << "[] == []: atteso 1, ottenuto " << (vuota1 == vuota2) << endl;
    ll corta;
    corta.append(1); corta.append(2);
    cout << "[1 2 3] == [1 2]: atteso 0, ottenuto " << (a == corta) << endl;
    cout << endl;

    // ─── Test 6: operator+ ────────────────────────────────────────────
    cout << "--- Test 6: operator+ ---" << endl;
    ll x, y;
    x.append(1); x.append(2);
    y.append(3); y.append(4);
    ll somma = x + y;
    cout << "[1 2] + [3 4] atteso: 1 2 3 4" << endl;
    cout << "Ottenuto: "; somma.print();
    cout << "x (non modificato): "; x.print();
    cout << "y (non modificato): "; y.print();
    cout << endl;

    // ─── Test 7: remove_last ──────────────────────────────────────────
    cout << "--- Test 7: remove_last ---" << endl;
    ll rl;
    rl.append(1); rl.append(2); rl.append(3); rl.append(2); rl.append(4);
    cout << "Prima: "; rl.print();
    rl.remove_last(2);
    cout << "Dopo remove_last(2), atteso: 1 2 3 4" << endl;
    cout << "Ottenuto: "; rl.print();
    cout << endl;

    // ─── Test 8: remove_all ───────────────────────────────────────────
    cout << "--- Test 8: remove_all ---" << endl;
    ll ra;
    ra.append(5); ra.append(1); ra.append(5); ra.append(5); ra.append(2); ra.append(5);
    cout << "Prima: "; ra.print();
    ra.remove_all(5);
    cout << "Dopo remove_all(5), atteso: 1 2" << endl;
    cout << "Ottenuto: "; ra.print();
    ll ra2;
    ra2.append(7); ra2.append(7); ra2.append(7);
    ra2.remove_all(7);
    cout << "[7 7 7] remove_all(7), atteso: (vuota)" << endl;
    cout << "Ottenuto: "; ra2.print();
    cout << endl;

    // ─── Test 9: remove_up_to_sum ─────────────────────────────────────
    cout << "--- Test 9: remove_up_to_sum ---" << endl;
    ll rs1;
    rs1.append(3); rs1.append(1); rs1.append(2); rs1.append(4); rs1.append(5);
    rs1.remove_up_to_sum(6);
    cout << "[3 1 2 4 5] remove_up_to_sum(6), atteso: 3 1 2 4" << endl;
    cout << "Ottenuto: "; rs1.print();

    ll rs2;
    rs2.append(1); rs2.append(2); rs2.append(3);
    rs2.remove_up_to_sum(10);
    cout << "[1 2 3] remove_up_to_sum(10), atteso: (vuota)" << endl;
    cout << "Ottenuto: "; rs2.print();

    ll rs3;
    rs3.append(1); rs3.append(2); rs3.append(3);
    rs3.remove_up_to_sum(0);
    cout << "[1 2 3] remove_up_to_sum(0), atteso: 1 2 3" << endl;
    cout << "Ottenuto: "; rs3.print();
    cout << endl;

    // ─── Test 10: flip ────────────────────────────────────────────────
    cout << "--- Test 10: flip ---" << endl;
    ll f1;
    f1.append(1); f1.append(2); f1.append(3); f1.append(4); f1.append(5);
    cout << "Prima: "; f1.print();
    f1.flip();
    cout << "Dopo flip, atteso: 5 4 3 2 1" << endl;
    cout << "Ottenuto: "; f1.print();

    ll f2;
    f2.append(42);
    f2.flip();
    cout << "[42] flip, atteso: 42 - Ottenuto: "; f2.print();

    ll f3;
    f3.flip();
    cout << "[] flip, atteso: (vuota) - Ottenuto: "; f3.print();
    cout << endl;

    // ─── Test 11: double_even ─────────────────────────────────────────
    cout << "--- Test 11: double_even ---" << endl;
    ll de1;
    de1.append(2); de1.append(7); de1.append(0); de1.append(5);
    cout << "Prima: "; de1.print();
    de1.double_even();
    cout << "Dopo double_even, atteso: 2 2 7 0 0 5" << endl;
    cout << "Ottenuto: "; de1.print();

    ll de2;
    de2.append(1); de2.append(3); de2.append(5);
    de2.double_even();
    cout << "[1 3 5] double_even, atteso: 1 3 5 - Ottenuto: "; de2.print();

    ll de3;
    de3.append(0);
    de3.double_even();
    cout << "[0] double_even, atteso: 0 0 - Ottenuto: "; de3.print();
    cout << endl;

    // ─── Test 12: countfrom0 ──────────────────────────────────────────
    cout << "--- Test 12: countfrom0 ---" << endl;
    int cnt;
    ll cf1;
    cf1.append(3); cf1.append(0); cf1.append(5); cf1.append(2);
    bool res = cf1.countfrom0(cnt);
    cout << "[3 0 5 2] atteso: true, 2 - Ottenuto: " << res << ", " << cnt << endl;

    ll cf2;
    cf2.append(1); cf2.append(0); cf2.append(2); cf2.append(0); cf2.append(7);
    res = cf2.countfrom0(cnt);
    cout << "[1 0 2 0 7] atteso: true, 1 - Ottenuto: " << res << ", " << cnt << endl;

    ll cf3;
    cf3.append(1); cf3.append(2); cf3.append(3);
    res = cf3.countfrom0(cnt);
    cout << "[1 2 3] atteso: false, 3 - Ottenuto: " << res << ", " << cnt << endl;

    ll cf4;
    cf4.append(0); cf4.append(0); cf4.append(0);
    res = cf4.countfrom0(cnt);
    cout << "[0 0 0] atteso: true, 0 - Ottenuto: " << res << ", " << cnt << endl;

    ll cf5;
    res = cf5.countfrom0(cnt);
    cout << "[] atteso: false, 0 - Ottenuto: " << res << ", " << cnt << endl;
    cout << endl;

    // ─── Test 13: print_rev ───────────────────────────────────────────
    cout << "--- Test 13: print_rev ---" << endl;
    ll pr;
    pr.append(1); pr.append(2); pr.append(3);
    cout << "Lista [1 2 3]" << endl;
    cout << "print:     "; pr.print();
    cout << "print_rev: "; pr.print_rev();
    cout << endl;

    // ─── Test 14: at ──────────────────────────────────────────────────
    cout << "--- Test 14: at ---" << endl;
    ll at1;
    at1.append(10); at1.append(20); at1.append(30);
    cout << "at(0) atteso: 10, ottenuto: " << at1.at(0) << endl;
    cout << "at(1) atteso: 20, ottenuto: " << at1.at(1) << endl;
    at1.at(1) = 99;
    cout << "Dopo at(1) = 99, atteso: 10 99 30" << endl;
    cout << "Ottenuto: "; at1.print();
    try {
        at1.at(100);
    } catch (std::out_of_range& e) {
        cout << "at(100) -> throw caught: " << e.what() << endl;
    }
    cout << endl;

    // ─── Test 15: is_present ──────────────────────────────────────────
    cout << "--- Test 15: is_present ---" << endl;
    ll ip;
    ip.append(1); ip.append(2); ip.append(3);
    cout << "is_present(2) atteso: 1, ottenuto: " << ip.is_present(2) << endl;
    cout << "is_present(99) atteso: 0, ottenuto: " << ip.is_present(99) << endl;
    cout << endl;

    cout << "========== FINE TEST ==========" << endl;
    return 0;
}