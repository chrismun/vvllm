#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = 0;
    }

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x];
            }
        }

        #pragma acc update device(b[0:n])

        #pragma acc compute wait(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] *= 2;
            }
        }

        #pragma acc update self(b[0:n])

        for (int x = 0; x < n; ++x){
            if (b[x] != a[x] * 2){
                err = 1;
                break;
            }
        }
    }

    free(a);
    free(b);

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