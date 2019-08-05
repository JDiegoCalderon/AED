#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define VMAX 1000
#define VMIN -1000

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

void conteo1(int *x, int n)
{
	register int i, j, k;
	register int *h;
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

void conteo2(int **X, int n, int min, int max)
{
	int i, j, *pX0;
	int *h2, *h1;
    pX0=(int*)malloc(n*sizeof(int));
	h2 = (int*)calloc((max-min+1),sizeof(int));
	h2=h2-min;
	for(i=0; i<n; i++)
        h1[*X[i]]++;
	for (i = 0; i < n; i++)
	{
	    while(h1[j]==0)
            j++;
	    pX0[i]=j;
	    h1[j]--;
    }
    free(pX0);
	free(h2);
}

void conteo3(int **X, int n)
{
	int *h, i, j, k;
	h = (int*)calloc(101,sizeof(int));
	for (i = 0; i < n; i++)
		h[*X[i]]++;
	j = 0;
	i = n;
	while (i > 0)
	{
		for (k = 0; k < h[j]; k++)
		{
			*X[n - i] = j;
			i--;
		}
		j++;
	}
	free(h);
}

void conteo4(int *x, int n)
{
	int **h, i, j, k;
	h = (int**)calloc(101,sizeof(int*));
	for (i = 0; i < n; i++)
		*h[x[i]]++;
	j = 0;
	i = n;
	while (i > 0)
	{
		for (k = 0; k < *h[j]; k++)
		{
			x[n - i] = j;
			i--;
		}
		j++;
	}
	free(h);
}



int main(int argc, const char * argv[]) {
    int *x, i, j, k, max, NP, *vN, oct_i, oct_f, ini, fin, lvN, dp, **X1;
    double **tiempo, *paux, **esta;
    clock_t ticks1, ticks2;
    FILE *fp;
    srand((unsigned int)time(NULL));
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
    fp=fopen("conteo.txt", "wt");
    for(i=0; i<lvN; i++)
    {
        vN[i] = pow(2,i+oct_i);
        x=(int*)malloc(vN[i]*sizeof(int));
        X1=(int**)malloc(vN[i]*sizeof(int*));
        for(j=0; j<NP; j++)
        {
                //x[k]=(max*(1.0*rand()))/RAND_MAX;
            //para doble puntero
                for(k=0; k<vN[i]; k++)
            {
                x[k]=(max*(1.0*rand()))/RAND_MAX;
                //x[k]= (VMAX-VMIN)*((1.0*rand())/RAND_MAX)+VMIN;
                X1[k]=x+k;
                //*X[k]=(max*(1.0*rand()))/RAND_MAX;
            }
            ticks1=clock();
            //conteo(x, vN[i]);
            //conteo1(x, vN[i]);
            //conteo2(X1, vN[i], VMIN, VMAX);
            conteo3(X1, vN[i]);
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
        free(X1);
        printf("%d\n", (int)((100.0*i)/lvN));
    }
    fclose(fp);
    free(vN);
    free(paux);
    free(tiempo[0]);
    free(tiempo);
    free(esta);
    return 0;
}

