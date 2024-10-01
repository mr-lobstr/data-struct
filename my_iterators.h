#ifndef MY_ITERATORS_H_GUARD
#define MY_ITERATORS_H_GUARD

#include "iterators/f_iter_template.h"
#include "iterators/bi_iter_template.h"
#include "iterators/rand_iter_template.h"

namespace data_struct
{
    template <typename T, typename Impl, typename Mut>
    using BaseContainerIter = ForwardIterTemplate<T, Impl, Mut>;


    template <typename Iter>
    Iter next_iter (Iter it) noexcept {
        return ++it;
    }


    template <typename Container>
    using get_iterator_t = typename Container::iterator;


    template <typename Container>
    using get_const_iterator_t = typename Container::const_iterator;
}

#endif