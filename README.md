# 🔧 Custom Smart Pointer Implementations (C++)

A lightweight C++ project implementing custom `shared_ptr` and `unique_ptr` classes.  
These implementations demonstrate how smart pointers work internally, including ownership models, memory management, and RAII behavior.

This project includes:

- Reference-counted shared ownership (`shared_ptr`)
- Exclusive ownership with move semantics (`unique_ptr`)
- Manually implemented constructors, destructors, and copy/move operators
- Memory-safe RAII patterns

---

## Project Structure

```
├── shared_ptr.hpp
├── shared_ptr_test.cpp
├── unique_ptr.hpp
└── unique_ptr_test.cpp
```

---

## Build & Run

### Compile Shared Pointer Tests
```bash
g++ -std=c++11 shared_ptr_test.cpp -o shared_ptr_test
./shared_ptr_test
```

### Compile Unique Pointer Tests
```bash
g++ -std=c++11 unique_ptr_test.cpp -o unique_ptr_test
./unique_ptr_test
```

---
