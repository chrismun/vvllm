#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
  
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
  
    #pragma acc data create(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i){
            a[i] = rand() % 100;
            b[i] = rand() % 100;
        }
  
        #pragma acc parallel loop
        for (int i = 0; i < n; ++i){
            c[i] = a[i] + b[i];
        }
    }
  
    for (int i = 0; i < n; ++i){
        if (c[i] != a[i] + b[i]){
            err = 1;
            break;
        }
    }
  
    free(a);
    free(b);
    free(c);
  
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