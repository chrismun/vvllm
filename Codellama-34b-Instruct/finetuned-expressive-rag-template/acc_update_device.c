#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])

    #pragma acc kernels present(a[0:n], b[0:n])
    {
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }

    #pragma acc update device(a[0:n])
    #pragma acc update self(b[0:n])

    for (int x = 0; x < n; ++x){
        if (a[x] != b[x]){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n])
    #pragma acc exit data delete(b[0:n])

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