#include <cassert>
#include "stack.hpp"

Stack::Stack() { head = nullptr; }

Stack::Stack(const Stack &s) {
  head = nullptr;
  cell *pc = s.head;
  cell *cur = nullptr;
  while (pc != nullptr) {
    cell *nuova = new cell;
    nuova->info = pc->info;
    nuova->next = nullptr;
    if (cur == nullptr) {
      head = nuova;
    } else {
      cur->next = nuova;
    }
    cur = nuova;
    pc = pc->next;
  }
}

Stack::~Stack() {
  while (!isempty())
    pop();
}

void Stack::push(int x) {
  cell *nuova = new cell;
  nuova->info = x;
  nuova->next = head;
  head = nuova;
}

void Stack::pop() {
  assert(head != nullptr);
  cell *pc = head;
  head = head->next;
  delete pc;
}

int Stack::remove() {
  int val = top();
  pop();
  return val;
}

int Stack::top() const {
  assert(head != nullptr);
  return head->info;
}

bool Stack::isempty() const {
  return head == nullptr;
}

int Stack::size() const {
  int count = 0;
  cell *pc = head;
  while (pc != nullptr) {
    count++;
    pc = pc->next;
  }
  return count;
}
