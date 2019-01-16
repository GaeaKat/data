#include <data/math/number/gmp/N.hpp>
#include <gmpxx.h>

namespace data {
    
    namespace number {
        
        namespace gmp {
            bool N::operator==(gmp_uint n) const {
                return __gmp_binary_equal::eval(&MPZ, n);
            }
                
            bool N::operator==(N& n) const {
                return __gmp_binary_equal::eval(&MPZ, &n.MPZ);
            }
                
            bool N::operator<(N& n) const {
                return __gmp_binary_less::eval(&MPZ, &n.MPZ);
            }
                
            bool N::operator>(N& n) const {
                return __gmp_binary_greater::eval(&MPZ, &n.MPZ);
            }
                
            bool N::operator<=(N& n) const {
                return !__gmp_binary_greater::eval(&MPZ, &n.MPZ);
            }
                
            bool N::operator>=(N& n) const {
                return !__gmp_binary_less::eval(&MPZ, &n.MPZ);
            }
                
            N N::operator+(gmp_uint n) const {
                N sum{};
                __gmp_binary_plus::eval(&sum.MPZ, &MPZ, n);
                return sum;
            }
                
            N& N::operator+=(gmp_uint n) {
                __gmp_binary_plus::eval(&MPZ, &MPZ, n);
                return *this;
            }
                
            N N::successor() const {
                return this->operator+(1);
            }
                
            N N::operator+(N& n) const {
                N sum{};
                __gmp_binary_plus::eval(&sum.MPZ, &MPZ, &n.MPZ);
                return sum;
            }
                
            N& N::operator+=(N& n) {
                __gmp_binary_plus::eval(&MPZ, &MPZ, &n.MPZ);
                return *this;
            }
                
            N N::operator*(N& n) const {
                N prod{};
                __gmp_binary_multiplies::eval(&prod.MPZ, &MPZ, &n.MPZ);
                return prod;
            }
                
            N& N::operator*=(N& n) {
                __gmp_binary_multiplies::eval(&MPZ, &MPZ, &n.MPZ);
                return *this;
            }
                
            N N::operator^(gmp_uint n) const {
                N pow{};
                mpz_pow_ui(&pow.MPZ, &MPZ, n);
                return pow;
            }
                
            N& N::operator^=(gmp_uint n) {
                mpz_pow_ui(&MPZ, &MPZ, n);
                return *this;
            }

            math::number::division<N> N::divide(N& n) const {
                math::number::division<N> qr{};
                mpz_cdiv_qr(&qr.Quotient.MPZ, &qr.Remainder.MPZ, &MPZ, &n.MPZ);
                return qr;
            }
            
        }
        
    }
