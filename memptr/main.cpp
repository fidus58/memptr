//
//  main.cpp
//  memptr
//
//  Created by Klaus Ahrens on 26.05.21.
//

#include <iostream>

class X {
    int x, y, z;
    void foo() {std::cout<<"X::foo()\n";}
    void bar() {std::cout<<"X::bar()\n";}
    void bar(int=0) {std::cout<<"X::bar(int)\n";}
public:
    void set(int X:: * im, int val) {
        this->*im = val;
    }
    void set(X& x, int X::* im, int val) {
        x.*im = val;
    }
    void call(void (X::*func)()) {
        (this->*func)();
    }
    static void call(X& x, void (X::*func)()) {
        (x.*func)();
    }
    friend int main();
};

void call(X& x, void (X:: *f)()) {
    (x.*f)();
}

void call(X* xptr, void (X:: *f)()) {

    (xptr->*f)();
}

void foo() {std::cout<<"::foo()\n";}
void bar() {std::cout<<"::bar()\n";}
void bar(int=0) {std::cout<<"::bar(int)\n";}

void call(void (*f)()) {
    f();    // same as:
    (*f)();
}

int main() {
    call(foo); // same as:
    call(&foo);
    call(&bar);
    
    void (*fptr)(int) = &bar;
    fptr(33);
    (*fptr)(33);

    void (X::*f)() = &X::bar;

    X x;
    (x.*f)();
    x.set(&X::x, 1);
    x.set(&X::y, 2);
    x.set(&X::z, 3);

    x.call(&X::foo);
    X::call(x, &X::foo);
    call(x, &X::bar);
    call(&x, &X::foo);

    return 0;
}
