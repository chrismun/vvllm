#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:kernels construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = 0;
    }

    #pragma acc kernels copy(a[0:n]) copyout(b[0:n])
    {
        for (int x = 0; x < n; ++x){
            b[x] = a[x] * 2;
        }
    }

    for (int x = 0; x < n; ++x){
        if (b[x] != a[x] * 2){
            err = 1;
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