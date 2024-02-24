#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    int a = 5;
    int b[1] = {0};

    #pragma acc data copyin(a) copyout(b)
    {
        b[0] = a * 2;
    }

    if (b[0] != 10) {
        err = 1;
    }

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