#include "FD.h"
#include "time.h"
#if 0
#define simple_alloc(x) malloc(x)
#define simple_free(x) free(x)
#endif
int main() {
    int num = 100;

        struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

   
    int * ptr = simple_alloc(sizeof(int)*num);
    for (int i = 0; i < num; i++){
        ptr[i] = i;
    }
    simple_free(ptr);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                        (end.tv_nsec - start.tv_nsec) / 1.0e6;

    printf("Time: %.3f ms\n", elapsed_ms);
    return 0;
}

