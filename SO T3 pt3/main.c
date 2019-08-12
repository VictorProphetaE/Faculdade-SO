/**
Descrição:Le um arquivo .in e gera um arquivo .out na leitura .in
ele pega a primeira e a segunda matriz antes de ser feito a multiplicação
após a leitura ele inicia o clock e faz a multiplicação da matriz
no término ele mostra o tempo e grava a multiplicação de ambas as matrizes
que foram lidas, sendo q primeiro grava o tamanho de ambas

Nota: Entrar somente com o nome sem .in um espaço e a qntidade de thread de
1 a n thread
GCC compiler and GDB debugger from TDM-GCC (version 4.7.1, 32 bit)

Nome: Victor Propheta Erbano
RGM: 021052
Matéria: Sistemas Operacionais
Prof: Fabrício Sérgio de Paula
Data de Criação: 20/06/2016
Data Modificação: 27/07/2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>


/**Variaveis globais para a alcação das matrizes
e para os números mais a qntidade de thread
*/
int16_t **A = NULL,**B = NULL,**T=NULL;
int16_t ele;
uint16_t n,tam;
int NT;


/**Parte que aloca as matrizes dinamicamente
verificando juntamente se há memória suficiente
caso não haja ele imprime a msg de erro
*/
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

/**Libera as alocações dinamicas
*/
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

/**Multiplicação das matrizes na thread variando
com a qntidade thread, isto é separando por pedaços
ou fatias
*/
void *multiply(void *fatias)
{
    long s = (long)fatias;
    int partir = (s * tam)/NT;
    int para = ((s+1) * tam)/NT;
    int i,j,k;

    for (i = partir; i < para; i++)
    {
        for (j = 0; j < tam; j++)
        {
            T[i][j] = 0;
            for ( k = 0; k < tam; k++)
                T[i][j] += A[i][k]*B[k][j];
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    clock_t t;/**Variavel do tempo*/
    pthread_t *thread;/**variavel da thread*/
    FILE *fp;
    FILE *res;
    char stren[30],strsa[30],str[10];
    int i = 0, j = 0;
    if ( argc != 3 ) /**verifica a qntidade de argumentos*/
    {
        printf( "uso do nome: %s arquivo-matriz somente o nome sem .in\n", argv[0] );
    }
    else
    {
        strcpy(stren,argv[1]);/**copia o nome em stren*/
        strcpy(str,stren);
        strcat(stren,".in");
        strcpy(strsa,str);
        strcat(strsa,".out");
        fp = fopen(stren,"rb");/**abri o arquivo de forma binaria*/
        if(fp == NULL)
        {
            printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
            exit(1);
        }
        while(!feof(fp))
        {
            fread(&n, sizeof(uint16_t), 1, fp);/**lê o primeiro valor q é o tamanho*/
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
                    fread(&ele, sizeof(int16_t), 1, fp);/**lê os valores de cada elemento da matriz A*/
                    A[i][j]= ele;
                }
            }
            for (i=0; i<tam; i++)
            {
                for(j=0; j<tam; j++)
                {
                    fread(&ele, sizeof(int16_t), 1, fp);/**lê os valores de cada elemento da matriz B*/
                    B[i][j]= ele;
                }
            }
            printf("\n");
        }

        NT = atoi(argv[2]);/**NT recebe a qntidade de thread q serão usados*/
        if(NT>=1)
        {
            t = clock();/**inicia o relógio para ver a diferença do tempo*/
            T = aloca(tam,tam);/**aloca a matriz thread*/

            thread = (pthread_t*) malloc(NT*sizeof(pthread_t));/**aloca a thread*/

            for (i = 1; i < NT; i++)
            {
                if (pthread_create (&thread[i], NULL, multiply, (void*)i) != 0 )/**faz a multiplicação da matriz thread*/
                {
                    perror("Nao foi possivel criar a thread");/**caso ñ seja possivel criar a thread*/
                    free(thread);/**libera a thread caso tenha algum erro*/
                    exit(-1);
                }
            }

            multiply(0);

            for (i = 1; i < NT; i++)
                pthread_join (thread[i], NULL);

            t = clock() - t;/**termina o relogio menos o tempo q foi iniciado*/
            printf ("%f\n",((float)t)/CLOCKS_PER_SEC);/**Imprime o tempo q foi utilizado*/
            res = fopen(strsa,"wb");     /**Criando e escrevendo um arquivo teste.out**/
            if (res == NULL)     /**Verifica se o arquivo está vazio**/
            {
                printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
                exit(1);
            }
            fwrite(&tam, sizeof(int16_t), 1, res);/**Grava o tamanho da matriz thread*/
            for (i=0; i<tam; i++)
            {
                for(j=0; j<tam; j++)
                {
                    fwrite(&T[i][j], sizeof(int16_t), 1, res);/**Grava a matriz thread no resultado*/
                }
            }
        }
        else
            printf("numero de thread nao pode ser 0");

        /**Libera todas as alocações e ponteiros*/
        free(thread);
        A = libera(tam,A);
        B = libera(tam,B);
        T = libera(tam,T);
        /**Fecha todos os ponteiros de arquivos*/
        fclose(fp);
        fclose(res);

    }

    return 0;
}
