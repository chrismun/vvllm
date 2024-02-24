#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    // Initialize array a
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }

    // Copy array a to device
    #pragma acc data copyin(a[0:N]) copyout(b[0:N])
    {
        // Use no_create clause to ensure array b is not created on device
        #pragma acc no_create(b)
        {
            // Copy array a to array b
            #pragma acc kernels
            {
                #pragma acc loop
                for (int i = 0; i < N; i++) {
                    b[i] = a[i];
                }
            }
        }
    }

    // Verify that array b is not created on device
    if (acc_is_present(b, N * sizeof(int)) == 1) {
        printf("Array b is present on device\n");
    } else {
        printf("Array b is not present on device\n");
    }

    // Free memory
    free(a);
    free(b);

    return 0;
}