#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc memcpy from device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a, *b, *c, i;
    int n = 1024;

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; ++i){
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])

    #pragma acc kernels present(a[0:n], b[0:n])
    for (i = 0; i < n; ++i){
        b[i] = a[i];
    }

    #pragma acc update host(b[0:n])

    #pragma acc exit data delete(a[0:n])
    #pragma acc exit data copyout(b[0:n])

    for (i = 0; i < n; ++i){
        if (a[i] != b[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

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