#ifndef FD___C___INCLUDE__
#define FD___C___INCLUDE__
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <malloc.h>
#define ___CONS_ ((1ULL << 53) - 1)
#if defined(__linux__)
  void * init_pb = NULL;
  long __pagesize;
  #include <sys/mman.h>
  #define MMAP_DEF__(num) (mmap(NULL,(num),PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS|MAP_NORESERVE,-1,0))
  #define MAP_ADDR(num,mul) (mmap((num),(mul)*getpagesize(),PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED,-1,0))
  void map_adder(void * adder,uint8_t mul);
  __attribute__((constructor))
  void before_main(){
    init_pb = sbrk(0);
    long __pagesize = sysconf(_SC_PAGESIZE);
  }
#else
  #include <windows.h>
#if !defined(_CRT_SECURE_NO_WARNINGS)
        #define _CRT_SECURE_NO_WARNINGS
#endif
  #define MMAP_DEF__(num) malloc(num)
#endif
void * HEAPCPY(const void * a, uint64_t s);
void *simple_alloc(size_t num);
int get_fd(const char* filepath, int file_flag);
void simple_realloc(void** ptr, size_t old_s, size_t new_s);
void simple_free(void* ptr);
#endif
