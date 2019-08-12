#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define IM 16
#define RT 5
#define RS 5
#define RD 5
#define OP_CODE 6
#define SHAMT 5
#define FUNCT 6
#define TARGET 26

int main()
{
    /**opcode rt,rs,imm*/
    /**addi r6,r5,35  */


    FILE *fp;
    FILE *res;
    uint32_t instrucao=0,instrucao1=0;

    fp = fopen("loop.bin","r");
    res = fopen("teste.bin","r");
    if (fp == NULL)
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
    }
    while(!feof(fp))
    {
        fread(&instrucao, sizeof(int), 1, fp);
        printf("0X%.8X\n",instrucao);
    }
    printf("\n");
    if (res == NULL)
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
    }
    while(!feof(res))
    {
        fread(&instrucao1, sizeof(int), 1, res);
        printf("0X%.8X\n",instrucao1);
    }
    return 0;
}
