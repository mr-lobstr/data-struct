#ifndef F_ITER_TEMPLATE_H_GUARD
#define F_ITER_TEMPLATE_H_GUARD

#include "my_iterators_fwd.h"

namespace data_struct
{
    template <typename T, typename Impl, typename Mut>
    class ForwardIterTemplate {
        using Self = ForwardIterTemplate;
        using Types = IterTraits<Self>;

        friend typename Impl::Container;
        friend ForwardIterTemplate<T, Impl, Const_tag>;;

    public:
        using iterator_tag    = typename Types::Tag;
        using difference_type = typename Types::Difference;

        using value_type = typename Types::Value;
        using reference  = typename Types::Reference;
        using pointer    = typename Types::Pointer;
        using Cont = typename Impl::Container;

    public:
        ForwardIterTemplate() noexcept = default;
        ~ForwardIterTemplate() noexcept = default;

        ForwardIterTemplate(Self const&) noexcept = default;
        Self& operator= (Self const&) noexcept = default;

        ForwardIterTemplate(Self&& rhs) noexcept
            : impl (std::exchange (rhs.impl, Impl{}))
        {}

        Self& operator= (Self&& rhs) noexcept {
            impl = std::exchange (rhs.impl, Impl{});
            return *this;
        }

        ForwardIterTemplate (Impl impl_) noexcept
            : impl (impl_)
        {}

        template <typename Mut_, typename = std::enable_if_t<std::is_same_v<Mut_, Mutable_tag>>>
        ForwardIterTemplate (ForwardIterTemplate<T, Impl, Mut_> const& it) noexcept 
            : impl (it.impl)
        {}

        friend
        bool operator== (Self const& lhs, Self const& rhs) noexcept {
            return lhs.impl.equal (rhs.impl);
        }

        friend
        bool operator!= (Self const& lhs, Self const& rhs) noexcept {
            return not (lhs == rhs);
        }

        reference operator*() const noexcept {
            return impl.get_value();
        }

        pointer operator->() const noexcept {
            return &operator*();
        }

        Self& operator++() noexcept {
            impl.next();
            return *this;
        }

        Self operator++ (int i) noexcept {
            auto tmp = *this;
            impl.next();
            return tmp;
        }

    protected:
        Impl impl{};
    };


    template <typename T, typename Impl>
    struct IterTraits<
        ForwardIterTemplate<T, Impl, Mutable_tag>
    > {
        using Tag        = std::forward_iterator_tag;
        using Difference = void;

        using Value     = T;
        using Reference = T&;
        using Pointer   = T*;
    };


    template <typename T, typename Impl>
    struct IterTraits<
        ForwardIterTemplate<T, Impl, Const_tag>
    > {
        using Tag        = std::forward_iterator_tag;
        using Difference = void;

        using Value     = T;
        using Reference = T const&;
        using Pointer   = T const*;
    };
}

#endif