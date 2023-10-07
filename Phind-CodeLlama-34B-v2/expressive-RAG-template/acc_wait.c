#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    int async = 1;
    int dev_num = acc_get_device_num(acc_device_nvidia);

    #pragma acc enter data copyin(async)
    #pragma acc parallel async(async)
    {
        // Do some work
    }
    #pragma acc exit data delete(async)

    acc_wait(async);

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