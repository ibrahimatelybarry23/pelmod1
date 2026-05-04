#include <iostream>
using namespace std;

struct cell {
    int   info;
    cell* next;
};

class list {
    public:
        list();
        list(const list& other);
        ~list();

        void push_back(int e);
        void print() const;

        void remove_all(int e);
        void remove_up_to_sum(int s);

    private:
        cell* head;
        int remove_up_to_sum_rec(int s, cell*& curr);   // ← firma COME l'hai scritta tu (senza &)
};

// ───── default ctor ─────
list::list() { head = nullptr; }

// ───── destructor ─────
list::~list() {
    while (head != nullptr) {
        cell* tmp = head;
        head = head->next;
        delete tmp;
    }
}

// ───── push_back (helper per i test) ─────
void list::push_back(int e) {
    cell* nuovo = new cell{e, nullptr};
    if (head == nullptr) head = nuovo;
    else {
        cell* cur = head;
        while (cur->next != nullptr) cur = cur->next;
        cur->next = nuovo;
    }
}

// ───── print ─────
void list::print() const {
    cell* cur = head;
    cout << "[";
    while (cur != nullptr) {
        cout << cur->info;
        if (cur->next != nullptr) cout << " ";
        cur = cur->next;
    }
    cout << "]" << endl;
}

// ═══════════════════════════════════════════════════════════════════
// ESERCIZIO 1 — copy constructor (come l'hai scritto tu)
// ═══════════════════════════════════════════════════════════════════
list::list(const list& other) {
    head = nullptr;
    cell* curr = nullptr;
    cell* curr_o = other.head;
    while (curr_o != nullptr) {
        cell* nuovo = new cell{curr_o->info, nullptr};
        if (head == nullptr) {
            head = nuovo;
            curr = nuovo;
        } else {
            curr->next = nuovo;
            curr = curr->next;
        }
        curr_o = curr_o->next;
    }
}

// ═══════════════════════════════════════════════════════════════════
// ESERCIZIO 2 — remove_all (come l'hai scritto tu, BUG INCLUSI)
// ═══════════════════════════════════════════════════════════════════
void list::remove_all(int e) {
    while (head != nullptr && head->info == e) {
        cell* tmp = head;
        head = head->next;
        delete tmp;
    }
    cell* prev = head;
    while (prev != nullptr && prev->next != nullptr) {
        cell*cur = prev->next;
        if (prev->next->info == e) {
            prev->next = cur->next;   // ← bug: 'cur' non dichiarato
            delete cur;                // ← bug: 'cur' non dichiarato
        } else {
            prev = prev->next;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════
// ESERCIZIO 3 — remove_up_to_sum (come l'hai scritto tu, BUG INCLUSI)
// ═══════════════════════════════════════════════════════════════════
void list::remove_up_to_sum(int s) {
    remove_up_to_sum_rec(s, head);
}

int list::remove_up_to_sum_rec(int s, cell*& curr) {   // ← bug: manca la &
    if (curr == nullptr) return 0;
    int sum_ol = remove_up_to_sum_rec(s, curr->next);
    int suf_s  = curr->info + sum_ol;
    if (suf_s <= s) {
        cell* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    return suf_s;
}

// ═══════════════════════════════════════════════════════════════════
// MAIN DI TEST
// ═══════════════════════════════════════════════════════════════════
int main() {
    cout << "### TEST 1: copy constructor ###\n";
    list a;
    a.push_back(10); a.push_back(5); a.push_back(7);
    list b(a);
    cout << "Originale: "; a.print();
    cout << "Copia:     "; b.print();
    cout << "(atteso entrambe: [10 5 7])\n\n";

    cout << "### TEST 2: remove_all ###\n";
    list r;
    r.push_back(10); r.push_back(7); r.push_back(10); r.push_back(10);
    cout << "Prima:     "; r.print();
    r.remove_all(10);
    cout << "Dopo:      "; r.print();
    cout << "(atteso: [7])\n\n";

    cout << "### TEST 3: remove_up_to_sum ###\n";
    list u;
    u.push_back(3); u.push_back(1); u.push_back(2); u.push_back(4); u.push_back(5);
    cout << "Prima:     "; u.print();
    u.remove_up_to_sum(6);
    cout << "Dopo:      "; u.print();
    cout << "(atteso: [3 1 2 4])\n";

    return 0;
}