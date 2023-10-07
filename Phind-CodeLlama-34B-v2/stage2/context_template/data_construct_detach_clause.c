#include "acc_testsuite.h"
#ifndef T1
//T1:data construct detach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(time(NULL));
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])

    #pragma acc parallel present(a[0:n], b[0:n])
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            b[x] = a[x] * 2.0;
        }
    }

    #pragma acc exit data delete(a[0:n]) detach(b[0:n]) finalize

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - (a[x] * 2.0)) > PRECISION) {
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