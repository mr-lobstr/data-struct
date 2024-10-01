#ifndef MY_HASH_SET_H_GUARD
#define MY_HASH_SET_H_GUARD

#include "dynamic_array.h"
#include "my_flist.h"

namespace data_struct
{
    template <typename T>
    struct DefaultHash;


    template <typename T, typename Hash = DefaultHash<T>>
    class HashSet {
        using Bucket = FList<T>;
        using Array  = DynamicArray<Bucket>;

        using buckets_iterator  = typename Array::iterator;
        using elements_iterator = typename Bucket::iterator;

        struct IterImpl {
            using Container = HashSet;

        public:
            bool equal (IterImpl const& rhs) const noexcept {
                if (is_end() or rhs.is_end())
                    return is_end() and rhs.is_end();
                
                return prevElemIt == rhs.prevElemIt;
            }

            void next() noexcept {               
                ++prevElemIt;

                if (not is_end()) 
                    return;
                
                while (++bucketIt != endIt and bucketIt->empty())
                    ;

                if (bucketIt != endIt) {
                    prevElemIt = bucketIt->prev_begin();
                }           
            }

            auto& get_value() const noexcept {
                return *elem_it();
            }
        
        private:
            auto elem_it() const noexcept {
                return next_iter(prevElemIt);
            }

            bool is_end() const noexcept {
                return bucketIt == endIt
                    or elem_it() == bucketIt->end();
            }

        public:
            buckets_iterator  bucketIt{};
            buckets_iterator  endIt{};
            elements_iterator prevElemIt{};
        }; 

    public:
        using iterator       = ForwardIterTemplate<T, IterImpl, Mutable_tag>;
        using const_iterator = ForwardIterTemplate<T, IterImpl, Const_tag>;

    public:
        HashSet() noexcept = default;
        ~HashSet() noexcept = default;

        HashSet (HashSet&& rhs) noexcept
            : array (std::move (rhs.array))
            , hash (std::move (rhs.hash))
            , size_ (std::exchange (rhs.size_, 0))
        {}

        HashSet (HashSet const& rhs) noexcept
            : array (rhs.array)
            , hash (rhs.hash)
            , size_ (rhs.size_)
        {}

        HashSet& operator= (HashSet&& rhs)
        {
            if (this == &rhs) {
                auto tmp {std::move (rhs)};
                swap (tmp);
            }
            return *this;
        }

        HashSet& operator= (HashSet const& rhs)
        {
            if (this == &rhs) {
                auto tmp {rhs};
                swap (tmp);
            }
            return *this;
        }
       
        void swap (HashSet& rhs) noexcept {
            using std::swap;

            swap (array, rhs.array);
            swap (hash, rhs.hash);
            swap (size_, rhs.size_);
        }

        bool empty() const noexcept {
            return size() == 0;
        }

        std::size_t size() const noexcept {
            return size_;
        }

        iterator begin() noexcept {
            return begin_iter_impl();
        }

        const_iterator cbegin() const noexcept {
            return begin_iter_impl();
        }

        const_iterator begin() const noexcept {
            return cbegin();
        }

        iterator end() noexcept {
            return IterImpl {
                array.end(), array.end(), elements_iterator{}
            };
        }

        const_iterator cend() const noexcept {
            auto [beg, end] = begin_end();
            return IterImpl {end, end, elements_iterator{}};
        }

        const_iterator end() const noexcept {
            return cend();
        }

        void erase (T const& value) noexcept {
            if (auto it = find (value); it != end()) {
                auto [bucketIt, _, prevIt] = it.impl;

                bucketIt->erase_after (prevIt);
                --size_;
            }
        }

        void add (T const& value) {
            if (size() >= buckets_cnt() * middleMaxDepth) {
                refill();
            }

            if (auto pos = find (value); pos == end()) {
                push_to_bucket (value);
            }
        }

        iterator find (T const& value) noexcept {
            return find_ (value);
        }

        const_iterator find (T const& value) const noexcept {
            return find_ (value);
        };

    private:
        std::size_t buckets_cnt() const noexcept {
            return array.size();
        }

        std::size_t bucket_number (T const& value) const noexcept {
            return hash (value) % buckets_cnt();
        }

        auto begin_end() const noexcept {
            auto& arr = const_cast<Array&> (array);
            return make_pair (arr.begin(), arr.end());
        }

        auto begin_iter_impl () const noexcept {
            auto [beg, end] = begin_end();

            beg = find_if (beg, end, [] (auto& bucket) {
                return not bucket.empty();
            });

            return IterImpl {
                beg, end, (beg != end ? beg->prev_begin() : elements_iterator{})
            };
        }

        auto find_ (T const& value) const noexcept {
            auto [bucketIt, endIt] = begin_end();

            if (empty())
                return IterImpl {endIt, endIt, elements_iterator{}};

            bucketIt += bucket_number (value);
            auto prevElemIt = bucketIt->find_prev (value);

            return IterImpl {bucketIt, endIt, prevElemIt};
        }

        void push_to_bucket (T const& value) {
            auto bucketIt = array.begin() + bucket_number (value);
            bucketIt->push_front (value);
            ++size_;
        }

        void refill() {
            if (empty()) {
                array.resize (minBucketCnt);
                return;
            }
            
            HashSet newSet;
            newSet.array.resize (buckets_cnt() * 1.5);

            for_each (begin(), end(), [&] (auto& el) {
                newSet.push_to_bucket (el);
            });

            swap (newSet);
        }

    private:
        static const std::size_t middleMaxDepth = 5;
        static const std::size_t minBucketCnt = 100;

        Array array{};
        Hash hash{};
        std::size_t size_ = 0;
    };


    template <typename T, typename Hash>
    void swap (HashSet<T, Hash>& lhs, HashSet<T, Hash>& rhs) noexcept {
        lhs.swap (rhs);
    }
}

#endif