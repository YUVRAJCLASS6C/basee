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
    volatile void *end_pb;
    int is_run = 0;
    #include <sys/mman.h>
    #define MMAP_DEF__(num) (mmap(NULL, (num), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))
    #define MAP_ADDR(num, mul) (mmap((num), (mul) * getpagesize(), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0))
    void map_adder(void *adder, uint8_t mul);

    struct Heap_info {
        uint64_t num;
    };
    struct Virtual_addr {
        uint64_t num;
    };
#else
    #include <windows.h>
    #if !defined(_CRT_SECURE_NO_WARNINGS)
        #define _CRT_SECURE_NO_WARNINGS
#endif
    #define MMAP_DEF__(num) malloc(num)
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__aarch64__) || defined(__ppc64__)
#define log2(x) (63 - __builtin_clzll((unsigned long long)(x)))
#else
#define log2(x) (31 - __builtin_clz((unsigned int)(x)))
#endif
unsigned long pagesize ;
uint8_t ex;
void base(){
    if (is_run == 0){
    end_pb = init_pb;
    #if defined(__linux__)

    pagesize = sysconf(_SC_PAGESIZE);
#else 

SYSTEM_INFO si;
GetSystemInfo(&si);
 pagesize = si.dwPageSize;
#endif
ex = log2(pagesize);
        is_run = 1;
    }
}
__attribute__((constructor))
void my_init() {
    base();
}

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
#define MB 1000000


void *simple_alloc(size_t num) {
    if (__builtin_expect(num <= 0,1)) {
        return NULL;
    }

    void *ptr;

#if defined(__linux__)
    if (num < MB) {
        struct Heap_info *start = sbrk(num + sizeof(struct Heap_info));
        
        uint64_t r = (start->num & ((1ULL << 61) - 1)); 
        while (r != 0) {
            start = (uint64_t * )start + r;
            r = ((start->num) & ((1ULL << 61) - 1));
        }

        start->num = (((num + sizeof(struct Heap_info) + 7) >> 3));
        start->num |= 1ULL << 63;
        ptr = (char *)start + sizeof(struct Heap_info) ;

    } else {
        uint64_t r = (( num + sizeof(struct Virtual_addr) + pagesize - 1) >> ex);
        size_t total_bytes = r;
        ptr = MMAP_DEF__(total_bytes << ex);
        if (ptr == MAP_FAILED) {
            perror("mmap");
            exit(1);
        }
        struct Virtual_addr * info = ptr;
        info->num = total_bytes;
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
    if ((info->num >> 63 ) == 0){
        int err = madvise(info,(info->num & ((1ULL << 53) - 1)) << ex,MADV_DONTNEED);
        if (err == -1) {
            perror("madvise");
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

