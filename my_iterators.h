#ifndef MY_ITERATORS_H_GUARD
#define MY_ITERATORS_H_GUARD

#include "iterators/f_iter_template.h"
#include "iterators/bi_iter_template.h"
#include "iterators/rand_iter_template.h"

namespace data_struct
{
    template <typename T, typename Impl, typename Mut>
    using BaseContainerIter = ForwardIterTemplate<T, Impl, Mut>;

    
    template <typename T, typename Cont>
    struct PtrIter {
        bool equal(PtrIter const& rhs) const noexcept {
            return (ptr == rhs.ptr);
        }
            
        ptrdiff_t diff (PtrIter const& rhs) const noexcept {
            return ptr - rhs.ptr;
        }

        void next() noexcept {
            ++ptr;
        }

        void prev() noexcept {
            --ptr;
        }

        void plus (ptrdiff_t n) noexcept {
            ptr += n;
        }

        T& get_value() const noexcept {
            return *ptr;
        }

    public:
        using Container = Cont;

        T* ptr = nullptr;
    };
}

#endif