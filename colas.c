#include <stdio.h>
#include <stdlib.h>
#define N 3

typedef struct v
{
    float *px;
    int n;
    float mag;
}v;

typedef struct cola
{
    v v1;
    char f;
    struct cola *p;
    void (*push)(struct cola *p, v v1);
    v(*pop)(struct cola **p)
}

cola *crear_c(v v1)
{
    cola *p;
    p=(cola*)malloc(sizeof(cola));
    p->v1.mag=v1.mag;
    p->v1.px=v1.px;
    p->f=0;
    p->p=NULL;
    p->push=push1;
    p->pop=pop1;
    return p;
}

void push1(cola *p, v v1)
{
    cola *pn;
    pn=crear_c(v1);
    while(p->p!=NULL)
            p=p->p;
    p->p=pn;
}

v pop1(cola **p)
{
    cola *pa;
    pa= *p;
    *p=(*p)->p;
    v1.n=pa->v1.n;
    v1.mag=pa->v1.mag;
    v1.px=pa->v1.px;
    free(pa);
    return v1;
}


int main()
{
   v v1;
   cola *pc;
   v1=captura();
   pc=crear_c(v1);
   v1=capturar();
   pc->push(pc, v1);
   v1=captura();
   pc->push(pc, v1);
   v1=pc->pop(&pc);
   imprimir (v1);
   v1=pc->pop(&pc);
   imprimir (v1);
   v1=captura();
   pc->push(pc, v1);
   return 0;
}
