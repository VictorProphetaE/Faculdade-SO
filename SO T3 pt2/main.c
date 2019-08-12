/**
Descrição:Le um arquivo .bin e gera um arquivo .sim.out na leitura .bin
ele pega as instruções e executa a informação contida nela, no sim.out
ele pega os registradores + ir, pc, base,limit da memoria e o mode

Nota:GCC compiler and GDB debugger from TDM-GCC (version 4.7.1, 32 bit)

Nome: Victor Propheta Erbano
RGM: 021052
Matéria: Sistemas Operacionais
Prof: Fabrício Sérgio de Paula
Data de Criação: 20/06/2016
Data Modificação: 15/07/2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>

int16_t **A = NULL,**B = NULL,**M= NULL,**T=NULL;
int16_t ele;
uint16_t n,tam;
int NT;

int16_t **aloca(uint16_t lin, uint16_t col)
{
    int16_t **m,i;
    m = (int16_t **) malloc(lin*sizeof(int16_t *));
    if(m!=NULL)
    {
        for (i=0; i<lin; i++)
        {
            m[i] = (int16_t *) calloc(col,sizeof(int16_t));
            if(m[i]==NULL)
            {
                printf("Memória Insuficiente.");
                exit(1);
            }
        }
    }
    else
    {
        printf("Memória Insuficiente.");
        exit(1);
    }
    return(m);
}

int16_t **libera(int16_t lin, int16_t **m)
{
    int i;
    if(m==NULL)
    {
        return(NULL);
    }

    for (i=0; i<lin; i++)
    {
        free(m[i]);
    }
    free(m);
    return(NULL);
}


void escreve(int16_t lin, int16_t col, int16_t **m)
{
    int i,j;
    for (i=0; i<lin; i++)
    {
        for(j=0; j<col; j++)
        {
            printf("% "PRId16, m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void *multiply(void *fatias)
{
    int s = (int)fatias;
    int partir = (s * tam)/NT;
    int para = ((s+1) * tam)/NT;
    int i,j,k;

    printf("computando fatias %d (a partir de linha %d para %d)\n", s, partir, para-1);
    for (i = partir; i < para; i++)
    {
        for (j = 0; j < tam; j++)
        {
            T[i][j] = 0;
            for ( k = 0; k < tam; k++)
                T[i][j] += A[i][k]*B[k][j];
        }
    }
    printf("terminado a fatia %d\n", s);
    return 0;
}

int main()
{
    clock_t t;
    pthread_t *thread;
    FILE *fp;
    FILE *res;
    char stren[30],strsa[30],str[10];
    int i = 0, j = 0,k = 0;
    srand(time(NULL));
    /**Le o nome do arquivo copia para o str concatena com o .bin e concatena
    com .sim.out do arquvio de saida*/
    printf("Nome do arquivo de entrada mais: ");
    scanf("%s",stren);
    strcpy(str,stren);
    strcat(stren,".in");
    strcpy(strsa,str);
    strcat(strsa,".out");
    fp = fopen(stren,"rb");
    if (fp == NULL)     /**Verifica se o arquivo está vazio**/
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
        exit(1);
    }
    else
    {
        while(!feof(fp))
        {
            fread(&n, sizeof(uint16_t), 1, fp);
            if( feof(fp) )
            {
                break ;
            }
            tam = n;
            A = aloca(tam,tam);
            B = aloca(tam,tam);
            for (i=0; i<tam; i++)
            {
                for(j=0; j<tam; j++)
                {
                    fread(&ele, sizeof(int16_t), 1, fp);
                    //printf("% "PRId16, ele);
                    A[i][j]= ele;
                }
            }
            for (i=0; i<tam; i++)
            {
                for(j=0; j<tam; j++)
                {
                    fread(&ele, sizeof(int16_t), 1, fp);
                    //printf("% "PRId16, ele);
                    B[i][j]= ele;
                }
            }
            printf("\n");
        }
    }
    M = aloca(tam,tam);
    for (i = 0 ; i < tam; i++ )
    {
        for (j = 0; j < tam; j++)
        {
            M[i][j] = 0;
            for (k = 0; k < tam; k++)
            {
                M[i][j] += A[i][k] * B[k][j];
            }
        }
    }


    printf("Numero de thread\n");
    scanf("%d",&NT);
    if(NT>=1)
    {
        t = clock();
        T = aloca(tam,tam);

        thread = (pthread_t*) malloc(NT*sizeof(pthread_t));

        for (i = 1; i < NT; i++)
        {
            if (pthread_create (&thread[i], NULL, multiply, (void*)i) != 0 )
            {
                perror("Nao foi possivel criar a thread");
                free(thread);
                exit(-1);
            }
        }

        multiply(0);

        for (i = 1; i < NT; i++)
            pthread_join (thread[i], NULL);

        t = clock() - t;
        printf ("%f\n",((float)t)/CLOCKS_PER_SEC);
        res = fopen(strsa,"wb");     /**Criando e escrevendo um arquivo teste.out**/
        if (res == NULL)     /**Verifica se o arquivo está vazio**/
        {
            printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
            exit(1);
        }
        fwrite(&tam, sizeof(int16_t), 1, res);
        for (i=0; i<tam; i++)
        {
            for(j=0; j<tam; j++)
            {
                fwrite(&T[i][j], sizeof(int16_t), 1, res);
            }
        }
        /**/
        //printf("Principal Thread\n");
        escreve(tam,tam,M);

        //printf("Thread\n");
        escreve(tam,tam,T);
    }
    else
        printf("numero de thread nao pode ser 0");



    free(thread);
    A = libera(tam,A);
    B = libera(tam,B);
    M = libera(tam,M);
    T = libera(tam,T);
    /**Fecha todos os ponteiros de arquivos*/
    fclose(fp);
    fclose(res);

    return 0;
}
