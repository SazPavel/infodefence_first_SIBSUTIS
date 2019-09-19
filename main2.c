#include "infodef.h"
#include "randombytes.h"

int main()
{
    int res;
    int_least64_t am[3], bm[3];
    res = randombytes(&am[0], sizeof(am[0]));
    am[0] = fabs(am[0] % (int_least64_t)1e1);
    res = randombytes(&bm[0], sizeof(bm[0]));
    bm[0] = fabs(bm[0] % (int_least64_t)1e1);
    printf("a = %"PRId64", b = %"PRId64, am[0], bm[0]);
    am[1] = 1; am[2] = 0;
    bm[1] = 0; bm[2] = 1;
    gcd_v(am, bm); 
    printf(", HOD = %"PRId64", x = %"PRId64", y = %"PRId64"\n", am[0], am[1], am[2]);
}
