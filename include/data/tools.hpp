// Copyright (c) 2019-2020 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_TOOLS
#define DATA_TOOLS

// basic types
#include <data/types.hpp>

// This library uses a valid() method and a Valid member in a stereotyped way. 
#include <data/valid.hpp>

#include <data/maybe.hpp>

// Interfaces related to data structures. 
#include <data/functional/set.hpp>
#include <data/functional/list.hpp>
#include <data/functional/map.hpp>
#include <data/functional/tree.hpp>

#include <data/reverse.hpp>
#include <data/take.hpp>
#include <data/sort.hpp>

// A implementations of data structures. 
#include <data/tools/linked_stack.hpp>
#include <data/tools/rb_map.hpp>
#include <data/tools/functional_queue.hpp>
#include <data/tools/linked_tree.hpp>
#include <data/tools/map_set.hpp>
#include <data/tools/priority_queue.hpp>
#include <data/tools/ordered_list.hpp>
#include <data/tools/cycle.hpp>

#include <data/cross.hpp>
#include <data/fold.hpp>

#include <data/string.hpp>

namespace data {
    
    template <typename X> using stack = linked_stack<X>;
    
    // functional queue built using the list. 
    template <typename X> using list = functional_queue<stack<X>>;
    
    template <typename X> using cycle = tool::cycle<list<X>, X>;
    
    // tree. 
    template <typename X> using tree = linked_tree<X>;
    
    // a functional map implemented as a red-black tree
    // wrapper of Milewski's implementation of Okasaki.
    template <typename K, typename V> using map = tool::rb_map<K, V>;
    
    // set implemented as a map. 
    template <typename X> using set = tool::map_set<map<X, tool::unit>>;
    
    // priority queue. wrapper of Milewski's implementation of Okasaki.
    template <typename X> using priority_queue = tool::priority_queue<tree<X>>;
    
    // ordered_list. wrapper of Milewski's implementation of Okasaki.
    template <typename X> using ordered_list = tool::ordered_stack<stack<X>>;
    
    template <typename f, sequence A, sequence B> 
    auto map_thread (f fun, A a, B b) {
        if (data::size (a) != data::size (b)) throw exception {"lists must be the same size"};
        
        list<decltype (fun (data::first (std::declval<A> ()), data::first (std::declval<B> ())))> l;
        
        while (data::size (a) != 0) {
            l = data::append (l, fun (data::first (a), data::first (b)));
            a = a.rest ();
            b = b.rest ();
        }
        
        return l;
    }

    // split a string by a delimiter.
    list<string> split (string_view str, const string &delimiter);

    template <typename map, typename key, typename value>
    map inline replace_part (map X, const key &k, const value &v) {
        return X.contains (k) ? X.remove (k).insert (k, v) : X;
    }

    template <typename elem>
    stack<elem> reverse (const ordered_list<elem> x) {
        stack<elem> n;
        for (const elem &e : x) n <<= e;
        return n;
    }

    template <typename elem>
    ordered_list<elem> select (const ordered_list<elem> x, function<bool (const elem &)> satisfies) {
        stack<const elem &> n;
        for (const elem &e : x) if (satisfies (e)) n <<= e;
        ordered_list<elem> r;
        for (const elem &e : n) r = r.insert (e);
        return r;
    }

}

#endif
