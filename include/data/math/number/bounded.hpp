#ifndef DATA_MATH_NUMBER_BOUNDED
#define DATA_MATH_NUMBER_BOUNDED

#include <data/types.hpp>
#include <data/math/group.hpp>
#include <data/math/sign.hpp>

namespace data {
    
    namespace math {
    
        namespace number {
            
            template <uint32_t size, typename parent = std::array<byte, size * 4>>
            struct bounded : public parent {  
                
                bounded() : parent() {}
                bounded(uint64_t x) : bounded() {
                    parent::operator[](size - 1) = x;
                }
                
                bounded(std::array<byte, 4 * size> b);
                
                static bounded zero() {
                    return bounded{};
                }

                bool operator<(const bounded& d) const {
                    for (uint32_t i = 0; i < size; i++) {
                        if (get(i) < d.get(i)) return true;
                        if (get(i) > d.get(i)) return false;
                    }
                    
                    return false;
                }
 
                bool operator<=(const bounded& d) const {
                    for (uint32_t i = 0; i < size; i++) {
                        if (get(i) < d.get(i)) return true;
                        if (get(i) > d.get(i)) return false;
                    }
                    
                    return true;
                }
                    
                bool operator>(const bounded& d) const {
                    return d <= *this;
                }
                    
                bool operator>=(const bounded& d) const {
                    return d < *this;
                }
                
                bool operator==(const bounded& d) const {
                    return static_cast<const parent&>(*this) == static_cast<const parent&>(d);
                }
                
                bool operator!=(const bounded& d) const {
                    return static_cast<const parent&>(*this) != static_cast<const parent&>(d);
                }
                
            private:
                uint64_t get(uint32_t i) const {
                    return *(uint64_t*)(parent::data() + 4 * i);
                }
            };
            
        }
    
    }

}

#endif