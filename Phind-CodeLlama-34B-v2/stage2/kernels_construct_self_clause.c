#include "acc_testsuite.h"
#ifndef T1
/*T1:kernels construct self clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() % n;
        b[x] = rand() % n;
        c[x] = 0;
    }

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc kernels self(acc_on_device(acc_device_host))
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (c[x] != a[x] + b[x]) {
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