#include "FD.h"
#include <string.h>
#define u64 unsigned long long int
#define u32 unsigned long int
#define u16 unsigned short int
void *simple_alloc(size_t num){
  void* ptr = MMAP_DEF__(num);
  #if defined(__linux__)
  if (!(ptr != MAP_FAILED)){
    fprintf(stderr, "Failed excution at %d\n",__LINE__);
  }
  #else 
  assert(ptr != NULLL);
  #endif
  return ptr;
}
typedef struct string {
  char* head;
  u64 size;
}
void * HEAPCPY(const void * a, uint64_t s){
  void* ptr = simple_alloc(s);
  memcpy(ptr,a,s);
  return ptr;
}
void map_adder(void * adder,uint8_t mul){
  void* ptr = MAP_ADDR(adder,mul);
  if (ptr == MAP_FAILED){
    perror("mmap");
    exit(1);
  }
}
void simple_free(void* ptr,size_t size){
  
  #if defined(_WIN32) || defined(_WIN64)
    free(ptr);
  #else
  if (size == 0){
    return;
  }
  int err = munmap(ptr, size);
  if (err == -1){
    perror("munmap");
  }
  #endif
}
void simple_realloc(void** ptr, size_t old_s, size_t new_s){
  void* n_ptr = simple_alloc(new_s);
  memcpy(n_ptr,*ptr,old_s);
  simple_free(*ptr,old_s);
  *ptr = n_ptr;
}
int get_fd(const char* filepath, int file_flag){
  int fd = -1;
  if (file_flag == 0){
   fd = open(filepath,O_CREAT | O_WRONLY);
  }
  if (file_flag == 1){
   fd = open(filepath,O_RDWR |O_APPEND ); 
  }
  if (!(fd != -1)){
    int hello = __LINE__;
    fprintf(stderr,"Failed exction at %d\n",hello);
  }
  return fd;
}
