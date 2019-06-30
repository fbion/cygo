#ifndef _CXRT_BASE_H_
#define _CXRT_BASE_H_


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/socket.h>

#include <gc.h> // must put after <pthread.h>

// golang type map
// typedef uint8_t bool;
typedef uint8_t byte;
typedef uint8_t uint8;
typedef int8_t int8;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint32_t uint32;
typedef uint32_t rune;
typedef int32_t int32;
typedef uint64_t uint64;
typedef int64_t int64;
typedef float float32;
typedef double float64;
typedef uintptr_t uintptr;
typedef unsigned int uint;
typedef void* error;

#define nilptr NULL

typedef struct _type {
    void* reserver;
} _type;
typedef struct cxeface {
    _type* _type; // _type
    void* data;
} cxeface;
typedef struct itab {
    void* reserver;
} itab;
typedef struct cxiface {
    itab* itab; // itab
    void* data;
} cxiface;
cxeface cxeface_new_of2(void* data, int sz);

// utils
void println(const char* fmt, ...);
void println2(const char* filename, int lineno, const char* funcname, const char* fmt, ...);

// TODO
#define gogorun

extern void cxrt_init_env();
extern void cxrt_routine_post(void (*f)(void*), void*arg);
extern void* cxrt_chan_new(int sz);
extern void cxrt_chan_send(void*ch, void*arg);
extern void* cxrt_chan_recv(void*arg);

#include <sys/types.h>
extern pid_t gettid();

// cxmemory
void* cxmalloc(size_t size);
void* cxrealloc(void*ptr, size_t size);
void cxfree(void* ptr);
char* cxstrdup(char* str);
char* cxstrndup(char* str, int n);
void* cxmemdup(void* ptr, int sz);

#include <collectc/hashtable.h>
#include <collectc/array.h>

// cxstring begin
typedef struct cxstring { char* ptr; int len; } cxstring;
// typedef struct cxstring string;
cxstring* cxstring_new_cstr(char* s);
cxstring* cxstring_new_cstr2(char* s, int len);
cxstring* cxstring_add(cxstring* s0, cxstring* s1);
int cxstring_len(cxstring* s);
cxstring* cxstring_sub(cxstring* s0, int start, int end);
bool cxstring_eq(cxstring* s0, cxstring* s1);
bool cxstring_ne(cxstring* s0, cxstring* s1);
char* CString(cxstring* s);
cxstring* GoString(char* s);
// cxstring end

// cxhashtable begin
HashTable* cxhashtable_new();
size_t cxhashtable_hash_str(const char *key);
size_t cxhashtable_hash_str2(const char *key, int len);
// cxhashtable end

// cxarray begin
Array* cxarray_new();
Array* cxarray_slice(Array* a0, int start, int end);
void* cxarray_get_at(Array* a0, int idx);

#endif
