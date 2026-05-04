#include <iostream>
 struct Cell{
            int val;
            Cell*next;
    };
    
class List {

    
public:
    Cell* reverseList(Cell* head);
    List();
    ~List();

 private:
    Cell*head;
   

};



 Cell* reverseList(Cell* head) {
        if(head == nullptr || head->next== nullptr)
            return head;
        Cell* newNode = reverseList(head->next);
        head->next->next= head;
        head->next=nullptr;
        return newNode;
        
    }
int main(){

}