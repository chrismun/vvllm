#include "acc_testsuite.h"
#ifndef T1
int test1(){
    int err = 0;
    int devices = acc_get_num_devices(acc_device_none);

    if (devices == 0){
        err += 1;
    }

    return err;
}

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