#include "acc_testsuite.h"
#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    int async_arg = 1;
    int async_default = -1;

    acc_set_default_async(async_arg);
    #pragma acc parallel async
    {
        // Do some work here
    }

    acc_set_default_async(async_default);
    #pragma acc parallel async
    {
        // Do some work here
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