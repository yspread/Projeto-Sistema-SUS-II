#include "paciente.h"
#include "avl.h"
#include "fila.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct paciente_
{
    int ID;
    char nome[100];
} PACIENTE;

int get_ID(PACIENTE *paciente) //função para retornar o ID do paciente
{
    if (paciente != NULL)
    {
        return (paciente->ID);
    }
}

char *get_nome_paciente(PACIENTE *paciente) //função para retornar o nome do paciente
{
    if (paciente != NULL)
    {
        return (paciente->nome);
    }
}

bool apagar_paciente(PACIENTE **paciente) //função que deleta o paciente do sistema
{
    if (*paciente != NULL)
    {
        free(*paciente);
        *paciente = NULL;
        return (true);
    }
    return false;
}

PACIENTE* criar_paciente(int id, char *nome, int prioridade) //cria um paciente
{
    PACIENTE *paciente;

    paciente = (PACIENTE*) malloc (sizeof(PACIENTE));
    if (paciente != NULL)
    {
        paciente->ID = id;
        strcpy(paciente->nome, nome);
        return paciente;
    }
    return NULL;
}

void imprimir_paciente(PACIENTE* paciente) //imprime as informaçoes sobre o paciente 
{
    if (paciente != NULL)
    {
        printf("ID: %d\n Nome: %s", paciente->ID, paciente->nome);
    }
    return;
}