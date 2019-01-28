#ifndef DATA_MATH_NUMBER_GMP_MPQ_HPP
#define DATA_MATH_NUMBER_GMP_MPQ_HPP

#include <gmp.h>
#include <data/types.hpp>
#include <data/math/sign.hpp>
#include <data/math/number/natural.hpp>

namespace data {
    
    namespace number {
        
        namespace gmp {
            
            const __mpq_struct MPQInvalid = __mpq_struct{MPQInvalid, MPQInvalid};
            
            inline bool equal(const __mpq_struct& a, const __mpq_struct& b) {
                return a._mp_num == b._mp_num && a._mp_den == b._mp_den;
            }
            
            inline bool valid(__mpq_struct& mpq) {
                return valid(mpq._mp_den) && valid(mpq._mp_num);
            }
            
            inline number::sign sign(const __mpq_strict& mpq) {
                return !valid(mpq) ? zero : sign(mpq._mp_num) * sign(mpq._mp_den);
            }
            
            struct mpq {
                __mpq_struct MPQ;
                
                void init() {
                    mpq_init(&MPQ);
                }
                
                mpq() : MPQ{MPQInvalid} {}
                
                bool valid() const {
                    return gmp::valid(MPQ);
                }
                
                virtual ~mpq() {
                    if (valid()) mpq_clear(&MPQ);
                }
                
                mpq(const mpq& q) {
                    mpq_set(&MPQ, &q.MPQ);
                }
                
                mpq(mpq&& q) {
                    MPQ = q.MPQ;
                    q.MPQ = MPQInvalid;
                }
                
                mpq(gmp_uint n) {
                    mpq_init_set_ui(&MPQ, n);
                }
                
                mpq(int n) {
                    mpq_init_set_i(&MPQ, n);
                }
                
                mpq(mpz z) {
                    throw 0;
                }
                
                mpq& operator=(const mpq& q) {
                    mpq_set(&MPZ, &q.MPZ);
                    return *this;
                }
                
                sign sign() {
                    return gmp::sign(MPQ);
                }
                
                bool operator==(gmp_uint n) const;
                
                bool operator==(int n) const;
                
                bool operator==(mpz& n) const;
                
                bool operator==(mpq& q) const;
                
                bool operator<(mpz& n) const;
                
                bool operator<(mpq& q) const;
                
                bool operator>(mpz& n) const;
                
                bool operator>(mpq& q) const;
                
                bool operator<=(mpz& n) const;
                
                bool operator<=(mpq& q) const;
                
                bool operator>=(mpz& n) const;
                
                bool operator>=(mpq& q) const;
            };
            
        }
        
    }

}

#endif
