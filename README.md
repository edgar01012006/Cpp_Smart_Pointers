# 🔧 Custom Smart Pointer Implementations (C++)

A lightweight C++ project implementing custom `shared_ptr`, `unique_ptr`, and `weak_ptr` classes.  
These implementations demonstrate how smart pointers work internally, including ownership models, reference counting (control blocks), memory management, and RAII behavior.



This project includes:

- **Exclusive ownership** with move semantics (`unique_ptr`)
- **Reference-counted shared ownership** (`shared_ptr`)
- **Non-owning observer pointers** (`weak_ptr`) to break circular dependencies
- **Custom Control Block** (`cb_base`) to manage shared and weak reference counts
- **Memory-safe RAII patterns** with manual implementation of Rule of Five

---

## Project Structure

```text
├── cb_base.hpp          # Base control block for reference counting
├── shared_ptr.hpp       # Shared ownership implementation
├── shared_ptr_test.cpp  # Tests for shared_ptr
├── unique_ptr.hpp       # Exclusive ownership implementation
├── unique_ptr_test.cpp  # Tests for unique_ptr
├── weak_ptr.hpp         # Non-owning observer implementation
└── weak_ptr_test.cpp    # Tests for weak_ptr and lock() mechanism
```

---

## Build & Run

### 1. Unique Pointer Tests
```bash
g++ -std=c++11 unique_ptr_test.cpp -o unique_ptr_test
./unique_ptr_test
```

### 2. Shared Pointer Tests
```bash
g++ -std=c++11 shared_ptr_test.cpp -o shared_ptr_test
./shared_ptr_test
```

### 3. Weak Pointer Tests
```bash
g++ -std=c++11 weak_ptr_test.cpp -o weak_ptr_test
./weak_ptr_test
```

---