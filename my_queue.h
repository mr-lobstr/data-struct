#ifndef MY_QUEUE_H_GUARD
#define MY_QUEUE_H_GUARD

#include "my_flist.h"

namespace data_struct
{
    template <typename T>
    class Queue {
    public:
        using iterator       = typename FList<T>::iterator;
        using const_iterator = typename FList<T>::const_iterator;

    public:
        Queue() noexcept = default;
        ~Queue() noexcept = default;

        Queue (Queue&& rhs) noexcept {
            if (not rhs.empty()) {
                size_   = std::exchange (rhs.size_, 0);
                flist   = std::move (rhs.flist);
                prevEnd = std::move (rhs.flist);
            }
        }

        Queue (Queue const& rhs)
        {
            for_each (rhs.begin(), rhs.end(),
                [&] (auto& value) {
                    push_back (value);
                }
            );
        }

        Queue& operator= (Queue&& rhs) noexcept {
            if (this != &rhs) {
                auto tmp = std::move (rhs);
                swap (tmp);
            }
            return *this;
        }

        Queue& operator= (Queue const& rhs) {
            if (this != &rhs) {
                auto tmp = rhs;
                swap (tmp);
            }
            return *this;
        }

        const_iterator begin() const noexcept {
            return flist.cbegin();
        }

        const_iterator end() const noexcept {
            return flist.cend();
        }

        std::size_t size() const noexcept {
            return size_;
        }

        void swap (Queue& rhs) noexcept {
            std::swap (*this, rhs);
        }

        void push_back (T const& value) {
            insert_after (prevEnd, value);
            ++prevEnd;
            ++size_;
        }

        void pop_front() noexcept {
            flist.pop_front();
            --size_;
        }

        T const& front() const noexcept {
            return flist.front();
        }

        T const& back() const noexcept {
            return *prevEnd;
        }

    private:
        std::size_t size_ = 0;

        FList<T> flist{};
        const_iterator prevEnd = list.prev_begin();
    };


    template <typename T>
    void swap (Queue<T>& lhs, Queue<T>& rhs) noexcept {
        lhs.swap (rhs);
    }
}
#endif