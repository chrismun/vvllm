#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    int a[NUM_ITERATIONS];
    int b[NUM_ITERATIONS];
    int c[NUM_ITERATIONS];

    srand(SEED);

    for (int i = 0; i < NUM_ITERATIONS; i++){
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

    #pragma acc data copyin(a, b) copyout(c)
    #pragma acc parallel loop num_workers(NUM_WORKERS) worker
    for (int i = 0; i < NUM_ITERATIONS; i++){
        c[i] = a[i] + b[i];
    }

    for (int i = 0; i < NUM_ITERATIONS; i++){
        if (c[i] != (a[i] + b[i])){
            err = 1;
            break;
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;

#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}