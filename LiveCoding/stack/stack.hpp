#pragma once

class Stack {
public:
  Stack();
  Stack(const Stack &s);
  ~Stack();
  void push(int x);
  void pop();
  int top() const;
  bool isempty() const;
  int size() const;
private:
  struct cell {
    int info;
    cell *next;
  };
  cell *head;
};
