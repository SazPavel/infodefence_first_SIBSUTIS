
#include "infodef.h"

int_least64_t steps = 0;


int comp_baby_step(const void *ptr1, const void *ptr2)
{
    steps += 1;
    struct BabyStep *a = (struct BabyStep*)ptr1;
    struct BabyStep *b = (struct BabyStep*)ptr2;
    if (a->value < b->value) return -1;
    else if (a->value > b->value) return  1;
    else return 0;
}

int_least64_t shencs(int_least64_t base, int_least64_t module, int_least64_t result)
{
    int_least64_t x = -1, k, m = ceil(sqrt(module));
    int i, j = 0;
    k = m;
    struct BabyStep *arr1, *arr2;
    arr1 = malloc(m * sizeof(struct BabyStep));
    arr2 = malloc(k * sizeof(struct BabyStep));
    for(i = 0; i < m; i++)
    {
        steps += 2;
        arr1[i].value = (result * modpow(base, i, module)) % module;
        arr2[i].value = modpow(base, ((i+1) * m), module);
        arr1[i].index = arr2[i].index = i;
    }
    i = 0;
    qsort(arr1, m, sizeof(struct BabyStep), comp_baby_step);
    qsort(arr2, k, sizeof(struct BabyStep), comp_baby_step);
    while(i < m && j < k)
    {
        steps += 1;
        if(arr1[i].value < arr2[j].value)
            i++;
        else if(arr1[i].value > arr2[j].value)
            j++;
        else break;
    }
    if(i < m && j < k)
        x = (arr2[j].index + 1) * m - (arr1[i].index);
    free(arr1);
    free(arr2);
    return x;
}

