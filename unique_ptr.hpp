#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

template <typename T>
class unique_ptr {
    private:
        T* data;

    public:
        unique_ptr() noexcept;
        explicit unique_ptr(T* ptr) noexcept;
        unique_ptr(const unique_ptr& u) = delete;
        unique_ptr& operator=(const unique_ptr& u) = delete;
        unique_ptr(unique_ptr&& u) noexcept;
        unique_ptr& operator=(unique_ptr&& u) noexcept;
        ~unique_ptr();

        T* release() noexcept;
        void reset(T* ptr = nullptr) noexcept;

        T* get() const noexcept;
        explicit operator bool() const noexcept;

        T& operator*() const;
        T* operator->() const noexcept;

        template<typename U>
        friend bool operator==(const unique_ptr<U>& u1, const unique_ptr<U>& u2);

};

template<typename T>
unique_ptr<T>::unique_ptr() noexcept : data { nullptr } {}

template<typename T>
unique_ptr<T>::unique_ptr(T* ptr) noexcept : data { ptr } {}

template<typename T>
unique_ptr<T>::unique_ptr(unique_ptr&& u) noexcept : data { u.data } {
    u.data = nullptr;
}

template<typename T>
unique_ptr<T>& unique_ptr<T>::operator=(unique_ptr&& u) noexcept {
    if (this != &u) {
        delete data;
        data = u.data;
        u.data = nullptr;
    }
    return *this;
}

template<typename T>
unique_ptr<T>::~unique_ptr() {
    reset();
}

template <typename T>
T* unique_ptr<T>::release() noexcept {
    T* tmp = data;
    data = nullptr;
    return tmp;
}

template<typename T>
void unique_ptr<T>::reset(T* ptr) noexcept {
    delete data;
    data = ptr;
}

template<typename T>
T* unique_ptr<T>::get() const noexcept {
    return data;
}

template<typename T>
unique_ptr<T>::operator bool() const noexcept {
    return data != nullptr ? true : false;
}

template<typename T>
T& unique_ptr<T>::operator*() const {
    return *data;
}

template<typename T>
T* unique_ptr<T>::operator->() const noexcept {
    return get();
}

template<typename U>
bool operator==(const unique_ptr<U>& u1, const unique_ptr<U>& u2) {
    return u1.get() == u2.get();
}

#endif