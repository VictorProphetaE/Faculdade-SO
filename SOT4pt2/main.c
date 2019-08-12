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
#include <math.h>

int tam = 1, NT = 1;

struct s_filenode
{
    uint32_t valor : 30;
    uint32_t esq : 1; /* 0: não possui filho esquerdo , 1: possui filho esquerdo */
    uint32_t dir : 1;
};

struct s_memnode
{
    uint32_t valor : 30;
    struct s_memnode* esq;
    struct s_memnode* dir;
};

void *leitura(void *fatias)
{
    int s = (int)fatias;
    int partir = (s * tam)/NT;
    int para = ((s+1) * tam)/NT;
    int i;

    printf("computando fatias %d (a partir de linha %d para %d)\n", s, partir, para-1);
    for (i = partir; i < para; i++)
    {

    }
    printf("terminado a fatia %d\n", s);
    return 0;
}

int main()
{
    struct s_memnode memoria;
    struct s_filenode file;
    uint32_t n;
    pthread_t *thread;
    FILE *fp;
    char stren[30];
    int i;
    /**Le o nome do arquivo copia para o str concatena com o .bin e concatena
    com .sim.out do arquvio de saida*/
    printf("Nome do arquivo de entrada mais: ");
    scanf("%s",stren);
    strcat(stren,".data");
    fp = fopen(stren,"rb");

    if (fp == NULL)
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
        exit(1);
    }
    else
    {
        while(!feof(fp))
        {
            fread(&n, sizeof(uint32_t), 1, fp);
            if( feof(fp) )
            {
                break ;
            }
            memoria.valor = n;
            memoria.esq = (n>>31&0X1);
            memoria.dir = (n>>30&0X1);
            printf("0X%.8X\n",memoria.valor);/**Imprime na tela o resultado*/
            printf("0X%.8X\n",memoria.esq);/**Imprime na tela o resultado*/
            printf("0X%.8X\n",memoria.dir);
            printf("\n");
        }
    }

    if(NT>=1)
    {
        thread = (pthread_t*) malloc(NT*sizeof(pthread_t));

        for (i = 1; i < NT; i++)
        {
            if (pthread_create (&thread[i], NULL, leitura, (void*)i) != 0 )
            {
                perror("Nao foi possivel criar a thread");
                free(thread);
                exit(-1);
            }
        }
        leitura(0);

        for (i = 1; i < NT; i++)
            pthread_join (thread[i], NULL);
    }

    /**Fecha todos os ponteiros de arquivos*/
    free(thread);
    fclose(fp);

    return 0;
}
