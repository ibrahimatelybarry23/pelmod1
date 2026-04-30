#include <cassert>
#include "stack.hpp"



struct Stack::Impl
{
    int info;
    Impl*next;
};

Stack::Stack() { pimpl = nullptr; }

Stack::Stack(const Stack &s) {
  pimpl = nullptr;
  Impl *pc = s.pimpl;
  Impl *cur = nullptr;
  while (pc != nullptr) {
    Impl *nuova = new Impl;
    nuova->info = pc->info;
    nuova->next = nullptr;
    if (cur == nullptr) {
      pimpl = nuova;
    } else {
      cur->next = nuova;
    }
    cur = nuova;
    pc = pc->next;
  }
}

void Stack::push(int x) {
  Impl *nuova = new Impl;
  nuova->info = x;
  nuova->next = pimpl;
  pimpl = nuova;
}

void Stack::pop() {
  assert(pimpl != nullptr);
  Impl *pc = pimpl;
  pimpl = pimpl->next;
  delete pc;
}

int Stack::top() const {
  assert(pimpl != nullptr);
  return pimpl->info;
}

bool Stack::isempty() const {
  return pimpl == nullptr;
}

