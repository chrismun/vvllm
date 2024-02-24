#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100

int main() {
    int *host_array = (int*)malloc(N * sizeof(int));
    int *device_array = (int*)malloc(N * sizeof(int));

    // Initialize host array
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Copy host array to device
    #pragma acc data copyin(host_array[:N]) copyout(device_array[:N])
    {
        // Copy host array to device
        #pragma acc update device(host_array[:N])

        // Perform some computation on the device
        #pragma acc parallel loop
        for(int i = 0; i < N; i++) {
            device_array[i] = host_array[i] * 2;
        }

        // Copy device array back to host
        #pragma acc update self(device_array[:N])
    }

    // Verify the results
    for(int i = 0; i < N; i++) {
        if(device_array[i] != host_array[i] * 2) {
            printf("Error: device_array[%d] = %d, expected %d\n", i, device_array[i], host_array[i] * 2);
            return 1;
        }
    }

    printf("Success!\n");
    return 0;
}