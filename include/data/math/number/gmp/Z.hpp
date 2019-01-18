#ifndef DATA_MATH_NUMBER_GMP_Z_HPP
#define DATA_MATH_NUMBER_GMP_Z_HPP

#include <data/math/number/gmp/N.hpp>

namespace data {
    
    namespace number {
        
        namespace gmp {
            
            struct Z final : public mpz {
                Z() : mpz() {}
                
                Z(int n) {
                    mpz_init_set(&MPZ, n);
                }
                
                Z(const Z& z) : mpz(&z.MPZ) {}
                
                Z(const N& n) : mpz(&n.MPZ) {}
                
                Z(Z&& z) {
                    MPZ = z.MPZ;
                    z.MPZ = MPZInvalid;
                }
                
                Z& operator=(N& n) {
                    mpz_set(&MPZ, &n.MPZ);
                    return *this;
                }
                
                Z& operator=(Z& z) {
                    mpz_set(&MPZ, &z.MPZ);
                    return *this;
                }
                
                bool operator==(int n) const;
                
                bool operator==(Z& n) const;
                
                bool operator<(Z& n) const;
                
                bool operator>(Z& n) const;
                
                bool operator<=(Z& n) const;
                
                bool operator>=(Z& n) const;
                
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
              
            constexpr static math::number::natural<Z> is_integer{};
            
        }
        
    }

}

#endif
