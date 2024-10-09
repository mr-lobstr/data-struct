#ifndef JUST_POINTER_H_GUARD
#define JUST_POINTER_H_GUARD

#include "iterators_general.h"

namespace data_struct
{
    template <typename T>
    class JustPointer
    {
        using Self = JustPointer;
        friend JustPointer<const T>;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::ptrdiff_t;

        using value_type = std::remove_cv_t<T>;
        using reference  = T&;
        using pointer    = T*;

    public:
        JustPointer()  noexcept = default;
        ~JustPointer() noexcept = default;

        JustPointer (Self const&)     noexcept = default;
        Self& operator= (Self const&) noexcept = default;

        JustPointer (Self&& rhs) noexcept 
            : ptr_ (std::exchange (rhs.ptr_, nullptr))
        {}

        Self& operator= (Self&& rhs) noexcept {
            ptr_ = std::exchange (rhs.ptr_, nullptr);
            return *this;
        }

        JustPointer (T* p) noexcept
            : ptr_ (const_cast<value_type*> (p))
        {}

        template <typename T1, typename = std::enable_if_t<!std::is_const_v<T1>>>
        JustPointer (JustPointer<T1> rhs) noexcept
            : ptr_ (rhs.ptr_)
        {}

        value_type* ptr() const noexcept {
            return ptr_;
        }

        reference operator*() const noexcept {
            return *ptr_;
        }

        pointer operator->() const noexcept {
            return ptr_;
        }

        Self& operator++() noexcept {
            ++ptr_;
            return *this;
        }

        Self operator++(int i) noexcept {
            return ptr_++;
        }

        Self& operator--() noexcept {
            --ptr_;
            return *this;
        }

        Self operator--(int i) noexcept {
            return ptr_--;
        }

        friend
        bool operator== (Self const& lhs, Self const& rhs) noexcept {
            return lhs.ptr_ == rhs.ptr_;
        }

        friend
        bool operator!= (Self const& lhs, Self const& rhs) noexcept {
            return not (lhs == rhs);
        }

        friend
        difference_type operator- (Self const& lhs, Self const& rhs) noexcept {
            return lhs.ptr_ - rhs.ptr_;
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

        Self& operator+= (std::ptrdiff_t n) noexcept {
            ptr_ += n;
            return *this;
        }

        Self& operator-= (std::ptrdiff_t n) noexcept {
            ptr_ -= n;
            return *this;
        }

        friend
        Self operator+ (Self it, std::ptrdiff_t n) noexcept {
            return (it += n);
        }

        friend
        Self operator+ (std::ptrdiff_t n, Self it) noexcept {
            return it + n;
        }

        friend
        Self operator- (Self it, std::ptrdiff_t n) noexcept {
            return (it -= n);
        }

        reference operator[] (std::size_t ind) noexcept {
            return *(ind + *this);
        }

    private:
        value_type* ptr_ = nullptr;
    };
}

#endif