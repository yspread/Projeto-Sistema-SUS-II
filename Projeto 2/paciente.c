#include "paciente.h"
#include "avl.h"
#include "fila.h"
#include "historico.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct paciente_
{
    int ID;
    char nome[100];
    HISTORICO* historico;
} PACIENTE;

int get_ID(PACIENTE *paciente) //função para retornar o ID do paciente
{
    if (paciente != NULL)
    {
        return (paciente->ID);
    }
    return -1;
}

char *get_nome_paciente(PACIENTE *paciente) //função para retornar o nome do paciente
{
    if (paciente != NULL)
    {
        return (paciente->nome);
    }
    return NULL;
}

HISTORICO* get_historico(PACIENTE* paciente)//retorna o historico
{
    if(paciente != NULL){
        return paciente->historico;
    }
    return NULL;
}

bool apagar_paciente(PACIENTE **paciente) //função que deleta o paciente do sistema
{
    if (*paciente != NULL)
    {
        apagar_historico(&((*paciente)->historico));
        free(*paciente);
        *paciente = NULL;
        return (true);
    }
    return false;
}

PACIENTE* criar_paciente(int id, char *nome) //cria um paciente
{
    PACIENTE *paciente;

    paciente = (PACIENTE*) malloc (sizeof(PACIENTE));
    if (paciente != NULL)
    {
        paciente->ID = id;
        strcpy(paciente->nome, nome);
        paciente->historico = criar_historico();
        return paciente;
    }
    return NULL;
}

void imprimir_paciente(PACIENTE* paciente) //imprime as informaçoes sobre o paciente 
{
    if (paciente != NULL)
    {
        printf("ID: %d\nNome: %s\n", paciente->ID, paciente->nome);
        printf("\n");
    }
    return;
}

void save_paciente(PACIENTE* paciente, FILE* fptr)//salvar paciente em um arquivo
{
    int tamanhoNome = strlen(paciente->nome);
    fwrite(&tamanhoNome, sizeof(int), 1, fptr); //necessario para quando for dar load
    char* nome = get_nome_paciente(paciente);
    fwrite(nome, sizeof(char), tamanhoNome, fptr);
    int id = get_ID(paciente);
    fwrite(&id, sizeof(int), 1, fptr);
    HISTORICO* historico = get_historico(paciente);
    if (historico != NULL)
    {
        int tamanhoHistorico = get_tamanho_historico(historico);
        fwrite(&tamanhoHistorico, sizeof(int), 1, fptr);
        while(tamanhoHistorico > 0)
        {    
            PROCEDIMENTO *topo = get_topo(historico);
            int tamanhoProcedimento = get_size_procedimento(topo);
            fwrite(&tamanhoProcedimento, sizeof(int), 1, fptr);
            char *nomeProcedimento = get_nome_procedimento(topo);
            fwrite(nomeProcedimento, sizeof(char), tamanhoProcedimento, fptr);
            retirar_procedimento(historico);
            tamanhoHistorico--;
        }
    }
    else //caso o paciente nao tenha um historico
    { 
        int tamanhoHistorico = 0;
        fwrite(&tamanhoHistorico, sizeof(int), 1, fptr);
    }
}

PACIENTE* load_paciente(FILE* fptr)//carregar paciente de um arquivo
{
    int tamanhoNome, id, tamanhoHistorico;
    fread(&tamanhoNome, sizeof(int), 1, fptr);  //necessario ler o tamanho primeiro
    
    char* nome = malloc((tamanhoNome + 1) * sizeof(char));
    fread(nome, sizeof(char), tamanhoNome, fptr);
    nome[tamanhoNome] = '\0';

    fread(&id, sizeof(int), 1, fptr);
    PACIENTE* paciente = criar_paciente(id, nome);

    free(nome);
    nome = NULL;

    fread(&tamanhoHistorico, sizeof(int), 1, fptr);
    //como o historico foi salvo sendo desempilhado, se ele for lido na ordem ele vai estar na ordem reversa
    //por isso salvo o historico em um vetor e depois empilho ele de tras pra frente do vetor
    PROCEDIMENTO *procedimentos[tamanhoHistorico]; 
    for (int i = 0; i < tamanhoHistorico; i++)
    {
        int tamanhoProcedimento;
        fread(&tamanhoProcedimento, sizeof(int), 1, fptr);

        char *nomeProcedimento;
        nomeProcedimento = malloc((tamanhoProcedimento + 1) * sizeof(char));
        fread(nomeProcedimento, sizeof(char), tamanhoProcedimento, fptr);
        nomeProcedimento[tamanhoProcedimento] = '\0';

        procedimentos[i] = criar_procedimento(nomeProcedimento);
        free(nomeProcedimento);
        nomeProcedimento = NULL;
    }
    for (int i = tamanhoHistorico - 1; i >= 0 ; i--) //empilhando os procedimentos
    {
        inserir_procedimento(get_historico(paciente), procedimentos[i]);
    }
    return paciente;
}