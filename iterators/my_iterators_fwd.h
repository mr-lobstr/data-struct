#ifndef MY_ITERATORS_FWD_H_GUARD
#define MY_ITERATORS_FWD_H_GUARD

#include <type_traits>
#include <iterator>
#include <utility>
#include "../my_algorithm.h"

namespace data_struct
{
    struct Mutable_tag;
    struct Const_tag;


    template <typename Iter>
    struct IterTraits {
        using Tag        = typename Iter::iterator_tag;
        using Difference = typename Iter::difference_type;

        using Value     = typename Iter::value_type;
        using Reference = typename Iter::reference;
        using Pointer   = typename Iter::pointer; 
    };


    template <typename T>
    struct IterTraits<T*> {
        using Tag        = std::random_access_iterator_tag;
        using Difference = std::ptrdiff_t;

        using Value     = std::remove_cv_t<T>;
        using Reference = T&;
        using Pointer   = T*; 
    };


    template <typename T, typename Impl, typename Mut>
    class ForwardIterTemplate;


    template <typename T, typename Impl, typename Mut>
    class BidirectIterTemplate;


    template <typename T, typename Impl, typename Mut>
    class RandomIterTemplate;
}

#endif