class Stack {
public:
  Stack();
  Stack(const Stack &s);
  ~Stack();
  void push(int x);
  void pop();
  int top() const;
  bool isempty() const;
private:
  struct Impl;
  Impl *pimpl;
};
