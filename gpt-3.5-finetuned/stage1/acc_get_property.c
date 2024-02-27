#include "acc_testsuite.h"
#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;

    if (acc_get_property(acc_get_device_num(acc_get_device_type()),acc_get_device_type(),acc_property_free_memory) == 0){
        err += 1;
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