#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define VMAX 1000
#define VMIN -1000
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

void bq(int *x, int n)
{
	lt **lt1;
	register int i;
	lt1 = (lt**)malloc(ND * sizeof(lt*));
	for (i = 0; i < ND; i++)
		lt1[i] = NULL;
	for (i = 0; i < n; i++)
		insertar(lt1, x, i);
	imprimir2(lt1);
	extraer(lt1, x, n);
	free(lt1);
}

void bq(int **x, int n)
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
	int *x, i, j, k, max, NP, *vN, oct_i, oct_f, ini, fin, lvN, dp, n;
    double **tiempo, *paux, **esta;
    clock_t ticks1, ticks2;
    FILE *fp;
    srand((long int)time(NULL));
	//printf("Ingrese el numero de datos: ");
	//scanf("%d", &n);
    printf("Ingrese el numero de pruebas: ");
    scanf("%d", &NP);
    printf("Ingrese la octava inicial: ");
    scanf("%d", &oct_i);
    printf("Ingrese la octava final: ");
    scanf("%d", &oct_f);
    printf("Ingrese el valor maximo: ");
    scanf("%d", &max);
    printf("Quiere mostrar los resultados: ");
    scanf("%d", &dp);
    ini = pow(2, oct_i);
    fin = pow(2, oct_f);
    lvN = (oct_f-oct_i)+1;
    vN = (int*)malloc(lvN*sizeof(int));
    paux = (double*)malloc(NP*lvN*sizeof(double));
    tiempo = (double**)malloc(NP*sizeof(double*));
    for(i=0; i<NP; i++)
        tiempo[i]=paux+i*lvN;
    paux = (double*)calloc(3*lvN,sizeof(double));
    esta = (double**)malloc(3*sizeof(double*));
    for(i=0; i<3; i++)
        esta[i]=paux+i*lvN;
    fp=fopen("Bucket.txt", "wt");
    for(i=0; i<lvN; i++)
    {
        vN[i] = pow(2,i+oct_i);
        x=(int*)malloc(vN[i]*sizeof(int));
        for(j=0; j<NP; j++)
        {
            x[k]=(max*(1.0*rand()))/RAND_MAX;
            ticks1=clock();
            bq(x, vN[i]);
            ticks2=clock();
            tiempo[j][i]=(double)((ticks2-ticks1)/(CLOCKS_PER_SEC/1000));
            if(dp)
                printf("Tiempo[%d][%d]: %f\n", j+1, i+1, tiempo[j][i]);
            if(j==0)
                esta[0][i]=tiempo[j][i];
            else if(tiempo[j][i]<esta[0][i])
                esta[0][i]=tiempo[j][i];
            esta[1][i]+=tiempo[j][i];
            if(tiempo[j][i]>esta[2][i])
                esta[2][i]=tiempo[j][i];
        }
        esta[1][i]/=NP;
        if(dp)
            printf("Minimo: %f\nMedia: %f\nMaximo: %f\n", esta[0][i], esta[1][i], esta[2][i]);
        fprintf(fp, "%d\t%f\t%f\t%f\n", vN[i], esta[0][i], esta[1][i], esta[2][i]);
        free(x);
        printf("%d\n", (int)((100.0*i)/lvN));
    }/*
    general(x, n);
	imprimir(x, n);
	bq(x, n);
	imprimir(x, n);*/
	free(x);
    fclose(fp);
    free(vN);
    free(paux);
    free(tiempo[0]);
    free(tiempo);
    free(esta);
}

