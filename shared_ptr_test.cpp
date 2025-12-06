#include <iostream>
#include "shared_ptr.hpp"

struct Test {
    int x;
    Test(int v) : x(v) { std::cout << "Test(" << x << ") constructed\n"; }
    ~Test() { std::cout << "Test(" << x << ") destroyed\n"; }

    void hello() { std::cout << "Hello from Test(" << x << ")\n"; }
};

int main() {
    std::cout << "=== Basic construction ===\n";
    shared_ptr<Test> p1(new Test(10));
    std::cout << "use_count p1 = " << p1.use_count() << "\n";
    std::cout << "p1->x = " << p1->x << "\n";
    (*p1).hello();

    std::cout << "\n=== Copy construction ===\n";
    shared_ptr<Test> p2(p1);
    std::cout << "use_count p1 = " << p1.use_count() << "\n";
    std::cout << "use_count p2 = " << p2.use_count() << "\n";

    std::cout << "\n=== Copy assignment ===\n";
    shared_ptr<Test> p3(new Test(20));
    std::cout << "use_count p3 (before) = " << p3.use_count() << "\n";
    p3 = p1;
    std::cout << "use_count p3 (after)  = " << p3.use_count() << "\n";
    std::cout << "use_count p1 = " << p1.use_count() << "\n";

    std::cout << "\n=== Move construction ===\n";
    shared_ptr<Test> p4(std::move(p1));
    std::cout << "use_count p4 = " << p4.use_count() << "\n";
    std::cout << "p1 bool = " << static_cast<bool>(p1) << "\n";

    std::cout << "\n=== Move assignment ===\n";
    shared_ptr<Test> p5(new Test(30));
    std::cout << "use_count p5 (before) = " << p5.use_count() << "\n";
    p5 = std::move(p2);
    std::cout << "use_count p5 (after) = " << p5.use_count() << "\n";
    std::cout << "p2 bool = " << static_cast<bool>(p2) << "\n";

    std::cout << "\n=== Reset to null ===\n";
    p3.reset();
    std::cout << "p3 bool = " << static_cast<bool>(p3) << "\n";

    std::cout << "\n=== Reset to new pointer ===\n";
    p4.reset(new Test(40));
    std::cout << "p4->x = " << p4->x << "\n";
    std::cout << "use_count p4 = " << p4.use_count() << "\n";

    std::cout << "\n=== Mixed scope lifetime test ===\n";
    {
        shared_ptr<Test> a(new Test(100));
        shared_ptr<Test> b(a);
        shared_ptr<Test> c(b);

        std::cout << "use_count inside scope = " << a.use_count() << "\n";
    }
    std::cout << "All a/b/c should be destroyed now.\n";

    std::cout << "\n=== End of main ===\n";
    return 0;
}
