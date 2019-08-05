#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ND 3

typedef struct lt{
	int x;
	struct lt *s, *a;
}lt;

void general(int *x, int n)
{
	int i;
	for (i = 0; i < n; i++)
		x[i] = (int)(100 * ((1.0 * rand()) / RAND_MAX));
}

void imprimir(int *x, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("x[%d] = %d\n", i+1, x[i]);
}

void burbuja(int *x, int n)
{
	int i, j, aux;
	for (i = 0; i < n - 1; i++)
		for (j = i + 1; j < n; j++)
			if (x[i]>x[j])
			{
				aux = x[i];
				x[i] = x[j];
				x[j] = aux;
			}
}

void intersion(int *x, int n)
{
	int i, j, aux;
	for (i = 1; i < n; i++)
	{
		j = i - 1;
		aux = x[i];
		while ((j >= 0) && (x[j] > aux))
		{
			x[j + 1] = x[j];
			j--;
		}
		x[j + 1] = aux;
	}
}

void swap(int *x, int *y)
{
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

int particion(int *x, int l, int r)
{
	int p, s, i;
	p = (r - l) / 2 + l;
	swap(x + p, x + r);
	s = l;
	for (i = l; i < r; i++)
	{
		if (x[i]<=x[r])
		{
			swap(x + i, x + s);
			s++;
		}
	}
	swap(x + s, x + r);
	return s;
}

void qs(int *x, int l, int r)
{
	int pi;
	if (l < r)
	{
		pi = particion(x, l, r);
		qs(x, l, pi - 1);
		qs(x, pi + 1, r);
	}
}

void quicksort(int *x, int n)
{
	qs(x, 0, n - 1);
}

void conteo(int *x, int n)
{
	int *h, i, j, k;
	h = (int*)calloc(101,sizeof(int));
	for (i = 0; i < n; i++)
		h[x[i]]++;
	j = 0;
	i = n;
	while (i > 0)
	{
		for (k = 0; k < h[j]; k++)
		{
			x[n - i] = j;
			i--;
		}
		j++;
	}
	free(h);
}

void insertar(lt **lt1, int *x, int i)
{
	lt *aux;
	int ind;
	ind = x[i] / 34;
	if (lt1[ind] == NULL)
	{
		lt1[ind] = (lt*)malloc(sizeof(lt));
		lt1[ind]->x = x[i];
		lt1[ind]->a = NULL;
		lt1[ind]->s = NULL;
	}
	else
	{
		aux = (lt*)malloc(sizeof(lt));
		aux->x = x[i];
		while (lt1[ind]->a != NULL)
			lt1[ind] = lt1[ind]->a;
		while ((lt1[ind]->x < x[i]) && (lt1[ind]->s!=NULL))
			lt1[ind] = lt1[ind]->s;
		if (lt1[ind]->x > x[i])
		{
			aux->a = lt1[ind]->a;
			aux->s = lt1[ind];
			if (lt1[ind]->a!=NULL)
				lt1[ind]->a->s = aux;
			lt1[ind]->a = aux;
		}
		else
		{
			aux->s = NULL;
			aux->a = lt1[ind];
			lt1[ind]->s = aux;
		}
	}
}

void extraer(lt **lt1, int *x, int n)
{
	int i, j;
	for (i = 0, j = 0; i < ND; i++)
	{
		if (lt1 != NULL)
		{
			while (lt1[i]->a != NULL)
				lt1[i] = lt1[i]->a;
			while (lt1[i] != NULL)
			{
				x[j] = lt1[i]->x;
				j++;
				if (lt1[i]->s == NULL)
				{
					free(lt1[i]);
					lt1[i] = NULL;
				}
				else
				{
					lt1[i] = lt1[i]->s;
					free(lt1[i]->a);
					lt1[i]->a = NULL;
				}
			}
		}
	}
}

void imprimir2(lt **lt1)
{
	int i;
	lt *aux;
	for (i = 0; i < ND; i++)
	{
		aux = lt1[i];
		while (aux->a != NULL)
			aux = aux->a;
		while (aux != NULL)
		{
			printf("%d\t", aux->x);
			aux = aux->s;
		}
		printf("\n");
	}
}

void bq(int *x, int n)
{
	lt **lt1;
	int i;
	lt1 = (lt**)malloc(ND * sizeof(lt*));
	for (i = 0; i < ND; i++)
		lt1[i] = NULL;
	for (i = 0; i < n; i++)
		insertar(lt1, x, i);
	imprimir2(lt1);
	extraer(lt1, x, n);
	free(lt1);
}

int main(int argc, char *argv[])
{
	int *x, n;
	srand((long int)time(NULL));
	printf("Ingrese el numero de datos: ");
	scanf("%d", &n);
	x = (int*)malloc(n*sizeof(int));
	general(x, n);
	imprimir(x, n);
	bq(x, n);
	imprimir(x, n);
	free(x);
	return 0;
}

