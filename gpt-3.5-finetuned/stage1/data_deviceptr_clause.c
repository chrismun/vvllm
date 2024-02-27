#include "acc_testsuite.h"
#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_device = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(n - 1);
        b[x] = rand() / (real_t)(n - 1);
        c[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) create(a_device[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            a_device[x] = a[x];
        }

        #pragma acc parallel loop deviceptr(a_device)
        for (int x = 0; x < n; ++x){
            c[x] = a_device[x] + b[x];
        }

    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}