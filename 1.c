
#include "infodef.h"

int_least64_t high_bit_bs(int_least64_t n)
{
    int_least64_t size = sizeof(n) * 4;
    int_least64_t result = 0;
    while(n != 1)
    {
        int l = n >> size;
        if(l)
        {
            n = l;
            result += size;
        }else{
            n ^= l << size;
        }
        size >>= 1;
    }
    return result+ 1;
}


uint_least64_t modpow(int_least64_t base, int_least64_t exponent, int_least64_t module)
{
    if(!module)
        return -1;
    if(!exponent)
        return 1 % module; 
    int i = 0;
    int_least64_t size = 0, bit_mask = 1;
    uint_least64_t result = 1;
    size = high_bit_bs(exponent);
    uint_least64_t tmp;
    tmp = base % module;
    if((exponent & bit_mask) != 0)
    {
        result *= tmp; 
    }
    bit_mask <<= 1;
    for(i = 1; i < size; i++, bit_mask <<= 1)
    {
        tmp = (tmp * tmp) % module;
        if((exponent & bit_mask) != 0)
        {
            result *= tmp; 
            result %= module;
        }
    }
    return result;
}
