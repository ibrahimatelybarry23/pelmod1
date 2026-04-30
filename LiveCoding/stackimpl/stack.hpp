



class Stack {
public:
  Stack();
  Stack(const Stack &s);
  void push(int x);
  void pop();
  int top() const;
  bool isempty() const;
private:
struct Impl; // dichiarazione ma non definizione sto dicendo che esite una strutura Impl

  Impl * pimpl;
};
