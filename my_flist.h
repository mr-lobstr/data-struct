#ifndef MY_FORWARD_LIST_GUARD_H
#define MY_FORWARD_LIST_GUARD_H

#include <utility>
#include "my_iterators.h"

namespace data_struct
{
    template <typename T>
    class FList {
        struct Head {
            Head* next = nullptr;
        };

        struct Node: public Head {
            T value;
        };

        struct IterImpl {
            T& get_value() const noexcept {
                return get_ptr_node (pHead)->value;
            }

            void next() noexcept {
                pHead = pHead->next;
            }

            bool equal(IterImpl const& rhs) const noexcept {
                return (pHead == rhs.pHead);
            }

        public:
            using Container = FList;

            Head* pHead = nullptr;
        };

    public:
        using iterator       = ForwardIterTemplate<T, IterImpl, Mutable_tag>;
        using const_iterator = ForwardIterTemplate<T, IterImpl, Const_tag>;
    
    public:
        FList() noexcept = default;

        FList (FList&& rhs) noexcept
            : prevFirst (std::exchange (rhs.prevFirst, Head{}))
        {}
    
        FList (FList const& rhs) {
            auto pLast = &prevFirst;

            for_each (rhs.begin(), rhs.end(),
                [&, this] (auto& value) {
                    push_front (value);
                    pLast = pLast->next;
                }
            );
        }

        FList& operator= (FList&& rhs) noexcept {
            if (this != &rhs) {
                auto tmp = std::move (rhs);
                swap (tmp);
            } 
            return *this;
        }

        FList& operator= (FList const& rhs) {
            if (this != &rhs) {
                auto tmp = rhs;
                swap (tmp);
            }
            return *this;
        }

        ~FList() noexcept {
            while (not empty()) {
                pop_front();
            }
        }

        iterator iter_begin() {
            return IterImpl {prevFirst.next};
        }

        bool empty() const noexcept {
            return prevFirst.next == nullptr;
        }

        void swap (FList& rhs) noexcept {
            std::swap(*this, rhs);
        }

        void insert_after (const_iterator it, T const& value) {
            auto pPrev = it.impl.pHead;
            auto oldNext = pPrev->next;
            pPrev->next = new Node {oldNext, value};
        }

        void push_front (T const& value) {
            insert_after (prev_begin(), value);
        }

        void erase_after (const_iterator it) noexcept {
            auto pPrev = it.impl.pHead;
            auto oldFirst = get_ptr_node (pPrev->next);
            pPrev->next = oldFirst->next;
            delete (oldFirst);
        }

        iterator find_prev (T const& value) noexcept {
            auto it = prev_begin();

            while (next_iter(it) != end()) {
                if (*next_iter(it) == value)
                    break;
                ++it;
            }

            return it;
        }

        const_iterator find_prev (T const& value) const noexcept {
            return find_prev (value);
        }

        void pop_front() noexcept {
            erase_after (prev_begin());
        }

        iterator prev_begin() noexcept {
            return IterImpl {&prevFirst};
        }

        const_iterator prev_begin() const noexcept {
            return IterImpl {const_cast<Head*> (&prevFirst)};
        }

        iterator begin() noexcept {
            return IterImpl {prevFirst.next};
        }

        const_iterator begin() const noexcept {
            return IterImpl {prevFirst.next};
        }

        iterator end() noexcept {
            return IterImpl {nullptr};
        }

        const_iterator end() const noexcept {
            return IterImpl {nullptr};
        }

        T& front() noexcept {
            return *begin();
        }

        T const& front() const noexcept {
            return *begin();
        }

    private:
        static
        Node* get_ptr_node (Head* pHead) noexcept {
            return static_cast<Node*> (pHead);
        }
    
    private:
        Head prevFirst{};
    };


    template <typename T>
    void swap (FList<T>& lhs, FList<T>& rhs) noexcept {
        lhs.swap (rhs);
    }
}
#endif