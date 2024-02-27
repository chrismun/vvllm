#include "acc_testsuite.h"
#ifndef T1
//T1:update directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[n];
    real_t * b = new real_t[n];
    real_t * c = new real_t[n];
    real_t * h = new real_t[n];
    real_t * k = new real_t[n];
    real_t * j = new real_t[n];
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        h[x] = rand() / (real_t)(RAND_MAX / 10);
        k[x] = rand() / (real_t)(RAND_MAX / 10);
        j[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], h[0:n], k[0:n]) copyout(c[0:n]) 
    {
      #pragma acc parallel 
      {
        #pragma acc loop 
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
        #pragma acc loop 
        for (int x = 0; x < n; ++x){
            j[x] = h[x] + k[x];
        }
        #pragma acc update host(c[0:n], j[0:n]) 
      }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
        if (fabs(j[x] - (h[x] + k[x])) > PRECISION){
            err += 1;
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