#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct default clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() % n;
        b[x] = 0;
    }

    #pragma acc parallel default(present) copy(a[0:n]) copyout(b[0:n])
    {
        int idx = acc_threadid();
        b[idx] = a[idx];
    }

    for (int x = 0; x < n; ++x) {
        if (b[x] != a[x]) {
            err = 1;
            break;
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