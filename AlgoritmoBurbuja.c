#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int burbuja(int *x, int N)
{
    int i, j, aux;
    for(i=0; i<(N-1); i++)
        for(j=i+1; j<N; j++)
            if(x[i]>x[j])
            {
                aux=x[i];
                x[i]=x[j];
                x[j]=aux;
            }
    return 0;
}

int burbuja1(int *x, int N)
{
    int i, j;
    for(i=0; i<(N-1); i++)
        for(j=i+1; j<N; j++)
            if(x[i]>x[j])
            {
                x[i]=x[i]+x[j];
                x[j]=x[i]-x[j];
                x[i]=x[i]-x[j];
            }
    return 0;
}

int burbuja2(int *x, int N)
{
    register int i, j;
    register int xi, xj;
    for(i=0; i<(N-1); i++)
        for(j=i+1; j<N; j++)
        {
            xi = x[i];
            xj = x[j];
            if(xi>xj)
            {
                xi=xi+xj;
                xj=xi-xj;
                xi=xi-xj;
            }
            x[i] = xi;
            x[j] = xj;
        }
    return 0;
}

int burbuja3(int *x, int N)
{
    register int i, j;
    for(i=0; i<(N-1); i++)
        for(j=i+1; j<N; j++)
            if(x[i]>x[j])
            {
                x[i]=x[i]+x[j];
                x[j]=x[i]-x[j];
                x[i]=x[i]-x[j];
            }
    return 0;
}

int recur(int *x, int i, int j, int N)
{
    if(j<N)
    {
        if(x[i]>x[j])
        {
            x[i]=x[i]+x[j];
            x[j]=x[i]-x[j];
            x[i]=x[i]-x[j];
        }
        return recur(x, i, j+1, N);
    }
    else
        return 0;
}

int burbuja4(int *x, int N)
{
    register int i;
    for(i=0; i<(N-1); i++)
        recur(x, i, i+1, N);
    return 0;
}

int burbuja5(int **X, int N)
{
    int i, j, *aux;
    for(i=0; i<N-1; i++)
        for(j=i+1; j<N; j++)
            if(*X[i]>*X[j])
            {
                aux=X[i];
                X[i]=X[j];
                X[j]=aux;
            }
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
    fp=fopen("Burbuja.txt", "wt");
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
                X1[k]=x+k;
                //*X[k]=(max*(1.0*rand()))/RAND_MAX;
            }
            ticks1=clock();
            //burbuja(x, vN[i]);
            //burbuja1(x, vN[i]);
            //burbuja2(x, vN[i]);
            //burbuja3(x, vN[i]);
            //burbuja4(x, vN[i]);
            burbuja5(X1, vN[i]);
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
