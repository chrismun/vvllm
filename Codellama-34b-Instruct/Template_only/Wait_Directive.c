#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array;
    cudaMalloc((void**)&dev_array, sizeof(int) * 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand();
    }

    // Create a host array
    int *host_array = (int*)malloc(sizeof(int) * 10);

    // Copy the device array to the host array
    cudaMemcpy(host_array, dev_array, sizeof(int) * 10, cudaMemcpyDeviceToHost);

    // Wait for the device array to be ready
    cudaDeviceSynchronize();

    // Check if the host array is equal to the device array
    for (int i = 0; i < 10; i++) {
        if (host_array[i] != dev_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array
    cudaFree(dev_array);

    // Free the host array
    free(host_array);

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