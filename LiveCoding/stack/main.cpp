#include <iostream>
#include "stack.hpp"

int main() {
  Stack s;
  s.push(6);
  s.push(12);
  s.push(43);
  while (!s.isempty()) {
    std::cout << s.top() << std::endl;
    s.pop();
  }
}