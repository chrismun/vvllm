#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device pointer
    int *device_ptr = acc_malloc(sizeof(int));

    // Set the device pointer to a random value
    *device_ptr = rand();

    // Create a host pointer
    int *host_ptr = (int *)acc_malloc(sizeof(int));

    // Set the host pointer to the same value as the device pointer
    *host_ptr = *device_ptr;

    // Verify that the host pointer and device pointer are equal
    if (*host_ptr != *device_ptr) {
        err = 1;
    }

    // Free the device pointer
    acc_free(device_ptr);

    // Free the host pointer
    acc_free(host_ptr);

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