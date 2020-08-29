// Copyright (c) 2019-2020 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_INTERFACE
#define DATA_INTERFACE

#include <type_traits>
#include <data/container.hpp>

namespace data {
    
    namespace meta {
        
        template <typename X, typename it>
        class is_iterable {
            template <typename T, typename i> static auto test(int) -> typename 
                std::enable_if<std::is_same<decltype(std::declval<T>().begin()), i>::value && 
                    std::is_same<decltype(std::declval<T>().end()), i>::value, yes>::type;
            template <typename, typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<X, it>(0)), yes>::value;
        };
        
        template <typename X, typename it>
        class is_const_iterable {
            template <typename T, typename i> static auto test(int) -> typename 
                std::enable_if<std::is_same<decltype(std::declval<const T>().begin()), i>::value && 
                    std::is_same<decltype(std::declval<const T>().end()), i>::value, yes>::type;
            template <typename, typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<X, it>(0)), yes>::value;
        };
        
        template <typename...> class has_insert_method;
        
        template <typename list, typename element>
        class has_insert_method<list, element> {
            template <typename X> static auto test(int) -> typename 
                std::enable_if<std::is_same<decltype(std::declval<const X>().insert(std::declval<element>())), list>::value, yes>::type;
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<list>(0)), yes>::value;
        };
        
        template <typename map, typename key, typename val>
        class has_insert_method<map, key, val> {
            template <typename X> static auto test(int) -> typename 
                std::enable_if<std::is_same<decltype(std::declval<const X>().insert(std::declval<key>(), std::declval<val>())), map>::value, yes>::type;
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<map>(0)), yes>::value;
        };
        
        template <typename set, typename key>
        class has_remove_method {
            template <typename X> static auto test(int) -> typename std::enable_if<
                std::is_same<decltype(std::declval<const X>().remove(std::declval<const key>())), set>::value, yes>::type;
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<set>(0)), yes>::value;
        };
        
        template <typename list, typename element>
        class has_prepend_method {
            template <typename X> static auto test(int) -> decltype((void)(std::declval<const X>().prepend(std::declval<const element>()) == std::declval<list>()), yes());
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<list>(0)), yes>::value;
        };
        
        template <typename list, typename element>
        class has_append_method {
            template <typename X> static auto test(int) -> decltype((void)(std::declval<const X>().append(std::declval<const element>()) == std::declval<list>()), yes());
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<list>(0)), yes>::value;
        };
        
        template <typename tree>
        class has_left_method {
            template <typename X> static auto test(int) -> decltype((void)(std::declval<const X>().left() == std::declval<tree>()), yes());
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<tree>(0)), yes>::value;
        };
        
        template <typename tree>
        class has_right_method {
            template <typename X> static auto test(int) -> decltype((void)(std::declval<const X>().right() == std::declval<tree>()), yes());
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<tree>(0)), yes>::value;
        };
        
        template <typename con, typename seq>
        class has_values_method {
            template <typename X> static auto test(int) -> decltype((void)(std::declval<const X>().values() == std::declval<seq>()), yes());
            template <typename> static no test(...);
        public:
            static constexpr bool value = std::is_same<decltype(test<con>(0)), yes>::value;
        };
        
        template <typename X, bool has_right_method> struct right {
            X operator()(const X& x) {
                return x;
            }
            
            const X* const operator()(const X* x){
                return x;
            }
        };
        
        template <typename X> struct right<X, true> {
            X operator()(const X& x) {
                return x.right();
            }
        };
        
        template <typename X, bool has_left_method> struct left {
            X operator()(const X& x) {
                return x;
            }
            
            const X* const operator()(const X* x){
                return x;
            }
        };
        
        template <typename X> struct left<X, true> {
            X operator()(const X& x) {
                return x.left();
            }
            
            const X* operator()(const X* x){
                return x == nullptr ? nullptr : x->rest();
            }
        };
        
        template <typename X, typename E, bool has_insert_method> struct insert;
        
        template <typename X, typename E> struct insert<X, E, true> {
            X operator()(const X& x, const E& e) {
                return x.insert(e);
            }
        };
        
    }
    
    namespace interface {
        
        template <typename M, typename key, typename val = decltype(std::declval<const M>()[std::declval<const key>()])>
        struct indexed {
            using value = val;
        }; 
        
    }

    template <typename L, typename X>
    inline L append(const L& l, const X& x) {
        return l.append(x);
    }

    template <typename X>
    inline X right(const X& x) {
        return meta::right<X, meta::has_right_method<X>::value>{}(x);
    }

    template <typename X>
    inline X left(const X& x) {
        return meta::left<X, meta::has_left_method<X>::value>{}(x);
    }

    template <typename X, typename E>
    inline X insert(const X& x, const E& e) {
        return meta::insert<X, E, meta::has_insert_method<X, E>::value>{}(x, e);
    }

}

#endif
