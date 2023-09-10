#include "acc_testsuite.h"
#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = new real_t[n];

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
    }

    #pragma acc kernels
    #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = 1.0;
        }

    for (int x = 0; x < n; ++x){
        if(a[x] != 1.0){
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