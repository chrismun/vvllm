#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy from device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n])
    #pragma acc enter data create(b[0:n])

    #pragma acc parallel present(a[0:n], b[0:n])
    {
        int i = acc_thread_id();
        b[i] = a[i];
    }

    #pragma acc exit data copyout(b[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err = 1;
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