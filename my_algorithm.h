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


    template <typename T>
    void range_init (T* begin, T* end, T const& value) {
        for_each (begin, end,
            [&] (auto& el) {
                new(&el) T {value};
            }
        );
    }


    template <typename InputIter, typename T>
    void range_init_copy (InputIter begin, InputIter end, T* out) {
        while (begin != end) {
            new(out) T {*begin};
            ++begin;
            ++out;
        }
    }


    template <typename InputIter, typename T>
    void range_init_move (InputIter begin, InputIter end, T* out) {
        while (begin != end) {
            new(out) T {std::move (*begin)};
            ++begin;
            ++out;
        }
    }


    template <typename InputIter, typename OutputIter>
    void move (InputIter begin, InputIter end, OutputIter out) {
        while (begin != end) {
            *out = std::move (*begin);
            ++begin;
            ++out;
        }
    }


    template <typename Iter>
    void shift_left (Iter begin, Iter end) {
        move (begin+1, end, begin);
    }


    template <typename Iter>
    void shift_right (Iter begin, Iter end) {
        while (--end != begin) {
            *end = std::move (*(end-1));
        }
    }
}

#endif