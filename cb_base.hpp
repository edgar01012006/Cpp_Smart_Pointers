#ifndef CB_BASE_HPP
#define CB_BASE_HPP

template <typename T>
class cb_base {
    private:
        long ref_count;
        long weak_count;
        T* data;

    public:
        cb_base(T* ptr = nullptr) : ref_count { 1 }, weak_count { 1 }, data { ptr } {}

        cb_base(const cb_base&) = delete;
        cb_base operator=(const cb_base&) = delete;

        void add_ref_count() { ++ref_count; }
        void add_weak_count() { ++weak_count; }

        void release_ref_count() {
            if (--ref_count == 0) {
                destroy_data();
                release_weak_count();
            }
        }
        void release_weak_count() {
            if (--weak_count == 0) {
                destroy_self();
            }
        }

        void destroy_data() { delete data; }
        void destroy_self() { delete this; }

        long get_ref_count() const { return ref_count; }
        // long get_weak_count() const { return --weak_count; }
};

#endif