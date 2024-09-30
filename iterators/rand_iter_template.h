#ifndef RAND_ITER_TEMPLATE_H_GUARD
#define RAND_ITER_TEMPLATE_H_GUARD

#include "bi_iter_template.h"

namespace data_struct
{
    template <typename T, typename Impl, typename Mut>
    class RandomIterTemplate
        : public BidirectIterTemplate<T, Impl, Mut>
    {
        using Base = BidirectIterTemplate<T, Impl, Mut>;
        using Self = RandomIterTemplate;

        friend typename Impl::Container;

    public:
        using iterator_tag = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;

        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;

    public:
        using Base::impl;

        using Base::operator*;
        using Base::operator->;
        using Base::operator++;
        using Base::operator--;

    public:
        RandomIterTemplate() noexcept = default;

        RandomIterTemplate (Impl impl_) noexcept
            : Base (impl_)
        {}

        template <typename Mut_>
        RandomIterTemplate (RandomIterTemplate<T, Impl, Mut_> const& it) noexcept 
            : Base (it)
        {}

        friend
        difference_type operator- (Self const& lhs, Self const& rhs) noexcept {
            return lhs.impl.diff (rhs.impl);
        }

        friend
        bool operator< (Self const& lhs, Self const& rhs) noexcept {
            return (lhs - rhs) < 0;
        }

        friend
        bool operator> (Self const& lhs, Self const& rhs) noexcept {
            return (lhs - rhs) > 0;
        }

        friend
        bool operator<= (Self const& lhs, Self const& rhs) noexcept {
            return lhs < rhs or lhs == rhs;
        }

        friend
        bool operator>= (Self const& lhs, Self const& rhs) noexcept {
            return lhs > rhs or lhs == rhs;
        }

        Self& operator+= (difference_type n) noexcept {
            impl.plus (n);
            return *this;
        }

        Self& operator-= (difference_type n) noexcept {
            impl.plus (-n);
            return *this;
        }

        friend
        Self operator+ (Self it, difference_type n) noexcept {
            return (it += n);
        }

        friend
        Self operator+ (difference_type n, Self it) noexcept {
            return it + n;
        }

        friend
        Self operator- (Self it, difference_type n) noexcept {
            return (it -= n);
        }

        value_type operator[] (std::size_t ind) noexcept {
            return *(ind + *this);
        }
    };
}

#endif