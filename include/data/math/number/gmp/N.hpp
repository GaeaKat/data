#ifndef DATA_MATH_NUMBER_GMP_N_HPP
#define DATA_MATH_NUMBER_GMP_N_HPP

#include <gmp.h>
#include <data/types.hpp>
#include <data/math/sign.hpp>
#include <data/math/number/natural.hpp>
#include <data/math/number/gmp/mpz.hpp>

namespace data {
    
    namespace number {
        
        namespace gmp {
            
            struct Z;
            
            struct N final : public mpz {
                N() : mpz() {}
                
                N(uint n) {
                    mpz_init_set_ui(&MPZ, n);
                }
                
                N(const N& n) : mpz(&n.MPZ) {}
                
                N(N&& n) {
                    MPZ = n.MPZ;
                    n.MPZ = MPZInvalid;
                }
                
                N& operator=(N& n) {
                    mpz_set(&MPZ, &n.MPZ);
                    return *this;
                }
                
                bool operator==(uint n) const;
                
                bool operator==(N& n) const;
                
                bool operator<(N& n) const;
                
                bool operator>(N& n) const;
                
                bool operator<=(N& n) const;
                
                bool operator>=(N& n) const;
                
                N successor() const;
                
                N operator+(N&) const;
                
                N& operator+=(N&);
                
                N operator+(uint) const;
                
                N& operator+=(uint);
                
                N operator*(N&) const;
                
                N& operator*=(N&);
                
                N operator^(uint n) const;
                
                N& operator^=(uint n);
                
                math::number::division<N> divide(N& n) const;
                
                bool operator|(N& n) const {
                    return this->divide(n).Quotient == 0;
                }
                
                N operator/(N& n) const {
                    return this->divide(n).Quotient;
                }
                
                N operator%(N& n) const {
                    return this->divide(n).Remainder;
                }
                
                N& operator/=(N& n) {
                    N q = this->operator/(n);
                    return this->operator=(q);
                }
                
                N& operator%=(N& n) {
                    N r = this->operator%(n);
                    return this->operator=(r);
                }
                
                friend struct Z;
            };
              
            constexpr static math::number::natural<N> is_natural{};
            
        }
        
    }

}

#endif
