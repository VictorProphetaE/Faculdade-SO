/**
Descrição:Le um arquivo .bin e gera um arquivo .sim.out na leitura .bin
ele pega as instruções e executa a informação contida nela, no sim.out
ele pega os registradores + ir, pc, base,limit da memoria e o mode

Nota:GCC compiler and GDB debugger from TDM-GCC (version 4.7.1, 32 bit)

Nome: Victor Propheta Erbano
RGM: 021052
Matéria: Sistemas Operacionais
Prof: Fabrício Sérgio de Paula
Data de Criação: 03/05/2016
Data Modificação: 22/05/2016
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

/**Variavel da memoria 2^20*/
uint8_t MEMORY[1<<20];

/**Estrutura dos registradores a ser usado*/
struct s_regs
{
    int32_t r[16];
    uint32_t ir;
    uint32_t pc;
    uint32_t base;
    uint32_t limit;
    uint8_t mode;
};

int main()
{
    /**Criação das variaveis a ser usado*/
    struct s_regs registrador;
    FILE *fp;
    FILE *res;
    char stren[30],strsa[30],str[10];
    uint32_t instrucao,opcode,opcode2;
    uint32_t soma_tudo,target,mode1;
    short rs,rt,rd,funct,sham,rh;
    int16_t imm;
    int i,cont2,mov=0;

    /**Zera todos as variaveis, mais a memoria, mais os registradores*/
    memset(&cont2, 0, sizeof cont2);
    for(i=0; i<1<<20; i++)
    {
        cont2++;
        memset(&MEMORY[i], 0, sizeof (uint8_t));
    }
    memset(&instrucao, 0, sizeof instrucao);
    memset(&opcode, 0, sizeof opcode);
    memset(&opcode2, 0, sizeof opcode2);
    memset(&soma_tudo, 0, sizeof soma_tudo);
    memset(&rs, 0, sizeof rs);
    memset(&rt, 0, sizeof rt);
    memset(&rd, 0, sizeof rd);
    memset(&rh, 0, sizeof rh);
    memset(&imm, 0, sizeof imm);
    memset(&funct, 0, sizeof funct);
    memset(&sham, 0, sizeof sham);
    memset(&target, 0, sizeof target);
    memset(&registrador.base, 0, sizeof registrador.base);
    memset(&registrador.ir, 0, sizeof registrador.ir);
    memset(&registrador.mode, 0, sizeof registrador.mode);
    memset(&registrador.pc, 0, sizeof registrador.pc);
    for(i=0; i<16; i++)
        memset(&registrador.r[i], 0, sizeof registrador.r[i]);

    registrador.limit = cont2-1;

    /**Le o nome do arquivo copia para o str concatena com o .bin e concatena
    com .sim.out do arquvio de saida*/
    printf("Nome do arquivo de entrada mais: \n");
    scanf("%s",stren);
    strcpy(str,stren);
    strcat(stren,".bin");
    strcpy(strsa,str);
    strcat(strsa,".sim.out");
    fp = fopen(stren,"r");
    if (fp == NULL)
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
        exit(1);
    }
    res = fopen(strsa,"wb");
    if (res == NULL)
    {
        printf("Nao existe nenhum dado a ser lido ou o arquivo reportou um erro!\n");
        exit(1);
    }
    while(!feof(fp))
    {
        /**Le o arquivo guardando as variaveis na memoria de 1MB utilizando o registrador contador*/
        fread(&MEMORY[registrador.pc], sizeof(uint32_t), 1, fp);
        registrador.pc += 4;
    }
    /**Laço da execução de dados a partir do registrador.pc 0 com os valores já guardados na memoria
       no registrador de instruções, em seguida separa o opcode, a funct e a sham*/
    registrador.pc =0;
    do{
        registrador.ir = (MEMORY[registrador.pc+3]<<24)|(MEMORY[registrador.pc+2]<<16)|(MEMORY[registrador.pc+1]<<8)|(MEMORY[registrador.pc]);
        opcode = (registrador.ir>>26);
        opcode2 = (registrador.ir&0X7F);
        funct = (registrador.ir&0X3F);
        sham = (registrador.ir>>6&0X1F);

        /**Laço do opcode*/
        switch(opcode)
        {
        case 0X3D:
            registrador.pc += 4;

            break;
        case 0X3C:
            registrador.pc += 4;

            break;
        case 0X2B:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            for(i=0;i<=3;i++)
            {
                MEMORY[registrador.r[rs] + imm + i] = (registrador.r[rt]>>mov);
                mov+=8;
            }
            registrador.pc += 4;

            break;
        case 0X28:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            for(i=0;i<=3;i++)
            {
                MEMORY[registrador.r[rs] + imm + i] = (0xff & registrador.r[rt]>>mov);
                mov+=8;
            }
            registrador.pc += 4;

            break;
        case 0X23:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            registrador.r[rt] = (MEMORY[registrador.r[rs] + imm+3]<<24)|(MEMORY[registrador.r[rs] + imm+2]<<16)|(MEMORY[registrador.r[rs] + imm+1]<<8)|(MEMORY[registrador.r[rs] + imm]);
            registrador.pc += 4;

            break;
        case 0X20:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            registrador.r[rt] = (MEMORY[registrador.r[rs] + imm+3]<<24)|(MEMORY[registrador.r[rs] + imm+2]<<16)|(MEMORY[registrador.r[rs] + imm+1]<<8)|(MEMORY[registrador.r[rs] + imm]);
            registrador.pc += 4;

            break;
        case 0XF:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            registrador.r[rt] = (imm << 16);
            registrador.pc += 4;

            break;
        case 0XC:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            registrador.r[rt]= registrador.r[rs]&imm;
            registrador.pc += 4;

            break;
        case 0XD:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            registrador.r[rt]= registrador.r[rs]|imm;
            registrador.pc += 4;

            break;
        case 0XA:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            if(registrador.r[rs]<imm)
            {
                registrador.r[rt] = 1;
                registrador.pc += 4;
            }
            else
            {
                registrador.r[rt] = 0;
                registrador.pc += 4;
            }

            break;
        case 0X8:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            registrador.r[rt]= registrador.r[rs]+imm;
            registrador.pc += 4;

            break;
        case 0X7:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            if(registrador.r[rs]> 0)
            {
                registrador.pc += (imm<<2);
            }
            else
            {
                registrador.pc += 4;
            }

            break;
        case 0X5:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            if(registrador.r[rs]!=registrador.r[rt])
            {
                registrador.pc += (imm<<2);
            }
            else
            {
                registrador.pc += 4;
            }

            break;
        case 0X4:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            if(registrador.r[rs]==registrador.r[rt])
            {
                registrador.pc += (imm<<2);
            }
            else
            {
                registrador.pc += 4;
            }

            break;
        case 0X2:
            target = (registrador.ir&0X3FFFFFF);
            registrador.pc = (registrador.pc & 0xf0000000) | (target << 2);
            registrador.ir = registrador.ir;

            break;
        case 0X1:
            imm = (registrador.ir&0XFFFF);
            rt = (registrador.ir>>16&0X1F);
            rs = (registrador.ir>>21&0X1F);
            switch(rt)
            {
            case 0X1:
                if(registrador.r[rs]>= 0)
                {
                    registrador.pc += (imm<<2);
                }
                else
                {
                    registrador.pc += 4;
                }
                break;
            }
            break;
        case 0X0:
            switch(funct)
            {
            case 0X00:
                if(sham!= 0)
                {
                    rh = (registrador.ir>>6&0X1F);
                    rd = (registrador.ir>>11&0X1F);
                    rt = (registrador.ir>>16&0X1F);
                    registrador.r[rd] = registrador.r[rt] << rh;
                    registrador.pc += 4;
                }

                break;
            case 0X02:
                rh = (registrador.ir>>6&0X1F);
                rd = (registrador.ir>>11&0X1F);
                rt = (registrador.ir>>16&0X1F);
                registrador.r[rd] = registrador.r[rt] >> rh;
                registrador.pc += 4;

                break;
                if(sham==0)
                {
                case 0X18:
                    rt = (registrador.ir>>16&0X1F);
                    rs = (registrador.ir>>21&0X1F);
                    registrador.r[10] = registrador.r[rs]*registrador.r[rt];
                    registrador.pc += 4;

                    break;
                case 0X1A:
                    rt = (registrador.ir>>16&0X1F);
                    rs = (registrador.ir>>21&0X1F);
                    registrador.r[10] = registrador.r[rs]/registrador.r[rt];
                    registrador.r[11] = registrador.r[rs]%registrador.r[rt];
                    registrador.pc += 4;

                    break;
                }
            case 0X20:
                rd = (registrador.ir>>11&0X1F);
                rt = (registrador.ir>>16&0X1F);
                rs = (registrador.ir>>21&0X1F);
                registrador.r[rd]= registrador.r[rs]+registrador.r[rt];
                registrador.pc += 4;

                break;
            case 0X22:
                rd = (registrador.ir>>11&0X1F);
                rt = (registrador.ir>>16&0X1F);
                rs = (registrador.ir>>21&0X1F);
                registrador.r[rd]= registrador.r[rs]-registrador.r[rt];
                registrador.pc += 4;

                break;
            case 0X24:
                rd = (registrador.ir>>11&0X1F);
                rt = (registrador.ir>>16&0X1F);
                rs = (registrador.ir>>21&0X1F);
                registrador.r[rd]= registrador.r[rs]&registrador.r[rt];
                registrador.pc += 4;

                break;
            case 0X25:
                rd = (registrador.ir>>11&0X1F);
                rt = (registrador.ir>>16&0X1F);
                rs = (registrador.ir>>21&0X1F);
                registrador.r[rd]= registrador.r[rs]|registrador.r[rt];
                registrador.pc += 4;

                break;
            case 0X26:
                rd = (registrador.ir>>11&0X1F);
                rt = (registrador.ir>>16&0X1F);
                rs = (registrador.ir>>21&0X1F);
                registrador.r[rd]= registrador.r[rs]^registrador.r[rt];
                registrador.pc += 4;

                break;
            case 0X2A:
                rd = (registrador.ir>>11&0X1F);
                rt = (registrador.ir>>16&0X1F);
                rs = (registrador.ir>>21&0X1F);
                if(registrador.r[rs]<registrador.r[rt])
                {
                    registrador.r[rd] = 1;
                    registrador.pc += 4;
                }
                else
                {
                    registrador.r[rd] = 0;
                    registrador.pc += 4;
                }

                break;
            case 0XC:
                registrador.pc += 4;

                break;
            }
        }
    }while(registrador.ir!=0);

    memset(&registrador.ir, 0, sizeof registrador.ir);
    memset(&mode1, 0, sizeof registrador.ir);
    mode1 = registrador.mode;
    soma_tudo= 0;
    for(i=0; i<1<<20; i+=4)
    {
        registrador.ir = (MEMORY[i+3]<<24)|(MEMORY[i+2]<<16)|(MEMORY[i+1]<<8)|(MEMORY[i]);
        soma_tudo+=registrador.ir;
    }
    /**Grava o resultado dos registradores no arquivo juntamente com
    o registrador de instruções que foi zerado, o contador que foi mantido
    ,a base que não foi mexido, o limit da memoria que 2^20-1, o mode que
    era 8bit e foi transformado em 32bit, juntamente com a soma de todas
    as instruções*/
    for(i=0; i<16; i++)
        fwrite(&registrador.r[i], sizeof(int32_t), 1, res);
    fwrite(&registrador.ir, sizeof(uint32_t), 1, res);
    fwrite(&registrador.pc, sizeof(uint32_t), 1, res);
    fwrite(&registrador.base, sizeof(uint32_t), 1, res);
    fwrite(&registrador.limit, sizeof(uint32_t), 1, res);
    fwrite(&mode1, sizeof(uint32_t), 1, res);
    fwrite(&soma_tudo, sizeof(uint32_t), 1, res);

    /**fecha os arquivos*/
    fclose(fp);
    fclose(res);
    return 0;
}
