#ifndef DATA_MATH_NUMBER_GMP_Q_HPP
#define DATA_MATH_NUMBER_GMP_Q_HPP

#include <data/math/number/gmp/Z.hpp>
#include <data/math/number/gmp/mpq.hpp>

namespace data {
    
    namespace number {
        
        namespace gmp {
            
            struct Q final : public mpq {
                Q() : mpq() {}
                
                Q(int q) {
                    mpq_init_set(&MPQ, q);
                }
                
                Q(const N& n) : mpq(&n.MPZ) {}
                
                Q(const Z& z) : mpq(&z.MPZ) {}
                
                Q(const Q& q) : mpq(&q.MPQ) {}
                
                Q(Q&& q) {
                    MPQ = q.MPQ;
                    q.MPQ = MPQInvalid;
                }
                
                Q& operator=(N& n) {
                    throw 0;
                    return *this;
                }
                
                Q& operator=(Z& z) {
                    throw 0;
                    return *this;
                }
                
                Q& operator=(Q& q) {
                    mpz_set(&MPQ, &q.MPQ);
                    return *this;
                }
                
                bool operator==(int n) const;
                
                bool operator==(Z& n) const;
                
                bool operator==(Q& q) const;
                
                bool operator<(Z& n) const;
                
                bool operator>(Z& n) const;
                
                bool operator<=(Z& n) const;
                
                bool operator>=(Z& n) const;
                
                bool operator<(int n) const;
                
                bool operator>(int n) const;
                
                bool operator<=(int n) const;
                
                bool operator>=(int n) const;
                
                bool operator<(Q& n) const;
                
                bool operator>(Q& n) const;
                
                bool operator<=(Q& n) const;
                
                bool operator>=(Q& n) const;
                
                Z operator+(Z&) const;
                
                Z& operator+=(Z&);
                
                Z operator+(int) const;
                
                Z& operator+=(int);
                
                Z operator-(N&) const;
                
                Z& operator-=(N&);
                
                Z operator-(int) const;
                
                Z& operator-=(int);
                
                Z operator*(Z&) const;
                
                Z& operator*=(Z&);
                
                Z operator^(uint n) const;
                
                Z& operator^=(uint n);
                
                math::number::division<Z> divide(Z& n) const;
                
                bool operator|(Z& n) const {
                    return this->divide(n).Quotient == 0;
                }
                
                Z operator/(Z& n) const {
                    return this->divide(n).Quotient;
                }
                
                Z operator%(Z& n) const {
                    return this->divide(n).Remainder;
                }
                
                Z& operator/=(Z& n) {
                    Z q = this->operator/(n);
                    return this->operator=(q);
                }
                
                Z& operator%=(Z& n) {
                    Z r = this->operator%(n);
                    return this->operator=(r);
                }
            };
              
            constexpr static math::field<Q> is_field{};
            
        }
        
    }

}

#endif
