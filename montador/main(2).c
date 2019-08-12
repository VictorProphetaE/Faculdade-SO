/**
Descrição: Este programa converte um arquivo teste.mips para um arquivo
teste.bin com todas as instruções abaixo
Instruções Tipo de operação
Lógica/aritmética
add, addi, sub, mult, div, and, andi, or, ori, slt, slti,
xor, sll, srl
j, beq, bne, bgez, bgtz     Desvio
lb, sb, lw, sw, lui         Acesso à memória
syscall                     Chamada ao SO
readb                       Leitura de dispositivo
writeb                      Escrita em dispositivo

Nota: Colocar o arquivo na pasta do programa com o nome "teste.mips"
GCC compiler and GDB debugger from TDM-GCC (version 4.7.1, 32 bit)

Nome: Victor Propheta Erbano
RGM: 021052
Matéria: Sistemas Operacionais
Prof: Fabrício Sérgio de Paula
Data de Criação: 29/03/2016
Data Modificação: 08/04/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main()
{
    /**Parte de criação de variaves*/
    FILE *fp; /***/
    FILE *res;  /***/
    char buff[250]; /***/
    const char s[8] =  " ,()\n";    /***/
    char *token,*point,*point1,*arma;   /**Criação de ponteiros*/
    int val=0,val1=0,val2=0,cont=0; /**Criação de valores para ser convertidos*/
    int16_t imm=0;  /***/
    uint32_t instrucao; /***/
    short rs=0,rt=0,opcode=0,rd=0,opcode2=0;    /***/
    int hmm=0;  /***/

    fp = fopen("teste.mips","r");       /**Abrindo o arquivo teste.mips*/
    res = fopen("teste.bin","wb+");     /**Criando e escrevendo um arquivo teste.bin*/
    if (fp == NULL)     /**Verifica se o arquivo está vazio*/
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
    }
    while(!feof(fp))    /**Faz a leitura até o final do arquivo*/
    {
        cont=0;         /**Contador para pegar somente os tokens necessario*/
        fgets(buff, 255, (FILE*)fp);    /**Pega a linha toda*/
        token = strtok(buff, s);        /**token recebe o primeiro palavra do strtok*/
        arma = token;                   /**ponteiro arma recebe token*/
        while( token != NULL )          /**Enquanto token não for NULL ele continua*/
        {
            if (strcmp(arma, "add") == 0)   /**compara arma com add */
            {
                point = token+1;            /**ponteiro recebe o valor de token +1*/
                val = atoi(point);          /**transformação de char para int*/
                rd = val;                   /**rd recebe o valor de já transformado*/
                if(val>=10){                /**Verifica se o valor é maior que 10*/
                    point = token+5;        /**pega o valor na posição +5*/
                    val1 = atoi(point);
                    rs = val1;              /**Guarda o valor em rs*/
                }
                else{
                    point = token+4;            /**Pega o valor na posição +4*/
                    val1 = atoi(point);
                    rs = val1;              /**Guarda o valor em rs*/
                }
                if(val>=10&&val1>=10){         /**Verifica se o valor e o valor 1 é maior que 10*/
                    point1 = token+9;           /**Pega o valor na posição +9*/
                    val2 = atoi(point1);
                    rt = val2;              /**Guarda o valor em rt*/
                }else{
                    if(val1>=10||val>=10)       /**Verifica se o valor ou o valor 1 é maior que 10*/
                    {
                        point1 = token+8;       /**Pega o valor na posição +8*/
                        val2 = atoi(point1);
                        rt = val2;
                    }else
                    {
                        point1 = token+7;       /**Pega o valor na posição +7*/
                        val2 = atoi(point1);
                        rt = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;                 /**Primeiro dos valores do opcode*/
                    opcode2 = 32;               /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);/**Converte bit a bit os valroes e os opcodes*/
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);    /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "addi") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    imm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;
                    }
                }
                if(cont==1)
                {
                    opcode = 8;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "sub") == 0)
            {
                point = token+1;
                val = atoi(point);
                rd = val;
                if(val>=10){
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;
                }
                else{
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+9;
                    val2 = atoi(point1);
                    rt = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;
                    }else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 34;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "mult") == 0)
            {
                point = token+1;
                val = atoi(point);
                rs = val;
                if(val>=10){
                    point = token+5;
                    val1 = atoi(point);
                    rt = val1;
                }
                else{
                    point = token+4;
                    val1 = atoi(point);
                    rt = val1;
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 24;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "div") == 0)
            {
                point = token+1;
                val = atoi(point);
                rs = val;
                if(val>=10){
                    point = token+5;
                    val1 = atoi(point);
                    rt = val1;
                }
                else{
                    point = token+4;
                    val1 = atoi(point);
                    rt = val1;
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 26;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "and") == 0)
            {
                point = token+1;
                val = atoi(point);
                rd = val;
                if(val>=10){
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;
                }
                else{
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;
                }

                if(val>=10&&val1>=10){
                    point1 = token+9;
                    val2 = atoi(point1);
                    rt = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;
                    }else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 36;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "andi") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    imm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;
                    }
                }
                if(cont==1)
                {
                    opcode = 12;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "or") == 0)
            {
                point = token+1;
                val = atoi(point);
                rd = val;
                if(val>=10){
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;
                }
                else{
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+9;
                    val2 = atoi(point1);
                    rt = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;
                    }else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 37;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "ori") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    imm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;
                    }
                }
                if(cont==1)
                {
                    opcode = 13;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "slt") == 0)
            {
                point = token+1;
                val = atoi(point);
                rd = val;
                if(val>=10){
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;
                }
                else{
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+9;
                    val2 = atoi(point1);
                    rt = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;
                    }else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 42;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "slti") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    imm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;
                    }
                }

                if(cont==1)
                {
                    opcode = 10;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "xor") == 0)
            {
                point = token+1;
                val = atoi(point);
                rd = val;
                if(val>=10){
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;
                }
                else{
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+9;
                    val2 = atoi(point1);
                    rt = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;
                    }else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 38;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "sll") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    hmm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        hmm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        hmm = val1;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 0;
                    instrucao = 0 |(opcode<<26)|(rs<<16)|(rt<<11)|(hmm<<6)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "srl") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    hmm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        hmm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        hmm = val1;
                    }
                }
                if(cont==1)
                {
                    opcode = 0;
                    opcode2 = 2;
                    instrucao = 0 |(opcode<<26)|(rs<<16)|(rt<<11)|(hmm<<6)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "j") == 0)
            {
                point1 = token;
                val = atoi(point1);
                imm = val;
                if(cont==1)
                {
                    opcode = 2;
                    instrucao = 0 |(opcode<<26)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "beq") == 0)
            {
                point = token+1;
                val = atoi(point);
                rs = val;
                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rt = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rt = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    imm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;
                    }
                }
                if(cont==1)
                {
                    opcode = 4;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "bne") == 0)
            {
                point = token+1;
                val = atoi(point);
                rs = val;

                if(val>=10){
                    point = token+5;
                    val2 = atoi(point);
                    rt = val2;
                }
                else{
                    point = token+4;
                    val2 = atoi(point);
                    rt = val2;
                }
                if(val>=10&&val2>=10){
                    point1 = token+8;
                    val1 = atoi(point1);
                    imm = val1;
                }else{
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;
                    }else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;
                    }
                }
                if(cont==1)
                {
                    opcode = 5;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "bgez") == 0)
            {
                point = token+1;
                val = atoi(point);
                rs = val;

                if(val>=10){
                    point = token+4;
                    val2 = atoi(point);
                    imm = val2;
                }
                else{
                    point = token+3;
                    val2 = atoi(point);
                    imm = val2;
                }
                if(cont==1)
                {
                    opcode = 1;
                    opcode2 = 1;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(opcode2<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "bgtz") == 0)
            {
                point = token+1;
                val = atoi(point);
                rs = val;
                if(val>=10){
                    point = token+4;
                    val2 = atoi(point);
                    imm = val2;
                }
                else{
                    point = token+3;
                    val2 = atoi(point);
                    imm = val2;
                }
                if(cont==1)
                {
                    opcode = 7;
                    opcode2 = 0;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(opcode2<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "lb") == 0)
            {

                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;
                }
                else{
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+8;
                    val2 = atoi(point1);
                    rs = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;
                    }else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);
                        rs = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 32;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "sb") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;
                }
                else{
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+8;
                    val2 = atoi(point1);
                    rs = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;
                    }else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);
                        rs = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 40;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "lw") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;
                }
                else{
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+8;
                    val2 = atoi(point1);
                    rs = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;
                    }else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);
                        rs = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 35;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "sw") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;
                }
                else{
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;
                }
                if(val>=10&&val1>=10){
                    point1 = token+8;
                    val2 = atoi(point1);
                    rs = val2;
                }else{
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;
                    }else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);
                        rs = val2;
                    }
                }
                if(cont==1)
                {
                    opcode = 43;
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if (strcmp(arma, "lui") == 0)
            {
                point = token+1;
                val = atoi(point);
                rt = val;
                if(val>=10){
                    point = token+4;
                    val2 = atoi(point);
                    imm = val2;
                }
                else{
                    point = token+3;
                    val2 = atoi(point);
                    imm = val2;
                }
                if(cont==1)
                {
                    opcode = 15;
                    instrucao = 0 |(opcode<<26)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);
                }
            }
            if(strcmp(arma, "syscall")==0)
            {
                opcode = 0;
                opcode2 = 12;
                instrucao = 0 |(opcode<<26)|(opcode2);
                printf("0X%.8X\n",instrucao);
                fwrite(&instrucao, sizeof(int), 1, res);
            }
            if(strcmp(arma, "readb")==0)
            {
                opcode = 60;
                instrucao = 0 |(opcode<<26);
                printf("0X%.8X\n",instrucao);
                fwrite(&instrucao, sizeof(int), 1, res);
            }
            if(strcmp(arma, "writeb")==0)
            {
                opcode = 61;
                instrucao = 0 |(opcode<<26);
                printf("0X%.8X\n",instrucao);
                fwrite(&instrucao, sizeof(int), 1, res);
            }
            cont++;                      /**Contador para ir na posição dos ponteiros movidos*/
            token = strtok(NULL, s);     /**Anda dentro do token*/
        }
    }
    /**Fecha todos os ponteiros e arquivos*/
    fclose(fp);
    fclose(res);
    free(arma);
    free(token);
    free(point);
    free(point1);

    return 0;
}
