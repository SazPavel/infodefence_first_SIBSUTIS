
#include "infodef.h"

void gcd_v(int_least64_t *a, int_least64_t *b)
{
    lldiv_t q;
    int i;
    struct vector t, *v, *u;
    u = (struct vector*)a;
    v = (struct vector*)b;
    while(v->e[0] != 0)
    {
        q = lldiv(u->e[0], v->e[0]);
        for(i = 0; i < 3; i++)
            t.e[i] = u->e[i] - q.quot * v->e[i];
        *u = *v;
        *v = t;
    }
}
