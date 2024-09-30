#ifndef MY_stackImplH_GUARD
#define MY_stackImplH_GUARD

#include "dynamic_array.h"

namespace data_struct
{
    template <typename T>
    class Stack {
    public:
        using iterator       = typename DynamicArray<T>::iterator;
        using const_iterator = typename DynamicArray<T>::const_iterator;

    public:
        const_iterator cbegin() const noexcept {
            return stackImpl.cbegin();
        }

        const_iterator cend() const noexcept {
            return stackImpl.end();
        }

        void push (T const& value) {
            stackImpl.push_back (value);
        }

        T& top() noexcept {
            return stackImpl.back();
        }

        T const& top() const noexcept {
            return stackImpl.back();
        }

        void pop() noexcept {
            stackImpl.pop_back();
        }

        bool empty() const noexcept {
            return stackImpl.empty();
        }

        std::size_t size() const noexcept {
            return stackImpl.size();
        }

        std::size_t capacity() const noexcept {
            return stackImpl.capacity();
        }

        void reserve (std::size_t newCapacity) {
            stackImpl.reserve (newCapacity);
        }

    private:
        DynamicArray<T> stackImpl;
    };


    template <typename T>
    void swap (Stack<T>& lhs, Stack<T>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif