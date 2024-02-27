#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * b = new real_t[10 * n];
    real_t * c = new real_t[10 * n];
    real_t * d = new real_t[10 * n];
    real_t max = 0.0;
    real_t temp = 0.0;

    for (int x = 0; x < 10 * n; ++x){
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
        d[x] = 0.0;
    }

    #pragma acc data copyin(b[0:10*n], c[0:10*n]) copyout(d[0:10*n])
    {
        #pragma acc kernels vector_length(32)
        {
            #pragma acc loop vector
            for (int x = 0; x < 10; ++x){
                for (int y = 0; y < n; ++y){
                    d[x * n + y] = b[x * n + y] + c[x * n + y];
                }
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(d[x] - (b[x] + c[x])) > PRECISION){
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