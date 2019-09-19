#include "infodef.h"
#include "randombytes.h"

int main()
{
    int res;
    int_least64_t a, b ,p;
    res = randombytes(&a, sizeof(a));
    a = fabs(a % (int_least64_t)1e9);
    res = randombytes(&b, sizeof(b));
    b = fabs(b % (int_least64_t)1e9);
    res = randombytes(&p, sizeof(p));
    p = fabs(p % (int_least64_t)1e9);
    printf("base = %"PRId64", exponent = %"PRId64", module = %"PRId64", result = %"PRId64"\n", a, b, p, modpow(a, b, p));
}
