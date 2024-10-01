#ifndef MY_HASH_TABLE_H_GUARD
#define MY_HASH_TABLE_H_GUARD

#include "my_hash_set.h"

namespace data_struct
{
    template <typename Key, typename Value>
    struct KeyValue {
        bool operator== (KeyValue const& rhs) const noexcept {
            return key == rhs.key;
        }
        
        Key key;
        Value value;
    };


    template <typename Key, typename Value>
    struct DefaultHash<KeyValue<Key, Value>> {
        size_t operator() (KeyValue<Key, Value> const& kv) const {
            return DefaultHash<Key>{} (kv.key);
        }
    };


    template <typename Key, typename Value, typename Hash = DefaultHash<KeyValue<Key, Value>>>
    class HashTable {
        using Elem = KeyValue<Key, Value>;
        using Impl = HashSet<Elem, Hash>;

    public:
        using iterator       = typename Impl::iterator;
        using const_iterator = typename Impl::const_iterator;

    public:
        void swap (HashTable& rhs) noexcept {
            impl.swap(rhs.impl);
        }

        bool empty() const noexcept {
            return impl.empty();
        }

        std::size_t size() const noexcept {
            return impl.size();
        }

        const_iterator cbegin() const noexcept {
            return impl.cbegin();
        }

        const_iterator begin() const noexcept {
            return cbegin();
        }

        const_iterator cend() const noexcept {
            return impl.cend();
        }

        const_iterator end() const noexcept {
            return cend();
        }

        void erase (Key const& key) noexcept {
            impl.erase (
                Elem {key, Value{}}
            );
        }

        Value& operator[] (Key const& key) {
            Elem el {key, Value{}};
            impl.add (el);
            return impl.find (el)->value;
        }

        Value const& operator[] (Key const& key) const {
            auto it = find (key);

            if (it == end()) {
                throw std::invalid_argument (
                    "не существует элемента с таким ключом\n"
                );
            }

            return it->value;
        }

        const_iterator find (Key const& key) const noexcept {
            return impl.find (Elem {key, Value{}});
        }

    private:
        Impl impl;
    };


    template <typename Key, typename Value, typename Hash>
    void swap (HashTable<Key, Value, Hash>& lhs, HashTable<Key, Value, Hash>& rhs) noexcept {
        lhs.swap (rhs);
    }
}

#endif