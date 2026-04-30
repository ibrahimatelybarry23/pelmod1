#include <cassert>
#include <vector>
#include "stack.hpp"

struct Stack::Impl {
    std::vector<int> v;
};

Stack::Stack() {
    pimpl = new Impl;
}

Stack::Stack(const Stack &s) {
    pimpl = new Impl;
    pimpl->v = s.pimpl->v;
}

Stack::~Stack() {
    delete pimpl;
}

void Stack::push(int x) {
    pimpl->v.push_back(x);
}

void Stack::pop() {
    pimpl->v.pop_back();
}

int Stack::top() const {
    assert(!pimpl->v.empty());
    return pimpl->v.back();
}

bool Stack::isempty() const {
    return pimpl->v.empty();
}
