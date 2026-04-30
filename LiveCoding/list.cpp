#include <iostream>


class List{
    
    public:
        List();
        List(const List &s);
        List();
        void prepend(int x);
        void append(int x);
        void print() const;
        bool presente (int x) const;
        int stampa_posizione(int pos) const; // se  non esiste la posizione stampo non esiste farlo sia ritorsivo che iterativo




    private:
        struct Cella{
            int info;
            Cella* next;
        };
        Cella* head;
         void  List::print_rec(Cella*pc)const;
         void List::append_rec(const Cella*& l,int x);
         bool presente_rec(Cella *pc,int x) const;
        
}; 



List::List(){
    head = nullptr;
    std::cout<< "Costruttore di default";

}
List::~List(){
    while (head != nullptr){
        Cella* pc = head;
        head=head->next;
        delete pc;
    }
    std::cout<< "Distruttore di classe"<<std::endl;
}

List::List(const List &s){
    Cella * pc = s.head; 
    Cella *nc= nullptr;
    head = nullptr;
    while(pc!= nullptr){
        if(head==nullptr){
            nc= new Cella;
            nc->info = pc->info;
            nc = head;
        }
        else{
            nc->next = new Cella;
            nc=nc->next;
            nc->info = pc->info;
        }
        pc=pc->next;
            
        }
    if(nc!=nullptr){
        nc->next=nullptr;
    }
    
}

void List::print() const{
    Cella * pc = head;
    // while (pc!= nullptr){
    //     std::cout << pc->info<<std::endl;
    //     pc=pc->next;
    // }
    print_rec(pc);
}

void List::print_rec(Cella*pc)const{
    if(pc!= nullptr){
        std::cout<<pc->info<<std::endl;
        print_rec(pc->next);
    }
}
void List::prepend(int x){
    Cella *nuova = new Cella;
    nuova->info=x;
    nuova->next= head;
    head = nuova;
}
void List::append(int x){
    
    if(head=nullptr){
        head= new Cella;
        return;
        head->info = x;
        head->next = nullptr;
    }
    else{
        Cella* cur = head; 
        while(cur->next != nullptr){
            cur= cur->next;
        }
        cur->next= new Cella;
        cur->next->info =x;
        cur->next->next = nullptr;
    }
}
// append ricorsiva facciamo la ricorsione su 
void List::append_rec(const Cella*& l,int x){
    if(l!=nullptr){
        append_rec(l->next,x);
    }else{
        l=new Cella;
        l->info =x;
        l->next = nullptr;
    }
}
bool List::presente (int x) const{
    Cella *pc =  head; 
    bool f = false; 

    while(pc!= nullptr && !f){
        if(pc->info == x)
            f = true;
        pc=pc->next;
    }
    return f;
}

void stampax2(const List &l){
    l.print();
    l.print();
}

  bool List::presente_rec(Cella *pc,int x) const{
        if(pc == nullptr)
            return else;
        else{
            retutn pc->info == x || presente_rec(pc->next,x) ;
        }
  }

// per const reference causa errori!  soluzione aggiungere un const 
int main(){
List l;
l.prepend(12);
l.prepend(25);
l.print();
List l1 = l;
l1.prepend(0);
l.print();
l1.print();
return 0;
}