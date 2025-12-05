#include <iostream>
#include "unique_ptr.hpp"

struct Test {
    int x;
    Test(int v) : x(v) {
        std::cout << "Test(" << x << ") constructed\n";
    }
    ~Test() {
        std::cout << "Test(" << x << ") destroyed\n";
    }
    void hello() const {
        std::cout << "Hello from Test(" << x << ")\n";
    }
};

unique_ptr<int> make_int_ptr(int v) {
    return unique_ptr<int>(new int(v));
}

unique_ptr<Test> make_test_ptr(int v) {
    return unique_ptr<Test>(new Test(v));
}

int main() {

    std::cout << "=== Constructor and operator* / operator-> ===\n";
    unique_ptr<Test> p1(new Test(10));
    std::cout << "p1->x = " << p1->x << "\n";
    p1->hello();
    std::cout << "*p1.x = " << (*p1).x << "\n";

    std::cout << "\n=== Move constructor ===\n";
    unique_ptr<Test> p2(std::move(p1));
    std::cout << "p1 is " << (p1 ? "not null" : "null") << "\n";
    std::cout << "p2 is " << (p2 ? "not null" : "null") << "\n";
    p2->hello();

    std::cout << "\n=== Move assignment ===\n";
    unique_ptr<Test> p3(new Test(20));
    p3 = std::move(p2);
    std::cout << "p2 is " << (p2 ? "not null" : "null") << "\n";
    std::cout << "p3 is " << (p3 ? "not null" : "null") << "\n";
    p3->hello();

    std::cout << "\n=== release() ===\n";
    Test* raw = p3.release();
    std::cout << "p3 is " << (p3 ? "not null" : "null") << "\n";
    std::cout << "raw->x = " << raw->x << "\n";
    delete raw; // manual delete after release()

    std::cout << "\n=== reset() ===\n";
    unique_ptr<int> ip = make_int_ptr(42);
    std::cout << "ip: " << *ip << "\n";
    ip.reset(new int(100));
    std::cout << "ip after reset: " << *ip << "\n";
    ip.reset(); // deleting stored int

    std::cout << "\n=== get() and bool() ===\n";
    unique_ptr<int> pnull(nullptr);
    std::cout << "pnull.get() = " << pnull.get() << "\n";
    std::cout << "pnull is " << (pnull ? "not null" : "null") << "\n";
    pnull.reset(new int(77));
    std::cout << "*pnull = " << *pnull << "\n";
    std::cout << "pnull is " << (pnull ? "not null" : "null") << "\n";

    std::cout << "\n=== Automatic destruction on scope exit ===\n";
    {
        unique_ptr<Test> temp(new Test(999));
        temp->hello();
    } // destructor called here


    std::cout << "\n=== operator bool() ===\n";

    // Start with a nullptr
    unique_ptr<int> p(nullptr);
    std::cout << "p is " << (p ? "not null" : "null") << "\n";

    // Reset with a value
    p.reset(new int(42));
    std::cout << "After reset, p is " << (p ? "not null" : "null") << "\n";

    // Release the pointer
    p.release();
    std::cout << "After release, p is " << (p ? "not null" : "null") << "\n";

    std::cout << "\n=== End of tests ===\n";
}
