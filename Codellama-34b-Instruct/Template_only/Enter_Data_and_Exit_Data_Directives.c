#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region
    #pragma acc data
    {
        // Declare a variable to store the data
        int data[10];

        // Initialize the data
        for (int i = 0; i < 10; i++) {
            data[i] = i;
        }

        // Enter the data region
        #pragma acc enter data copyin(data)

        // Verify that the data has been copied to the device
        for (int i = 0; i < 10; i++) {
            if (data[i] != i) {
                err = 1;
                break;
            }
        }

        // Exit the data region
        #pragma acc exit data delete(data)

        // Verify that the data has been deleted from the device
        for (int i = 0; i < 10; i++) {
            if (data[i] != 0) {
                err = 1;
                break;
            }
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