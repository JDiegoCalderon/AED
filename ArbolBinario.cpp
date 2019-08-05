// ArbolBinario.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct nodo
{
	int dato;
	struct nodo *i, *d;
}nodo;

nodo * crear_arbol(int n)
{
	nodo *n1;
	n1 = (nodo*)calloc(1,sizeof(nodo));
	if (n == 1)
	{
		n1->i = NULL;
		n1->d = NULL;
	}
	else
	{
		n1->i = crear_arbol(n - 1);
		n1->d = crear_arbol(n - 1);
	}
	return n1;
}

void cargar(nodo *n1, int *pi, int ni, int dato)
{
	if (ni == 0)
		n1->dato = dato;
	else
	{
		if (pi[0] == 0)
			cargar(n1->i, pi + 1, ni - 1, dato);
		else
			cargar(n1->d, pi + 1, ni - 1, dato);
	}
}

void imprimir(nodo *n1)
{
	if (n1 != NULL)
	{
		printf("%d\t", n1->dato);
		imprimir(n1->i);
		imprimir(n1->d);
	}
}

int cargar_n(nodo *n1, int *dato, int nd)
{
	n1->dato = *(dato+nd);
	if (n1->i != NULL)
	{
		nd = cargar_n(n1->i, dato, nd + 1);
		nd = cargar_n(n1->d, dato, nd + 1);
	}
	else
		return nd;
}

int cargar_n2(nodo *n1, int *dato, int nd)
{
	n1->dato = *(dato + nd -1);
	if (n1->i != NULL)
	{
		cargar_n2(n1->i, dato, 2*nd);
		cargar_n2(n1->d, dato, 2*nd + 1);
	}
	else
		return nd;
}

int cargar_l(nodo *n1, int *dato, int nd)
{
	if (n1->d != NULL)
	{
		n1 -> dato = 0;
		nd = cargar_l(n1->i, dato, nd);
		nd = cargar_l(n1->d, dato, nd);
	}
	else
	{
		n1->dato = *(dato + nd);
		return nd + 1;
	}
}

int *cargar_l2(nodo *n1, int *dato)
{
	if (n1->d != NULL)
	{
		n1->dato = 0;
		dato = cargar_l2(n1->i, dato);
		dato = cargar_l2(n1->d, dato);
	}
	else
	{
		n1->dato = *(dato);
		return dato + 1;
	}
}

int evaluar (nodo *n1, int *pi)
{
    if(n1->d==NULL)
    return n1->dato;
    else if(pi[0])
        return evaluar(n1->d,pi+1);
    else
        return evaluar(n1->i,pi+1);

}

int asignar (nodo *n1, int *pi, int dato) {

    if (n1->d==NULL){
        n1->dato=dato;
        return 0;
    }

    else if (pi[0])
        return asignar(n1->d, pi+1, dato);
    else
        return asignar(n1->i, pi+1, dato);
}

int comparar (nodo *n1) {
    if((n1->d->dato==n1->i->dato)&&(n1->d->dato!=2))
        n1->dato = 1;
    else
        n1->dato = 2;
    return 0;
}

int main(int argc, char* argv[])
{
	nodo *r;
	int n, *pi, ni, dato, i;
	printf("Ingrese el numero de niveles: ");
	scanf("%d", &n);
	r = crear_arbol(n);
	do{
		printf("Ingrese el numero de instrucciones: ");
		scanf("%d", &ni);
	} while (ni>=n);
	pi = (int*)calloc(ni, sizeof(int));
	for (i = 0; i < ni; i++)
	{
		printf("PI[%d] = ", i+1);
		scanf("%d", pi+i);
	}
	printf("Ingrese el dato: ");
	scanf("%d", &dato);
	cargar(r, pi, ni, dato);
	imprimir(r);
	printf("\n");
	free(pi);
	ni = (int)pow(2.0,n) - 1;
	pi = (int*)malloc(ni*sizeof(int));
	for (i = 0; i < ni; i++)
	{
		printf("dato[%d] = ", i+1);
		scanf("%d", pi+i);
	}
	cargar_n(r, pi, 0);
	imprimir(r);
	printf("\n");
	cargar_n2(r, pi, 1);
	imprimir(r);
	printf("\n");
	free(pi);
	// Arboles binarios para funciones logicas
	ni = (int)pow(2.0, n-1) ;
	pi = (int*)malloc(ni*sizeof(int));
	for (i = 0; i < ni; i++)
	{
		printf("dato[%d] = ", i + 1);
		scanf("%d", pi + i);
	}
	cargar_l(r, pi, 0);
	imprimir(r);
	printf("\n");
	cargar_l2(r, pi);
	imprimir(r);
	printf("\n");
	evaluar(r, pi);
	imprimir(r);
	printf("\n");
	asignar(r, pi, 0);
	imprimir(r);
	printf("\n");
	free(pi);
	getchar();
	getchar();
	return 0;
}

