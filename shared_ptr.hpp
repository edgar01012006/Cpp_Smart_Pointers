#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <string>

#include "cb_base.hpp"

class bad_weak_ptr {
    private:
        std::string m_msg;

    public:
        bad_weak_ptr(const std::string& msg) : m_msg { msg } {}
        std::string what() const noexcept { return m_msg; }
};

template<typename T>
class weak_ptr;

template<typename T>
class shared_ptr {
    friend class weak_ptr<T>;

    private:
        T* data;
        cb_base<T>* cb;

    public:
        shared_ptr() noexcept;
        explicit shared_ptr(T* ptr) noexcept;

        shared_ptr(const weak_ptr<T>& r);

        shared_ptr(const shared_ptr& s) noexcept;
        shared_ptr& operator=(const shared_ptr& s) noexcept;

        shared_ptr(shared_ptr&& s) noexcept;
        shared_ptr& operator=(shared_ptr&& s) noexcept;

        ~shared_ptr();

        T* get() const noexcept;

        long use_count() const noexcept;

        explicit operator bool() const noexcept;

        T& operator*() const noexcept;
        T* operator->() const noexcept;

        void reset() noexcept;
        void reset(T* ptr); 
};

template<typename T>
shared_ptr<T>::shared_ptr() noexcept : data { nullptr }, cb { nullptr } {}

template<typename T>
shared_ptr<T>::shared_ptr(T* ptr) noexcept : data { ptr }, cb { new cb_base<T>(data) } {}

template<typename T>
shared_ptr<T>::shared_ptr(const weak_ptr<T>& r) {
    if (r.use_count() == 0) { throw bad_weak_ptr("bad weak ptr"); }
    data = r.data;
    cb = r.cb;
    cb->add_ref_count();
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr& s) noexcept 
    : data { nullptr }, cb { nullptr } {
    if (s.data != nullptr) {
        data = s.data;
        cb = s.cb;
        cb->add_ref_count();
    }
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(const shared_ptr& s) noexcept {
    if (this == &s) { return *this; }
    reset();
    if (s.data != nullptr) {
        data = s.data;
        cb = s.cb;
        cb->add_ref_count();
    }
    return *this;
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr&& s) noexcept 
    : data { s.data }, cb { s.cb } {
    s.data = nullptr;
    s.cb = nullptr;
}

template<typename T>
shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr&& s) noexcept {
    if (this == &s) { return *this; }
    reset();
    data = s.data;
    cb = s.cb;
    s.data = nullptr;
    s.cb = nullptr;
    return *this;
}

template<typename T>
shared_ptr<T>::~shared_ptr() { reset(); }

template<typename T>
T* shared_ptr<T>::get() const noexcept { return data; }

template<typename T>
long shared_ptr<T>::use_count() const noexcept { return cb->get_ref_count(); }

template<typename T>
shared_ptr<T>::operator bool() const noexcept { return get() != nullptr ? true : false; } 

template<typename T>
T& shared_ptr<T>::operator*() const noexcept { return *get(); }

template<typename T>
T* shared_ptr<T>::operator->() const noexcept { return get(); }

template<typename T>
void shared_ptr<T>::reset() noexcept {
    if (data == nullptr) { return; }
    else { cb->release_ref_count(); }
    data = nullptr;
    cb = nullptr;
}

template<typename T>
void shared_ptr<T>::reset(T* ptr) {
    reset();
    data = ptr;
    cb = new cb_base<T>(data);
}

#endif