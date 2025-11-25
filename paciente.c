#include "paciente.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//EM COMPARAÇÃO COM O PROJETO 1, AGORA O PACIENTE NAO TEM MAIS O HISTORICO
//ELE TEM UM INTEIRO Q INDICA O NIVEL DE PRIORIDADE

typedef struct paciente_
{
    int ID;
    char nome[100];
    int tamanhoNome;
    int prioridade; //inteiro q indica o nivel de prioridade
}PACIENTE;

int get_prioridade(PACIENTE *paciente)
{
    return (paciente->prioridade);
}

int get_ID(PACIENTE *paciente) //função para retornar o ID do paciente
{
    return (paciente->ID);
}

char *get_nome_paciente(PACIENTE *paciente) //função para retornar o nome do paciente
{
    return (paciente->nome);
}

int get_tamanho_nome_paciente(PACIENTE *paciente) //retorna o tamanho do nome do paciente
{
    return (paciente->tamanhoNome);
}

bool apagar_paciente(PACIENTE **paciente)
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
        paciente->tamanhoNome = strlen(nome);
        paciente->prioridade = prioridade;
        return paciente;
    }
    return NULL;
}