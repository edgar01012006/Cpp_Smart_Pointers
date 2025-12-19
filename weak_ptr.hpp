#ifndef WEAK_PTR_HPP
#define WEAK_PTR_HPP

#include "cb_base.hpp"
#include "shared_ptr.hpp"

template <typename T>
class weak_ptr {
    friend class shared_ptr<T>;

    private:
        T* data;
        cb_base<T>* cb;

    public:
        weak_ptr() noexcept;

        // TODO: this might be error because of template
        weak_ptr(const shared_ptr<T>& r) noexcept;
        weak_ptr& operator=(const shared_ptr<T>& r) noexcept;

        weak_ptr(const weak_ptr& r) noexcept;
        weak_ptr& operator=(const weak_ptr& r) noexcept;

        weak_ptr(weak_ptr&& r) noexcept;
        weak_ptr& operator=(weak_ptr&& r) noexcept;

        ~weak_ptr();

        void reset() noexcept;

        long use_count() const noexcept;

        bool expired() const noexcept;

        shared_ptr<T> lock() const noexcept;

};

template<typename T>
weak_ptr<T>::weak_ptr() noexcept
    : data { nullptr }, cb { nullptr } {}

template<typename T>
weak_ptr<T>::weak_ptr(const shared_ptr<T>& r) noexcept
    : data { r.data }, cb { r.cb } {
    if (cb != nullptr) {
        cb->add_weak_count();
    }
}

template<typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const shared_ptr<T>& r) noexcept {
    if (this == &r) { return *this; }
    data = r.data;
    cb = r.cb;
    if (cb != nullptr) {
        cb->add_weak_count();
    }
    return *this;
}

template<typename T>
weak_ptr<T>::weak_ptr(const weak_ptr& r) noexcept
    : data { r.data }, cb { r.cb } {
    if (cb != nullptr) {
        cb->add_weak_count();
    }
}

template<typename T>
weak_ptr<T>& weak_ptr<T>::operator=(const weak_ptr& r) noexcept {
    if (this == &r) { return *this; }
    data = r.data;
    cb = r.cb;

    if (cb != nullptr) {
        cb->add_weak_count();
    }
    return *this;
}

template<typename T>
weak_ptr<T>::weak_ptr(weak_ptr&& r) noexcept
    : data { r.data }, cb { r.cb } {
    r.data = nullptr;
    r.cb = nullptr;
}

template<typename T>
weak_ptr<T>& weak_ptr<T>::operator=(weak_ptr&& r) noexcept {
    if (this == &r) { return *this; }
    data = r.data;
    cb = r.cb;
    r.data = nullptr;
    r.cb = nullptr;
    return *this;
}

template<typename T>
weak_ptr<T>::~weak_ptr() {
    reset();
}

template<typename T>
void weak_ptr<T>::reset() noexcept {
    if (cb != nullptr) {
        cb->release_weak_count();
    }
    data = nullptr;
    cb = nullptr;
}

template<typename T>
long weak_ptr<T>::use_count() const noexcept {
    if (cb != nullptr) {
        return cb->get_ref_count();
    }
    return 0;
}

template<typename T>
bool weak_ptr<T>::expired() const noexcept {
    return use_count() == 0;
}

template<typename T>
shared_ptr<T> weak_ptr<T>::lock() const noexcept {
    return expired() ? shared_ptr<T>() : shared_ptr<T>(*this);
}

#endif