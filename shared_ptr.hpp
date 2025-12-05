#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

class CB {
    private:
        int shared_count;

    public:
        CB() : shared_count { 0 } {}

        void addSharedCount() noexcept { ++shared_count; }
        void removeSharedCount() noexcept { --shared_count; }
};

template<typename T>
class shared_ptr {
    private:
        T* data;
        CB* cb;

    public:
        explicit shared_ptr(T* ptr) noexcept;
        shared_ptr(const shared_ptr& s) noexcept;
        shared_ptr& operator=(const shared_ptr& s) noexcept;
        shared_ptr(shared_ptr&& s) noexcept;
        shared_ptr& operator=(shared_ptr&& s) noexcept;
        ~shared_ptr();

        void reset() noexcept;
        void reset(T*); 
};

#endif