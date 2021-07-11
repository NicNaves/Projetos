#include "imm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main(int argc, char *argv[])
{

    if (strcmp(argv[1], "-open") == 0)
    {
        if ((openImage(argv[2])) == SUCCESS)
        {
            printf("Aberto com sucesso!\n");
        }
        else
        {
            printf("Problema ao abrir / Arquivo Inválido\n");
        }
    }
    else if (strcmp(argv[1], "-convert") == 0)
    {
        if (convertTXTIMM(argv[2], argv[3]) == SUCCESS)
            printf("Convertido com sucesso!\n");
        else
            printf("Erro ao tentar converter! / Arquivo Inválido\n");
    }
    else if (strcmp(argv[1], "-segment") == 0)
    {
        if (segmentIMAGE(atoi(argv[2]), argv[3], argv[4]) == SUCCESS)
            printf("Segmentada com sucesso!\n");
        else
            printf("Erro na segmentação! / Arquivo Inválido\n");
    }

    else if (strcmp(argv[1], "-cc") == 0)
    {
        if (compCONEXO(argv[2], argv[3]) == SUCCESS)
            printf("Diferenciação de objetos feita com sucesso!\n");
        else
            printf("Erro ao diferenciar objetos! /  Arquivo Inválido\n");
    }
    else if (strcmp(argv[1], "-lab") == 0)
    {
        if (LABIRINTO(argv[2], argv[3]) == MAP_SEM_SAIDA)
            printf("Labirinto sem saída!\n");
        if(LABIRINTO(argv[2], argv[3]) == SUCCESS)
            printf("Labirinto Resolvido! \n");
        else
            printf("Arquivo Inválido! \n");
    }
    else
    {
        system("clear");
        printf("Comando não encontrado! \n");
    }

    return 0;
}
