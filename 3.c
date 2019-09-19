
#include "infodef.h"


int_least64_t jacobi(int_least64_t a, int_least64_t b)
{
    int_least64_t am[3], bm[3], r = 1, tmp, t, c;
    am[0] = a; am[1] = 1; am[2] = 0;
    bm[0] = b; bm[1] = 0; bm[2] = 1;
    gcd_v(am, bm);
    if(am[0] != 1)
        return 0;
    if(a < 0)
    {
        a = -a;
        tmp = modpow(b, 1, 8);
        if(tmp == 3 || tmp == 5)
            r = -r;
    }
    while(1)
    {
        t = 0;
        while(a % 2 == 0)
        {
            t += 1;
            a /= 2;
        }
        if(t % 2 == 1)
        {
            tmp = modpow(b, 1, 8);
            if(tmp == 3 || tmp == 5)
                r = -r;
        }
        if(modpow(a, 1, 4) == modpow(b, 1, 4) == 3)
            r = -r; 
        c = a; a = modpow(b, 1, c); b = c;   
        if(a == 0)
           return r;
    }
}

int bpsw (int_least64_t n)
{
    int_least64_t mask, r;
    if ((int_least64_t)sqrt(n + 0.0) * (int_least64_t)sqrt(n + 0.0) == n)  
        return 0;
    int_least64_t dd = 5;
    for (;;)
    {
        int_least64_t a[3], b[3];
        a[0] = n; a[1] = 1; a[2] = 0;
        b[0] = abs(dd); b[1] = 0; b[2] = 1;
        gcd_v(a, b);
        int_least64_t g = a[0];
        if (1 < g && g < n)  return 0;
        if (jacobi (dd, n) == -1)  break;
        dd = dd < 0 ? -dd + 2 : -dd - 2;
    }
    int_least64_t p = 1,  q = (p * p - dd)/4;
    int_least64_t d = n + 1,  s = 0;
    while ((d & 1) == 0)
        ++s,  d >>= 1;
    int_least64_t u = 1, v = p, u2m = 1, v2m = p, qm = q, qm2 = q*2, qkd = q;
    for (mask = 2; mask <= d; mask <<= 1)
    {
        u2m = (u2m * v2m) % n;
        v2m = (v2m * v2m) % n;
        while (v2m < qm2)   v2m += n;
        v2m -= qm2;
        qm = (qm * qm) % n;
        qm2 = qm * 2;
        if (d & mask) {
            int_least64_t t1 = (u2m * v) % n,  t2 = (v2m * u) % n,
                t3 = (v2m * v) % n,  t4 = (((u2m * u) % n) * dd) % n;
            u = t1 + t2;
            if (u & 1)  u += n;
            u = (u >> 1) % n;
            v = t3 + t4;
            if (v & 1)  v += n;
            v = (v >> 1) % n;
            qkd = (qkd * qm) % n;
        }
    }
    if (u==0 || v==0)  return 1;
    int_least64_t qkd2 = qkd*2;
    for (r=1; r<s; ++r) {
        v = (v * v) % n - qkd2;
        if (v < 0)  v += n;
        if (v < 0)  v += n;
        if (v >= n)  v -= n;
        if (v >= n)  v -= n;
        if (v == 0)  return 1;
        if (r < s-1) {
            qkd = (qkd * 1ll * qkd) % n;
            qkd2 = qkd * 2;
        }
    }
    return 0;
}


int miller_rabin(int_least64_t n, int k)
{
    if (n == 2 || n == 3)
        return 1;
    if (n < 2 || n % 2 == 0)
        return 0;
    int_least64_t a, x, t = n - 1;
    int i, res, r, s = 0;
    while(t % 2 == 0)
    {
        t /= 2;
        s += 1;
    }
    for(i = 0; i < k; i++)
    {
        res = randombytes(&a, sizeof(a));
        a = fabs(a % (n - 6)) + 2;
        x = modpow(a, t, n);
        if(x == 1 || x == n - 1)
            continue;
        for(r = 1; r < s; r++)
        {
            x = modpow(x, 2, n);
            if(x == 1)
                return 0;
            if(x == n - 1)
                break;
        }
        if(x != n - 1)
            return 0;
    }
    return 1;
}

int prime_test(int_least64_t n)
{
    if(!miller_rabin(n, 10))
        return 0;
    return bpsw(n);
}


int_least64_t diff_hell_man(int seed)
{
    int_least64_t a, b, q, fp, tmpfp, p, g, A, B, K1, K2;
    int i, tmp = 0;
    int res;
    res = randombytes(&a, sizeof(a));
    a = fabs(a % seed) + 11 + seed;
    printf("min %"PRId64"\n", a);
    p = a;
    while(1)
    {
        if(modpow(p, 1, 12) == 11)
            break;
        p += 1;
    }
    for(;; p += 12)
    {
        q = (p - 1) / 2;
        if(p >= 11 && (modpow(p, 1, 12) == 11) && prime_test(p) && prime_test(q))
        {
            break;
        }
    }
    printf("p %"PRId64" q %"PRId64"\n", p, q);
    for(g = 2; g < p - 1; g++)
    {
        if(modpow(g, q, p) != 1) 
            break;
    }
    printf("g %"PRId64"\n", g);
    //private keys
    res = randombytes(&a, sizeof(a));
    a = fabs(a % p - 4) + 2;
    res = randombytes(&b, sizeof(b));
    b = fabs(b % p - 4) + 2;
    //public keys
    A = modpow(g, a, p);
    B = modpow(g, b, p);
    printf("public key A: %"PRId64", public key B: %"PRId64"\n", A, B);
    //secret key
    K1 = modpow(B, a, p);
    K2 = modpow(A, b, p);
    printf("secret key K1: %"PRId64", secret key K2: %"PRId64"\n", K1, K2);
    return K1;
}

