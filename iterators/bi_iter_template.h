#ifndef F_ITER_TEMPLATE_H_GUARD
#define F_ITER_TEMPLATE_H_GUARD

#include "f_iter_template.h"

namespace data_struct
{
    template <typename T, typename Impl, typename Mut>
    class BidirectIterTemplate
        : public ForwardIterTemplate<T, Impl, Mut>
    {
        using Base = ForwardIterTemplate<T, Impl, Mut>;
        using Self = BidirectIterTemplate;

        friend typename Impl::Container;

    public:
        using iterator_tag = std::bidirectional_iterator_tag;
        
        using typename Base::difference_type;
        using typename Base::value_type;
        using typename Base::reference;
        using typename Base::pointer;

    public:
        using Base::impl;

        using Base::swap;
        using Base::operator*;
        using Base::operator->;
        using base::operator++;

    public:
        BidirectIterTemplate() noexcept = default;

        BidirectIterTemplate (Impl impl_) noexcept
            : Base (impl_)
        {}

        template <typename Mut_>
        BidirectIterTemplate (BidirectIterTemplate<T, Impl, Mut_> it) noexcept 
            : Base (it)
        {}

        Self& operator--() noexcept {
            impl.prev();
            return *this;
        }

        Self operator-- (int i) noexcept {
            auto tmp = *this;
            impl.prev();
            return tmp;
        }
    };
}

#endif