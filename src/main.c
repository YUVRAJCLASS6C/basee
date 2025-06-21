#include "FD.h"
#include "time.h"
int main() {
    const int N = 1000000;
    clock_t start, end;

    start = clock();
    for(int i = 0; i < N; i++) {
        void *p = malloc(100);
        free(p);
    }
    end = clock();
    printf("malloc/free: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    start = clock();
    for(int i = 0; i < N; i++) {
        void *p = simple_alloc(100);
        simple_free(p);
    }
    end = clock();
    printf("simple_alloc/free: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}


