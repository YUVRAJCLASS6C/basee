#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <malloc.h>
#include <errno.h>

#define u64 unsigned long long int
#define u32 unsigned long int
#define u16 unsigned short int


#if defined(__linux__)
    extern void *init_pb;

    #include <sys/mman.h>
    #define MMAP_DEF__(num) (mmap(NULL, (num), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))
    #define MAP_ADDR(num, mul) (mmap((num), (mul) * getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0))
    void map_adder(void *adder, uint8_t mul);

    struct Heap_info {
        char a;
        void *Next_chunk;
    };
    struct Virtual_addr {
        char a;
        u64 size;
    };
#else
    #include <windows.h>
    #if !defined(_CRT_SECURE_NO_WARNINGS)
        #define _CRT_SECURE_NO_WARNINGS
#endif
    #define MMAP_DEF__(num) malloc(num)
#endif

void *HEAPCPY(const void *a, uint64_t s);
void *simple_alloc(size_t num);
int get_fd(const char *filepath, int file_flag);
void simple_realloc(void **ptr, size_t old_s, size_t new_s);
void simple_free(void *ptr);
static int is_zero(const void *ptr, size_t size) {
    const unsigned char *p = ptr;
    for (size_t i = 0; i < size; i++) {
        if (p[i] != 0) {
            return 0;
        }
    }
    return 1;
}



void *simple_alloc(size_t num) {
    if (num <= 0) {
        return NULL;
    }

    void *ptr;

#if defined(__linux__)
    if (num < 100000) {
        struct Heap_info *start = sbrk(num + sizeof(struct Heap_info)+1);

        
        while (start->Next_chunk != 0) {
            start = (struct Heap_info *)start->Next_chunk;
        }

        void **start_s = (void **)start;
        start->a = 'H';
        start->Next_chunk = (void *)((char *)start + num + sizeof(struct Heap_info)+1);
        start_s = (char *)start + num + sizeof(struct Heap_info);
        ptr = (char *)start + sizeof(struct Heap_info) + 1;

    } else {
        size_t total_bytes = ( num + sizeof(struct Virtual_addr));
        ptr = MMAP_DEF__(total_bytes);
        if (ptr == MAP_FAILED) {
            perror("mmap");
            exit(1);
        }
        struct Virtual_addr * info = ptr;
        info->a = 'V';
        info->size = total_bytes;
        ptr = info +1;
    }
#else
 ptr = VirtualAlloc(NULL, num, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#endif

    return ptr;
}

typedef struct string {
    char *head;
    u64 size;
};

void *HEAPCPY(const void *a, uint64_t s) {
    void *ptr = simple_alloc(s);
    memcpy(ptr, a, s);
    return ptr;
}
#if defined(__linux__)

void map_adder(void *adder, uint8_t mul) {
    void *ptr = MAP_ADDR(adder, mul);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
}
#endif
void simple_free(void *ptr) {
#if defined(_WIN32) || defined(_WIN64)
    VirtualFree(ptr, 0, MEM_RELEASE);
#else
    struct Virtual_addr *info = ((struct Virtual_addr *)ptr) - 1;
    if (info->a == 'V'){
        int err = munmap(info,info->size);
        if (err == -1) {
            perror("munmap");
            exit(1);
        }
    }
    else {

    }
#endif
}

void simple_realloc(void **ptr, size_t old_s, size_t new_s) {
    void *n_ptr = simple_alloc(new_s);
    memcpy(n_ptr, *ptr, old_s);
    simple_free(*ptr);
    *ptr = n_ptr;
}

int get_fd(const char *filepath, int file_flag) {
    int fd = -1;

    if (file_flag == 0) {
        fd = open(filepath, O_CREAT | O_WRONLY);
    }
    if (file_flag == 1) {
        fd = open(filepath, O_RDWR | O_APPEND);
    }

    if (!(fd != -1)) {
        int hello = __LINE__;
        fprintf(stderr, "Failed exction at %d\n", hello);
    }

    return fd;
}

