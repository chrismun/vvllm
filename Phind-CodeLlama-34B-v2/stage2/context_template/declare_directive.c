#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b, *c;
    int n = 1000;

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x) {
        a[x] = x;
        b[x] = 0;
        c[x] = 0;
    }

    #pragma acc declare create(a[0:n])
    #pragma acc parallel present(a, b, c)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x) {
            b[x] = a[x] * 2;
            c[x] = a[x] * 3;
        }
    }

    for (int x = 0; x < n; ++x) {
        if (b[x] != a[x] * 2 || c[x] != a[x] * 3) {
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