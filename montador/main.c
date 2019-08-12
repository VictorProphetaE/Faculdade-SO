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

Nota:GCC compiler and GDB debugger from TDM-GCC (version 4.7.1, 32 bit)

Nome: Victor Propheta Erbano
RGM: 021052
Matéria: Sistemas Operacionais
Prof: Fabrício Sérgio de Paula
Data de Criação: 29/03/2016
Data Modificação: 06/05/2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main()
{
    /**Parte de criação de variaves*/
    FILE *fp; /**Criação dos ponteiros para os arquivos*/
    FILE *res;
    char buff[250]; /**Buffer para receber a linha do arquivo*/
    const char s[8] =  " ,()\n";    /**Caracteres constantes para se usar nos tokens*/
    char *token,*point,*point1,*arma,stren[30],strsa[30],str[10];   /**Criação de ponteiros*/
    int val=0,val1=0,val2=0,cont=0; /**Criação de valores para ser convertidos*/
    int16_t imm=0;  /**Inteiro com 16 bits*/
    uint32_t instrucao; /**Instrução com 32 bits de casa*/
    short rs=0,rt=0,opcode=0,rd=0,opcode2=0;    /**Criação dos rts e opcodes*/
    int hmm=0;  /**Criação do hmm ou rh*/
    printf("Nome do arquivo de entrada mais: \n");
    gets(stren);
    strcpy(str,stren);
    strcat(stren,".mips");
    strcpy(strsa,str);
    strcat(strsa,".bin");
    fp = fopen(stren,"r");
    if (fp == NULL)     /**Verifica se o arquivo está vazio*/
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
        exit(1);
    }
    res = fopen(strsa,"wb+");     /**Criando e escrevendo um arquivo teste.bin*/
    if (res == NULL)     /**Verifica se o arquivo está vazio*/
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
        exit(1);
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
                if(val>=10)                 /**Verifica se o valor é maior que 10*/
                {
                    point = token+5;        /**pega o valor na posição +5*/
                    val1 = atoi(point);
                    rs = val1;              /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;            /**Pega o valor na posição +4*/
                    val1 = atoi(point);
                    rs = val1;              /**Guarda o valor em rs*/
                }
                if(val>=10&&val1>=10)          /**Verifica se o valor e o valor 1 é maior que 10*/
                {
                    point1 = token+9;           /**Pega o valor na posição +9*/
                    val2 = atoi(point1);
                    rt = val2;              /**Guarda o valor em rt*/
                }
                else
                {
                    if(val1>=10||val>=10)       /**Verifica se o valor ou o valor 1 é maior que 10*/
                    {
                        point1 = token+8;       /**Pega o valor na posição +8*/
                        val2 = atoi(point1);
                        rt = val2;
                    }
                    else
                    {
                        point1 = token+7;       /**Pega o valor na posição +7*/
                        val2 = atoi(point1);
                        rt = val2;
                    }
                }
                if(cont==1)                     /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                 /**Primeiro dos valores do opcode*/
                    opcode2 = 32;               /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);/**Converte bit a bit os valroes e os opcodes*/
                    printf("0X%.8X\n",instrucao);           /**Imprime na tela o resultado*/
                    fwrite(&instrucao, sizeof(int), 1, res);    /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "addi") == 0)      /**compara arma com addi */
            {
                point = token+1;                /**ponteiro recebe o valor de token +1*/
                val = atoi(point);              /**transformação de char para int*/
                rt = val;                       /**rt recebe o valor de já transformado*/
                if(val>=10)                         /**Verifica se o valor é maior que 10*/
                {
                    point = token+5;                /**Pega o valor na posição +5*/
                    val2 = atoi(point);             /**transformação de char para int*/
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;                /**Pega o valor na posição +4*/
                    val2 = atoi(point);             /**transformação de char para int*/
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val2>=10)               /**Verifica se o valor e o valor 1 é maior que 10*/
                {
                    point1 = token+8;               /**Pega o valor na posição +8*/
                    val1 = atoi(point1);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    if(val2>=10||val>=10)           /**Verifica se o valor ou o valor 1 é maior que 10*/
                    {
                        point1 = token+7;           /**Pega o valor na posição +7*/
                        val1 = atoi(point1);
                        imm = val1;
                    }
                    else
                    {
                        point1 = token+6;           /**Pega o valor na posição +6*/
                        val1 = atoi(point1);
                        imm = val1;
                    }
                }
                if(cont==1)                             /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 8;                         /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF); /**Converte bit a bit os valroes e os opcodes*/
                    printf("0X%.8X\n",instrucao);           /**Imprime na tela o resultado*/
                    fwrite(&instrucao, sizeof(int), 1, res);    /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "sub") == 0)           /**compara arma com sub*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rd = val;                           /**Guarda o valor em rd*/
                if(val>=10)
                {
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+9;
                    val2 = atoi(point1);
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                    else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 34;                   /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "mult") == 0)          /**compara arma com mult*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rs = val;                           /**Guarda o valor em rs*/
                if(val>=10)
                {
                    point = token+5;
                    val1 = atoi(point);
                    rt = val1;                      /**Guarda o valor em rt*/
                }
                else
                {
                    point = token+4;
                    val1 = atoi(point);
                    rt = val1;                      /**Guarda o valor em rt*/
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 24;                   /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);            /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "div") == 0)           /**compara arma com div*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rs = val;                           /**Guarda o valor em rs*/
                if(val>=10)
                {
                    point = token+5;
                    val1 = atoi(point);
                    rt = val1;                      /**Guarda o valor em rt*/
                }
                else
                {
                    point = token+4;
                    val1 = atoi(point);
                    rt = val1;                      /**Guarda o valor em rt*/
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 26;                   /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "and") == 0)           /**compara arma com and*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rd = val;                           /**Guarda o valor em rd*/
                if(val>=10)
                {
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }

                if(val>=10&&val1>=10)
                {
                    point1 = token+9;
                    val2 = atoi(point1);            /**transformação de char para int*/
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                    else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 36;                   /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "andi") == 0)          /**compara arma com andi*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val2 = atoi(point);             /**transformação de char para int*/
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val2>=10)
                {
                    point1 = token+8;
                    val1 = atoi(point1);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);        /**transformação de char para int*/
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                    else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 12;                    /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "or") == 0)            /**compara arma com or*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rd = val;                           /**Guarda o valor em rd*/
                if(val>=10)
                {
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+9;
                    val2 = atoi(point1);
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                    else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 37;                   /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "ori") == 0)           /**compara arma com ori*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val2>=10)
                {
                    point1 = token+8;
                    val1 = atoi(point1);            /**transformação de char para int*/
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                    else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 13;                    /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "slt") == 0)           /**compara arma com slt*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rd = val;                           /**Guarda o valor em rd*/
                if(val>=10)
                {
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+9;
                    val2 = atoi(point1);            /**transformação de char para int*/
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                    else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 42;                   /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "slti") == 0)          /**compara arma com slti*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val2>=10)
                {
                    point1 = token+8;
                    val1 = atoi(point1);            /**transformação de char para int*/
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                    else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);        /**transformação de char para int*/
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                }

                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 10;                    /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "xor") == 0)           /**compara arma com xor*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rd = val;                           /**Guarda o valor em rd*/
                if(val>=10)
                {
                    point = token+5;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val1 = atoi(point);
                    rs = val1;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+9;
                    val2 = atoi(point1);            /**transformação de char para int*/
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+8;
                        val2 = atoi(point1);
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                    else
                    {
                        point1 = token+7;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rt = val2;                  /**Guarda o valor em rt*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 38;                   /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(rd<<11)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "sll") == 0)           /**compara arma com sll*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val2>=10)
                {
                    point1 = token+8;
                    val1 = atoi(point1);            /**transformação de char para int*/
                    hmm = val1;                     /**Guarda o valor em hmm*/
                }
                else
                {
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        hmm = val1;                 /**Guarda o valor em hmm*/
                    }
                    else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);        /**transformação de char para int*/
                        hmm = val1;                 /**Guarda o valor em hmm*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 0;                    /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<16)|(rt<<11)|(hmm<<6)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "srl") == 0)           /**compara arma com srl*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+5;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    point = token+4;
                    val2 = atoi(point);
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                if(val>=10&&val2>=10)
                {
                    point1 = token+8;
                    val1 = atoi(point1);            /**transformação de char para int*/
                    hmm = val1;                     /**Guarda o valor em hmm*/
                }
                else
                {
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        hmm = val1;                 /**Guarda o valor em hmm*/
                    }
                    else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);        /**transformação de char para int*/
                        hmm = val1;                 /**Guarda o valor em hmm*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 0;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 2;                    /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<16)|(rt<<11)|(hmm<<6)|(opcode2);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "j") == 0)             /**compara arma com j*/
            {
                point1 = token;
                val = atoi(point1);                 /**transformação de char para int*/
                imm = val;                          /**Guarda o valor em imm*/
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 2;                     /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "beq") == 0)           /**compara arma com beq*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rs = val;                           /**Guarda o valor em rs*/
                if(val>=10)
                {
                    point = token+5;
                    val2 = atoi(point);
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                else
                {
                    point = token+4;
                    val2 = atoi(point);
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                if(val>=10&&val2>=10)
                {
                    point1 = token+8;
                    val1 = atoi(point1);            /**transformação de char para int*/
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                    else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);        /**transformação de char para int*/
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 4;                     /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "bne") == 0)           /**compara arma com bne*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rs = val;                           /**Guarda o valor em rs*/
                if(val>=10)
                {
                    point = token+5;
                    val2 = atoi(point);
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                else
                {
                    point = token+4;
                    val2 = atoi(point);
                    rt = val2;                      /**Guarda o valor em rt*/
                }
                if(val>=10&&val2>=10)
                {
                    point1 = token+8;
                    val1 = atoi(point1);            /**transformação de char para int*/
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    if(val2>=10||val>=10)
                    {
                        point1 = token+7;
                        val1 = atoi(point1);
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                    else
                    {
                        point1 = token+6;
                        val1 = atoi(point1);        /**transformação de char para int*/
                        imm = val1;                 /**Guarda o valor em imm*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 5;                     /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "bgez") == 0)          /**compara arma com bgez*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rs = val;                           /**Guarda o valor em rs*/

                if(val>=10)
                {
                    point = token+4;
                    val2 = atoi(point);
                    imm = val2;                     /**Guarda o valor em imm*/
                }
                else
                {
                    point = token+3;
                    val2 = atoi(point);             /**transformação de char para int*/
                    imm = val2;                     /**Guarda o valor em imm*/
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 1;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 1;                    /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(opcode2<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "bgtz") == 0)          /**compara arma com bgtz*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rs = val;                           /**Guarda o valor em rs*/
                if(val>=10)
                {
                    point = token+4;
                    val2 = atoi(point);
                    imm = val2;                     /**Guarda o valor em imm*/
                }
                else
                {
                    point = token+3;
                    val2 = atoi(point);             /**transformação de char para int*/
                    imm = val2;                     /**Guarda o valor em imm*/
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 7;                     /**Primeiro dos valores do opcode*/
                    opcode2 = 0;                    /**Segundo valor do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(opcode2<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "lb") == 0)            /**compara arma com lb*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+8;
                    val2 = atoi(point1);            /**transformação de char para int*/
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                    else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 32;                    /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "sb") == 0)            /**compara arma com sb*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+8;
                    val2 = atoi(point1);            /**transformação de char para int*/
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                    else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 40;                    /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "lw") == 0)            /**compara arma com lw*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+8;
                    val2 = atoi(point1);            /**transformação de char para int*/
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                    else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 35;                    /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "sw") == 0)            /**compara arma com sw*/
            {
                point = token+1;                    /**ponteiro recebe o valor de token +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)
                {
                    point = token+4;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                else
                {
                    point = token+3;
                    val1 = atoi(point);
                    imm = val1;                     /**Guarda o valor em imm*/
                }
                if(val>=10&&val1>=10)
                {
                    point1 = token+8;
                    val2 = atoi(point1);            /**transformação de char para int*/
                    rs = val2;                      /**Guarda o valor em rs*/
                }
                else
                {
                    if(val1>=10||val>=10)
                    {
                        point1 = token+7;
                        val2 = atoi(point1);
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                    else
                    {
                        point1 = token+6;
                        val2 = atoi(point1);        /**transformação de char para int*/
                        rs = val2;                  /**Guarda o valor em rs*/
                    }
                }
                if(cont==1)                         /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 43;                    /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rs<<21)|(rt<<16)|(imm&0xFFFF);
                    printf("0X%.8X\n",instrucao);
                    fwrite(&instrucao, sizeof(int), 1, res);        /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if (strcmp(arma, "lui") == 0)           /**compara arma com lui*/
            {
                point = token+1;                    /**Pega o valor na posição +1*/
                val = atoi(point);                  /**transformação de char para int*/
                rt = val;                           /**Guarda o valor em rt*/
                if(val>=10)                         /**Verifica se o valor é maior que 10*/
                {
                    point = token+4;                /**Pega o valor na posição +4*/
                    val2 = atoi(point);
                    imm = val2;                     /**Guarda o valor em imm*/
                }
                else
                {
                    point = token+3;                /**Pega o valor na posição +3*/
                    val2 = atoi(point);
                    imm = val2;                     /**Guarda o valor em imm*/
                }
                if(cont==1)                                 /**Verifica se o contador é 1 para entrar dentro da condição e gravar*/
                {
                    opcode = 15;                            /**Primeiro dos valores do opcode*/
                    instrucao = 0 |(opcode<<26)|(rt<<16)|(imm&0xFFFF);  /**Converte bit a bit os valroes e os opcodes*/
                    printf("0X%.8X\n",instrucao);           /**Imprime na tela o resultado*/
                    fwrite(&instrucao, sizeof(int), 1, res);    /**Pega o resultado e escreve dentro do arquivo .bin*/
                }
            }
            if(strcmp(arma, "syscall")==0)          /**compara arma com syscall*/
            {
                opcode = 0;                             /**Primeiro dos valores do opcode*/
                opcode2 = 12;                           /**Pega o segundo valor do opcode*/
                instrucao = 0 |(opcode<<26)|(opcode2);  /**Converte bit a bit os valroes e os opcodes*/
                printf("0X%.8X\n",instrucao);           /**Imprime na tela o resultado*/
                fwrite(&instrucao, sizeof(int), 1, res);    /**Pega o resultado e escreve dentro do arquivo .bin*/
            }
            if(strcmp(arma, "readb")==0)            /**compara arma com readb*/
            {
                opcode = 60;                        /**Primeiro dos valores do opcode*/
                instrucao = 0 |(opcode<<26);        /**Converte bit a bit os valroes e os opcodes*/
                printf("0X%.8X\n",instrucao);       /**Imprime na tela o resultado*/
                fwrite(&instrucao, sizeof(int), 1, res);    /**Pega o resultado e escreve dentro do arquivo .bin*/
            }
            if(strcmp(arma, "writeb")==0)           /**compara arma com writeb*/
            {
                opcode = 61;                        /**Primeiro dos valores do opcode*/
                instrucao = 0 |(opcode<<26);        /**Converte bit a bit os valroes e os opcodes*/
                printf("0X%.8X\n",instrucao);       /**Imprime na tela o resultado*/
                fwrite(&instrucao, sizeof(int), 1, res);    /**Pega o resultado e escreve dentro do arquivo .bin*/
            }
            cont++;                      /**Contador para ir na posição dos ponteiros movidos*/
            token = strtok(NULL, s);     /**Anda dentro do token*/
        }
    }

    /**Fecha todos os ponteiros de arquivos*/
    fclose(fp);
    fclose(res);
    /**Libera o ponteiro usado*/
    free(token);

    return 0;
}
