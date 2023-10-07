#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct private clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = 0;
    }

    #pragma acc parallel private(a)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            a[x] = a[x] * 2;
        }
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != (x * 2)){
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