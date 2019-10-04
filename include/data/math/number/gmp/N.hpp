// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_MATH_NUMBER_GMP_N
#define DATA_MATH_NUMBER_GMP_N

#include <data/math/number/natural.hpp>
#include <data/math/number/gmp/Z.hpp>
#include <limits>

namespace data {
    
    namespace math {
    
        namespace number {
            
            namespace gmp {
                
                struct Q;
                
                struct N {
                    Z Value;
                    
                    N() : Value{} {}
                    
                    N(gmp_uint n) : Value{n} {}
                    explicit N(string& s) : Value{s} {}
                    
                    N& operator=(const N& n) {
                        Value = n.Value;
                        return *this;
                    }
                    
                    bool valid() {
                        return Value.valid() && Value >= 0;
                    }
                    
                    bool operator==(uint64 n) const {
                        return Value == n;
                    }
                    
                    bool operator==(const N& n) const {
                        return Value == n.Value;
                    }
                    
                    bool operator==(const Z& z) const {
                        if (z < 0) return false;
                        return Value == z;
                    }
                    
                    bool operator<(uint64 n) const {
                        return Value < n;
                    }
                    
                    bool operator<(const N& n) const {
                        return Value < n.Value;
                    }
                    
                    bool operator<(const Z& z) const {
                        if (z < 0) return false;
                        return Value < z;
                    }
                    
                    bool operator>(uint64 n) const {
                        return Value > n;
                    }
                    
                    bool operator>(const N& n) const {
                        return Value > n.Value;
                    }
                    
                    bool operator>(const Z& z) const {
                        if (z < 0) return true;
                        return Value > z;
                    }
                    
                    bool operator<=(uint64 n) const {
                        return Value <= n;
                    }
                    
                    bool operator<=(const N& n) const {
                        return Value <= n.Value;
                    }
                    
                    bool operator<=(const Z& z) const {
                        if (z < 0) return false;
                        return Value <= z;
                    }
                    
                    bool operator>=(uint64 n) const {
                        return Value >= n;
                    }
                    
                    bool operator>=(const N& n) const {
                        return Value >= n.Value;
                    }
                    
                    bool operator>=(const Z& z) const {
                        if (z < 0) return true;
                        return Value == z;
                    }
        
                    N& operator++() {
                        ++Value;
                        return *this;
                    }
                    
                    N& operator--() {
                        if (Value != 0) --Value; 
                        return *this;
                    }
                    
                    N operator++(int) {
                        Z z = *this;
                        ++(*this);
                        return N{z};
                    }
                    
                    N operator--(int) {
                        Z z = *this;
                        ++(*this);
                        return N{z};
                    }
                    
                    N operator+(uint64 n) const {
                        return N{Value + n};
                    }
                    
                    N operator+(const N& n) const {
                        return N{Value + n.Value};
                    }
                    
                    N operator-(uint64 n) const {
                        if (Value < n) return 0;
                        return N{Value - n};
                    }
                    
                    N operator-(const N& n) const {
                        if (Value < n) return 0;
                        return N{Value - n.Value};
                    }
                    
                    N& operator+=(uint64 n) {
                        Value += n;
                        return *this;
                    }
                    
                    N& operator+=(const N& n) {
                        Value += n;
                        return *this;
                    }
                    
                    N operator*(uint64 n) const {
                        return N{Value * n};
                    }
                    
                    N operator*(const N& n) const {
                        return N{Value * n.Value};
                    }
                    
                    N& operator*=(uint64 n) {
                        Value *= n;
                        return *this;
                    }
                    
                    N& operator*=(const N& n) {
                        Value *= n.Value;
                        return *this;
                    }
                    
                    N operator^(uint32 n) const {
                        return N{Value ^ n};
                    }
                    
                    N& operator^=(uint32 n) {
                        Value ^= n;
                        return *this;
                    };
                    
                    math::number::division<N> divide(const N& n) const {
                        auto div = Value.divide(n.Value);
                        return math::number::division<N>{N{div.Quotient}, N{div.Remainder}};
                    }
                    
                    bool operator|(const N& n) const {
                        return divide(n).Remainder == 0;
                    }
                    
                    N operator/(const N& n) const {
                        return divide(n).Quotient;
                    }
                    
                    N operator%(const N& n) const {
                        return divide(n).Remainder;
                    }
                    
                    N& operator/=(const N& n) {
                        N q = operator/(n);
                        return operator=(q);
                    }
                    
                    N& operator%=(const N& n) {
                        N r = operator%(n);
                        return operator=(r);
                    }
                    
                    N operator<<(int64) const {
                        throw method::unimplemented{};
                    }
                    
                    N operator>>(int64) const {
                        throw method::unimplemented{};
                    }
                    
                    N& operator<<=(int64) {
                        throw method::unimplemented{};
                    }
                    
                    N& operator>>=(int64) {
                        throw method::unimplemented{};
                    }
                    
                    static N as(const Z& z) {
                        if (z < 0) return N{0};
                        return N{z};
                    }
                
                    constexpr static math::number::natural<N> is_natural{};
                private:
                    explicit N(const Z& z) : Value{z} {}
                };
            
                inline bool Z::operator==(const N& n) const {
                    return operator==(n.Value);
                }
                
                inline bool Z::operator!=(const N& n) const {
                    return operator!=(n.Value);
                }
                
                inline bool Z::operator<(const N& n) const {
                    return operator<(n.Value);
                }
                
                inline bool Z::operator>(const N& n) const {
                    return operator>(n.Value);
                }
                
                inline bool Z::operator<=(const N& n) const {
                    return operator<=(n.Value);
                }
                
                inline bool Z::operator>=(const N& n) const {
                    return operator>=(n.Value);
                }
                
                inline Z Z::operator+(const N& n) const {
                    return operator+(n.Value);
                }
                
                inline Z& Z::operator+=(const N& n) {
                    return operator+=(n.Value);
                }
                
                inline Z Z::operator*(const N& n) const {
                    return operator*(n.Value);
                }
                
                inline Z& Z::operator*=(const N& n) {
                    return operator*=(n.Value);
                }
        
                inline math::number::division<Z> Z::divide(const N& n) const {
                    return divide(n.Value);
                }

                inline N Z::abs() const {
                    N n;
                    __gmp_abs_function::eval(&n.Value.MPZ, &MPZ);
                    return n;
                }

                inline N square(Z &z) {
                    return N::as(z * z);
                }
            
            }
            
        }
    
        inline number::gmp::N abs(number::gmp::N n) {
            return n;
        }
        
        inline number::gmp::N square(number::gmp::N n) {
            return n * n;
        }
        
        inline number::gmp::N norm(number::gmp::N n) {
            return n;
        }
    }

}

#endif
