#ifndef MY_ITERATORS_FWD_H_GUARD
#define MY_ITERATORS_FWD_H_GUARD

#include <type_traits>
#include <iterator>
#include "../my_algorithm.h"

namespace data_struct
{
    struct Mutable_tag;
    struct Const_tag;


    template <typename Iter>
    struct IterOutTypes;


    template <typename T, typename Impl, typename Mut>
    class ForwardIterTemplate;


    template <typename T, typename Impl, typename Mut>
    class BidirectIterTemplate;
}

#endif