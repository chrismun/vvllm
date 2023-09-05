#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copyout(err)
    {
        int a[N];
        int b[N];
        int c[N];

        #pragma acc parallel loop
        for(int i = 0; i < N; i++){
            a[i] = i;
            b[i] = i * 2;
        }

        #pragma acc parallel loop
        for(int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }

        int sum = 0;
        #pragma acc parallel loop reduction(+:sum)
        for(int i = 0; i < N; i++){
            sum += c[i];
        }

        if(sum != N * (2 * N - 1)){
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