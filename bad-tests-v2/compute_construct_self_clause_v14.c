#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() == acc_device_host) {
        // The self clause is not supported on the host device, so we expect an error
        err = 1;
    } else {
        // The self clause is supported on the device, so we expect the region to execute on the device
        int device_type = acc_get_device_type();
        if (device_type != acc_device_host) {
            err = 1;
        }
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