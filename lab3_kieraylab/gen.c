#include "happy.h"

static struct gen
{
    int error;
    int data;
    void* stack;
    __ctx_type ctx;
    struct gen* caller;
    void* eh_list;
    void (*f)(int);
} __gen_0;
struct gen* __this_gen = &__gen_0;

int yield(int value)
{
    if (__this_gen->caller == NULL)
        throw(ERR_GENNIL);
    __this_gen->data = value;

    if(__ctx_record(&__this_gen->ctx) == 0)
    {
        __this_gen = __this_gen->caller;
        __ctx_recover(&__this_gen->ctx, 1);
    }
    

    return __this_gen->data;
}

int send(struct gen* gen, int value)
{
    if (gen == NULL)
        throw(ERR_GENNIL);
    if (gen->error)
        throw(gen->error);
    gen->data = value;

    if(__ctx_record(&__this_gen->ctx) == 0)
    {
        gen->caller = __this_gen;
        __this_gen = gen;
        __ctx_recover(&__this_gen->ctx, 1);
    }

    if (gen->error)
        throw(gen->error);
    return gen->data;
}

void __throw_error()
{
    throw(ERR_GENEND);
}

struct gen* generator(void (*f)(int), int arg)
{
    struct gen* g = malloc(sizeof(*g));
    memset(g, 0, sizeof(*g));
    g->f = f;
    g->stack = malloc(8192);
    g->ctx.rsp = (g->stack + 0x1fe0);
    *(void**)(g->ctx.rsp + 0x8) = __throw_error;
    g->ctx.jmp = *f;
    g->ctx.rdi = arg;
    return g;
}

void genfree(struct gen** g)
{
    if (*g == NULL)
        throw(ERR_GENNIL);
    free((*g)->stack);
    free(*g);
    *g = NULL;
}

void __eh_push(void* ctx)
{
    assert(ctx != NULL);

    void** v = ctx;
    *v = __this_gen->eh_list;
    __this_gen->eh_list = ctx;
}

void* __eh_pop()
{
    assert(__this_gen->eh_list != NULL);

    void* c = __this_gen->eh_list;
    __this_gen->eh_list = *((void**)(__this_gen->eh_list));

    return c;

}

void* __eh_head()
{
    return __this_gen->eh_list;
}

void throw(int error)
{
    if (error == 0)
        throw(ERR_THROW0);
    if (__eh_head() == NULL)
    {
        __this_gen->error = error;
        __this_gen = __this_gen->caller;
        __ctx_recover(&__this_gen->ctx, 1);
    }
    __ctx_type* ctx = __eh_pop();
    __ctx_recover(ctx, error);

    assert(0); // shouldn't run here
}
