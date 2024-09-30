#ifndef MY_ITERATORS_H_GUARD
#define MY_ITERATORS_H_GUARD

#include "iterators/f_iter_template.h"
#include "iterators/bi_iter_template.h"
#include "iterators/rand_iter_template.h"

namespace data_struct
{
    template <typename T, typename Impl, typename Mut>
    using BaseContainerIter = ForwardIterTemplate<T, Impl, Mut>;
}

#endif