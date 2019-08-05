#include <stdio.h>
#include <stdlib.h> 



typedef union dato
{
    char c;
    int i;
    float f;
    double d;
}dato;
 
typedef struct cola
{
    dato d;
    struct cola *siguente;
    struct cola *(*push1)(struct cola *p, dato d);
    struct cola *(*pop1)(struct cola *p, dato *d);
}cola;
cola* pop(cola *c, dato *d);
cola* push(cola *c, dato d);
cola* push(cola *c, dato d)
{ 
	cola *nv=NULL;
	nv=(cola*)malloc(sizeof(cola));
	cola *aux;
	nv->d.d=d.d;
	nv->push1=push;
	nv->pop1=pop;
        if(c==NULL)
    {
        nv->siguente = NULL;
        c=nv;
        return c;
    }
    else if(c->siguente==NULL)
    {
        c->siguente =nv ;
        nv->siguente = NULL;
        return c;
    }
    else
    {
        aux=c;
        while(aux->siguente!=NULL)
            aux=aux->siguente;
        aux->siguente=nv;
        nv->siguente = NULL;
        return c;
    }
}


cola* pop(cola *c, dato *d){
	if(c==NULL){
	printf("\ncola Vacia");
	return NULL;
}
	if(c->siguente==NULL){
	    *d=c->d;
		free(c);
		return NULL;
	}
	*d=c->d;
	cola* black=c->siguente;
	free(c);
	c=black;
	return c;
	
}


int main(){
	cola *list=NULL;
	dato x;
	int i;
	x.d=1;
	list=push(list,x);
	x.d=2;
	list=push(list,x);
	for(x.d=1;x.d<20;x.d++){
	printf("\npush(%f)",x.d);
		list=list->push1(list,x);
	}
	for(i=0;i<20;i++){
		list=list->pop1(list,&x);
		printf("\n%d-%f",i,x.d);
	}
	list=pop(list,&x);
	printf("\n%d-%f",i,x.d);
	list=pop(list,&x);
	list=pop(list,&x);
	
	return 0;
}
