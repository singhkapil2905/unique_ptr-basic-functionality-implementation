#include "my_unique_ptr.h"
#include <iostream>

using namespace kapil;

class A {
  private:
    int* p;
  public:
    A() {
      std::cout << " constructed \n";
      p = new int{20};
    }

    ~A() {
      delete p;
      std::cout << " destructed !! \n";
    }
};

int main() {
  unique_ptr<int> x1;
  x1 = unique_ptr<int>(new int{200});
  unique_ptr<int> x2{new int{4}};
  std::cout << " x1 : " << *x1.get() << "  x2 : " << *x2.get() << std::endl;

  int *t1 = x1.release();
  if (!x1) {
    std::cout << " x1 is empty and its value was : " << *t1 << std::endl;
  }

  unique_ptr<int> x4;
  x4.reset(new int{9});

  x2.swap(x4);
  std::cout << " x2 : " << *x2 << "   x4 : " << *x4 << std::endl;

  swap(x2, x4);
  std::cout << " x2 : " << *x2 << "   x4 : " << *x4 << std::endl;


  unique_ptr<A> a{new A}; 
  unique_ptr<A> b; 

  return 0;
}
