#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define N 16
#define B 64
#define TB 64//(B/sizeof(float)<N ? B/sizeof(float) : N)

#define GET_TIME(actual){ \
    struct timeval t; \
    gettimeofday(&t,NULL); \
    actual=t.tv_sec+t.tv_usec/1000000.0; }

using namespace std;


float matrizA[N][N];
float matrizB[N][N];
float matrizC[N][N];

void InicializarMatrices() // asignar valores a las matrices A y B
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            matrizA[i][j]=rand()%100+1;//(float)rand();
            matrizB[i][j]=rand()%100+1;//(float)rand();
        }
    }
}

void ResetearMatriz() //Inicializa en cero la matriz C
{
    for(int i=0;i<N;i++)
    {
        matrizC[i][i]=0.0;
        for(int j=i+1;j<N;j++)
        {
            matrizC[j][i]=matrizC[i][j]=0.0;
        }
    }
}

void MultThreeNestedLoop()
{
    float sum;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            sum=0.0;
            for(int k=0;k<N;k++)
            {
                sum+=matrizA[i][k]*matrizB[k][j];
            }
            matrizC[i][j]=sum;
        }
    }
}

void MultBlockedSixNestedLoop()
{
    //ResetearMatriz();
    float sum;
    for(int ii=0;ii<N;ii+= TB)
    {
        for(int jj=0;jj<N;jj+= TB)
        {
            for(int kk=0;kk<N;kk+= TB)
            {
                for(int i=ii;i<((ii+TB)>N?N:(ii+TB));i++)
                {
                    for(int j = jj; j<((jj+TB)>N?N:(jj+TB)); j++)
                    {
                        sum=0.0;
                        for(int k = kk; k<((kk+TB)>N?N:(kk+TB)); k++)
                        {
                            sum += matrizA[i][k]*matrizB[k][j];
                        }
                        matrizC[i][j]=sum;
                    }
                }
            }
        }
    }
}


void ImprimirMatrizResultado()
{
    cout<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cout<<matrizC[i][j]<<"\t";
        }
        cout<<endl;
    }
}

int main()
{
    double tIni, tFin;
    cout<<"Matrices cuadradas de"<<N<<"x"<<N<<endl;
    srand(10);
    InicializarMatrices();
    cout<<TB<<endl;

    GET_TIME(tIni);
    MultThreeNestedLoop();
    GET_TIME(tFin);
    //ImprimirMatrizResultado();
    printf("Tiempo: %f s \n",tFin-tIni);

    GET_TIME(tIni);
    MultBlockedSixNestedLoop();
    GET_TIME(tFin);
    //ImprimirMatrizResultado();
    printf("Tiempo: %f s \n",tFin-tIni);

    return 0;
}
