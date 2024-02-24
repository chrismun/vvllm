#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000;
    int a[N], b[N], c[N];

    for(int i = 0; i < N; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    #pragma acc kernels copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc loop worker
        for(int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }
    }

    for(int i = 0; i < N; i++){
        if(c[i] != a[i] + b[i]){
            err = 1;
            break;
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