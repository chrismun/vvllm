#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:variable predetermined data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    int sum = 0;

    #pragma acc parallel loop reduction(+:sum)
    for (int i = 0; i < 100; i++) {
        sum++;
    }

    if (sum != 100) {
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
    for (int x = 0; x < 10; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}