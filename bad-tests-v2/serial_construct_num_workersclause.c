#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:serial construct num_workersclause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int num_workers = 4;
    int num_gangs = 1;
    int num_threads = num_workers * num_gangs;

    #pragma acc parallel num_gangs(num_gangs) num_workers(num_workers)
    {
        int worker_id = acc_worker_id();
        int gang_id = acc_gang_id();
        if (worker_id >= num_workers || gang_id >= num_gangs) {
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