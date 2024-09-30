#ifndef MY_ALGORITHM_H_GUARD
#define MY_ALGORITHM_H_GUARD

namespace data_struct
{
    template <typename Iter, typename Action>
    void for_each (Iter begin, Iter end, Action action) {
        while (begin != end) {
            action (*begin);
            ++begin;
        }
    }
}

#endif