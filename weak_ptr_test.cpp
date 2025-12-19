#include <iostream>
#include <cassert>
#include "shared_ptr.hpp"
#include "weak_ptr.hpp"

struct Resource {
    int value;
    Resource(int v) : value(v) { std::cout << "Resource created\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main() {
    std::cout << "--- Starting weak_ptr Tests ---\n";

    // 1. Basic Construction and expired() check
    {
        std::cout << "\nTest 1: Basic Lifecycle\n";
        shared_ptr<Resource> sp1(new Resource(10));
        weak_ptr<Resource> wp1(sp1);

        std::cout << "Use count after wp creation: " << wp1.use_count() << "\n";
        assert(!wp1.expired());

        sp1.reset(); 
        std::cout << "Use count after sp1 reset: " << wp1.use_count() << "\n";
        
        if (wp1.expired()) {
            std::cout << "Success: weak_ptr expired after shared_ptr reset.\n";
        } else {
            std::cout << "Failure: weak_ptr should be expired.\n";
        }
    }

    // 2. Lock mechanism
    {
        std::cout << "\nTest 2: Lock mechanism\n";
        shared_ptr<Resource> sp2(new Resource(20));
        weak_ptr<Resource> wp2(sp2);

        shared_ptr<Resource> locked = wp2.lock();
        if (locked) {
            std::cout << "Locked shared_ptr value: " << locked->value << "\n";
            std::cout << "Use count during lock: " << wp2.use_count() << "\n";
        }
        
        locked.reset();
        sp2.reset();
        
        shared_ptr<Resource> locked_after = wp2.lock();
        if (!locked_after) {
            std::cout << "Success: Lock returned empty shared_ptr after resource destruction.\n";
        }
    }

    // 3. Copy and Assignment
    {
        std::cout << "\nTest 3: Copy and Assignment\n";
        shared_ptr<Resource> sp3(new Resource(30));
        weak_ptr<Resource> wp_orig(sp3);
        
        weak_ptr<Resource> wp_copy(wp_orig);
        std::cout << "Copy use count: " << wp_copy.use_count() << "\n";

        weak_ptr<Resource> wp_assign;
        wp_assign = wp_orig;
        std::cout << "Assignment use count: " << wp_assign.use_count() << "\n";
    }

    // 4. Move Semantics
    {
        std::cout << "\nTest 4: Move Semantics\n";
        shared_ptr<Resource> sp4(new Resource(40));
        weak_ptr<Resource> wp_to_move(sp4);
        
        std::cout << "Before move - wp_to_move use_count: " << wp_to_move.use_count() << "\n";
        
        weak_ptr<Resource> wp_moved_to(std::move(wp_to_move));
        std::cout << "After move - wp_moved_to use_count: " << wp_moved_to.use_count() << "\n";
        // wp_to_move should now be null/empty
    }

    // 5. Reset
    {
        std::cout << "\nTest 5: weak_ptr::reset()\n";
        shared_ptr<Resource> sp5(new Resource(50));
        weak_ptr<Resource> wp5(sp5);
        
        wp5.reset();
        if (wp5.expired() && wp5.use_count() == 0) {
            std::cout << "Success: weak_ptr reset manually.\n";
        }
    }

    std::cout << "\n--- Tests Completed ---\n";
    return 0;
}

