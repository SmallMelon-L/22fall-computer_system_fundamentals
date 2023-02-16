#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include <string.h>

typedef unsigned long long u64;
typedef struct __ctx_type
{
    void *next, *rsp, *rbx, *rbp, *r12, *r13, *r14, *r15, *rsi;
    long rdi;
    void *jmp;
} __ctx_type;
struct gen;

#define ERR_THROW0 -1
#define ERR_GENEND -2
#define ERR_GENNIL -3

int __ctx_record(__ctx_type*);
void __ctx_recover(__ctx_type*, int);

void __eh_push(void*);
void* __eh_pop();
void throw(int);
static inline void __eh_check_cleanup(int* error) {
    if(*error == 0)
    {
         __eh_pop();
    }
}

#define try int error __attribute__((cleanup(__eh_check_cleanup))) = 0; \
__ctx_type c; \
error = __ctx_record(&c); \
if(error == 0) \
{ \
__eh_push(&c);


#define catch } \
else 


struct gen* generator(void (*)(int), int);
void genfree(struct gen**);
int yield(int);
int send(struct gen*, int);
#define next(gen) send(gen, 0)
