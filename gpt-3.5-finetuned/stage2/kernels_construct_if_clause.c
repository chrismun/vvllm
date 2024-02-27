#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t* a = (real_t *)malloc(n * sizeof(real_t));
    real_t* b = (real_t *)malloc(n * sizeof(real_t));
    real_t* c = (real_t *)malloc(n * sizeof(real_t));
    real_t* d = (real_t *)malloc(n * sizeof(real_t));
    real_t* a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t* b_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        d[x] = 0;
        a_host[x] = a[x];
        b_host[x] = b[x];
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n], d[0:n])
    {
        #pragma acc kernels if(0)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x];
            }
        }
        #pragma acc kernels if(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x]) > PRECISION){
            err += 1;
        }
        if (fabs(d[x] - b_host[x]) > PRECISION){
            err += 1;
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