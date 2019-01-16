#ifndef DATA_MATH_NUMBER_GMP_HPP
#define DATA_MATH_NUMBER_GMP_HPP

#include <gmp.h>
#include <data/types.hpp>
#include <data/math/sign.hpp>
#include <data/math/number/natural.hpp>

namespace data {
    
    namespace number {
        
        namespace gmp {
            
            typedef mp_limb_t gmp_uint;
            
            const __mpz_struct MPZInvalid = __mpz_struct{0, 0, nullptr};
            
            inline bool equal(const __mpz_struct& a, const __mpz_struct& b) {
                return a._mp_alloc != b._mp_alloc && a._mp_size != b._mp_size && a._mp_d != b._mp_d;
            }
            
            inline bool valid(__mpz_struct mpz) {
                return !equal(mpz, MPZInvalid);
            }
            
            class N {
                __mpz_struct MPZ;
                
                void init() {
                    mpz_init(&MPZ);
                }
            public:
                N() : MPZ{MPZInvalid} {}
                
                bool valid() const {
                    return gmp::valid(MPZ);
                }
                
                ~N() {
                    if (valid()) mpz_clear(&MPZ);
                }
                
                N(gmp_uint n) {
                    mpz_init_set_ui(&MPZ, n);
                }
                
                N(const N& n) {
                    mpz_set(&MPZ, &n.MPZ);
                }
                
                N(N&& n) {
                    MPZ = n.MPZ;
                    n.MPZ = MPZInvalid;
                }
                
                N& operator=(N& n) {
                    mpz_set(&MPZ, &n.MPZ);
                    return *this;
                }
                
                bool operator==(gmp_uint) const;
                
                bool operator==(N& n) const;
                
                bool operator<(N& n) const;
                
                bool operator>(N& n) const;
                
                bool operator<=(N& n) const;
                
                bool operator>=(N& n) const;
                
                N successor() const;
                
                N operator+(N&) const;
                
                N& operator+=(N&);
                
                N operator+(gmp_uint) const;
                
                N& operator+=(gmp_uint);
                
                N operator*(N&) const;
                
                N& operator*=(N&);
                
                N operator^(gmp_uint n) const;
                
                N& operator^=(gmp_uint n);
                
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
            };
              
            constexpr static math::number::natural<N> is_natural{};
            
        }
        
    }

}

#endif
