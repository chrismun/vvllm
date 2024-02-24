#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 100

#ifndef T1
//T1:serial construct,V:2.7-3.3
int test1(){
    int err = 0;
    int a[N], b[N], c[N];
    int i;

    for(i = 0; i < N; i++){
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc serial
        for(i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }
    }

    for(i = 0; i < N; i++){
        if(c[i] != 2*i){
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}