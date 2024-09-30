#ifndef DYNAMIC_ARRAY_GUARD_H
#define DYNAMIC_ARRAY_GUARD_H

#include <stdexcept>
#include <utility>
#include "my_iterators.h"
#include "my_algorithm.h"

namespace data_struct
{
    template <typename T>
    class DynamicArray {  
        using IterImpl = PtrIter<T, DynamicArray>;

    public:
        using iterator       = RandomIterTemplate<T, IterImpl, Mutable_tag>;
        using const_iterator = RandomIterTemplate<T, IterImpl, Const_tag>;

    public:
        DynamicArray() noexcept = default;

        DynamicArray (DynamicArray&& rhs)
            : data (std::exchange(rhs.data,  Data{}))
        {}

        DynamicArray (DynamicArray const& rhs) {
            mem_alloc_and_data_init (rhs.size(), rhs.size());
            range_init_copy (rhs.begin(), rhs.end(), begin());
        }

        DynamicArray (std::size_t count, T const& value = T()) {
            mem_alloc_and_data_init (count, count);
            range_init (data.begin, data.avail, value);
        }

        DynamicArray& operator= (DynamicArray&& rhs) noexcept {
            if (this == &rhs) {
                auto tmp {std::move (rhs)};
                swap (tmp);
            }
            return *this;
        }

        DynamicArray& operator= (DynamicArray const& rhs) {
            if (this == &rhs) {
                auto tmp {rhs};
                swap (tmp);
            }
            return *this;
        }

        ~DynamicArray() noexcept {
            resize(0);
            mem_free (data.begin);
        }

        iterator begin() noexcept {
            return IterImpl {data.begin};
        }

        const_iterator cbegin() const noexcept {
            return IterImpl {const_cast<int*> (data.begin)};
        }

        const_iterator begin() const noexcept {
            return cbegin();
        }

        iterator end() noexcept {
            return IterImpl {data.avail};
        }

        const_iterator cend() const noexcept {
            return IterImpl {const_cast<int*> (data.avail)};
        }

        const_iterator end() const noexcept {
            return cend();
        }

        void swap (DynamicArray& rhs) noexcept {
            std::swap (data, rhs.data);
        }

        std::size_t size() const noexcept {
            return data.avail - data.begin;
        }

        std::size_t capacity() const noexcept {
            return data.limit - data.begin;
        }

        bool empty() const noexcept {
            return size() == 0;
        }

        void reserve (std::size_t newCapacity) {
            realloc_if_capacity_less (newCapacity, newCapacity);
        }

        void resize (std::size_t newSize) {
            reserve (newSize);
        
            while (size() != newSize) {
                size() < newSize ? push_back (T{})
                                 : pop_back();
            }
        }

        T& operator[] (std::size_t ind) noexcept {
            return begin()[ind];
        }

        T const& operator[] (std::size_t ind) const noexcept {
            return begin()[ind];
        }

        T& front () noexcept {
            return *begin();
        }

        T const& front () const noexcept {
            return *begin();
        }

        T& back () noexcept {
            return *--end();
        }

        T const& back () const noexcept {
            return *--end();
        }

        void push_back (T const& value) {
            reserve_before_insert();
            new(data.avail) T {value};
            ++data.avail;
        }

        void pop_back() noexcept {
            --data.avail;
            data.avail->~T();
        }

        void insert (iterator it, T const& value) {
            push_back (T{});
            shift_right (it, end());
            *it = value;
        }

        void erase (iterator it) {
            shift_left (it, end());
            pop_back();
        }

    private:
        void mem_alloc_and_data_init (std::size_t size_, std::size_t capacity_) {        
            auto mem = reinterpret_cast<T*> (
                ::operator new (sizeof(T) * capacity_)
            );

            data.begin = mem;
            data.avail = mem + size_;
            data.limit = mem + capacity_;
        }

        void mem_free (T* ptr) noexcept {
            ::operator delete(ptr);
        }

        void realloc_if_capacity_less (std::size_t lowerBound, std::size_t newCapacity) {
            if (capacity() >= lowerBound)
                return;

            auto oldBeg = begin();
            auto oldEnd = end();
            
            mem_alloc_and_data_init (size(), newCapacity);
            range_init_move (oldBeg, oldEnd, data.begin);
            mem_free (&*oldBeg);
        }

        void reserve_before_insert() {
            realloc_if_capacity_less(size() + 1, size() * 2);
        }

    private:
        struct Data {
            T* begin = nullptr;
            T* avail = nullptr;
            T* limit = nullptr;
        };

        Data data{};
    };

    template <typename T>
    void swap (DynamicArray<T>& lhs, DynamicArray<T>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif