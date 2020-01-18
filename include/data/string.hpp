// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_STRING
#define DATA_STRING

#include <data/slice.hpp>

namespace data::iterable {
    // A string that might manage its own memory or might not. 
    template <typename X>
    class string : public slice<X> {
        X* String;
    public:
        ~string() {
            delete[] String;
        }
        
        string(const string& x) : string{std::basic_string_view<X>(x)} {}
        
        string& operator=(const string& x) {
            delete[] String;
            slice<X>::operator=(slice<X>{new X[x.size()], x.size()});
            String = slice<X>::data();
            std::copy(x.begin(), x.end(), slice<X>::begin());
            return *this;
        }
        
        string(string&& x) : slice<X>{x.data(), x.size()}, String{x.String} {
            x.String = nullptr;
        }
        
        string(size_t size, X fill) : slice<X>{new X[size], size}, String{slice<X>::data()} {
            for (auto i = slice<X>::begin(); i <= slice<X>::end(); i++) *i = fill;
        }
        
        string(size_t size) : string(size, 0) {}
        string() : slice<X>{}, String{nullptr} {}
        string(slice<X> x) : slice<X>{x}, String{nullptr} {}
        string(std::basic_string_view<X> x) : slice<X>{new X[x.size()], x.size()}, String{slice<X>::data()} {
            std::copy(x.data(), x.end(), slice<X>::begin());
        }
        
        bool operator==(const string& s) const {
            return slice<X>::operator==(static_cast<slice<X>>(s));
        }
        
        bool operator!=(const string& s) const {
            return !operator==(s);
        }
    };
}

namespace data {
    using bytes = iterable::string<byte>;
}

#endif
