#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct num_gangs clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){
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
    int dev_test1 = 1;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + dev_test1;
        return_val = 0;
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}