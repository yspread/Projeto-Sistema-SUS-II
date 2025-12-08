#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "historico.h"
#include "procedimento.h"
#define MAX_PROCEDIMENTOS 10 //quantidade maxima de procedimentos no historico

typedef struct no_ NO_HIST;

struct no_
{
    //no para a implementacao da pilha encadeada
    PROCEDIMENTO* procedimento;
    NO_HIST* anterior;
};


typedef struct historico_
{
    int ContadorProcedimentos; //contador para ver se a quantidade de procedimentos do historico estourou o limite (10)
    NO_HIST* topo;
}HISTORICO;

HISTORICO* criar_historico() //aloca memoria para o historico
{
    HISTORICO* historico = malloc(sizeof(HISTORICO));
    if(historico != NULL){
        historico->topo = NULL;
        historico->ContadorProcedimentos = 0;
        return historico;
    }
    return NULL;
}

void apagar_historico(HISTORICO** historico) //apaga o historico (para quando for apagar o paciente)
{
    if((*historico) != NULL && (!historico_vazio(*historico))){
        while((*historico)->topo != NULL){
            retirar_procedimento(*historico);
        }
    }
    free(*historico);
    *historico = NULL;
}

void print_historico(HISTORICO* historico)
{
    NO_HIST* p = historico->topo;
    if(p == NULL){
        printf("Histórico vazio\n");
        return;
    }
    while(p != NULL){
        print_procedimento(p->procedimento);
        p = p->anterior;
    }
}

bool inserir_procedimento(HISTORICO* historico, PROCEDIMENTO* procedimento) //empilhar
{
    if(historico == NULL || procedimento == NULL)return false;
    if(!historico_cheio(historico) && !procedimento_cheio(procedimento)){
        NO_HIST* p = malloc(sizeof(NO_HIST));
        if(p != NULL){
            p->procedimento = procedimento;
            p->anterior = historico->topo;
            historico->topo = p;
            historico->ContadorProcedimentos++;
            return true;
        }
    }
    return false;
}

bool historico_cheio(HISTORICO* historico)
{
    return historico->ContadorProcedimentos >= MAX_PROCEDIMENTOS;
}

bool retirar_procedimento(HISTORICO* historico) //desempilhar
{
    if(historico != NULL && !historico_vazio(historico)){
        NO_HIST* p = historico->topo;
        PROCEDIMENTO* procedimento = p->procedimento;

        historico->topo = historico->topo->anterior;

        historico->ContadorProcedimentos--;

        apagar_procedimento(&procedimento);
        p->anterior = NULL;
        free(p);
        p = NULL;

        return true;
    }
    return false;
}

bool historico_vazio(HISTORICO* historico)
{
    if(historico != NULL){
        return ((historico->ContadorProcedimentos) == 0);
    }
    return false;
}

PROCEDIMENTO *get_topo(HISTORICO *historico)
{
    if(historico != NULL && historico->topo != NULL) {
        return (historico->topo->procedimento);
    }
    return NULL;
}

int get_tamanho_historico(HISTORICO* historico)
{
    return (historico->ContadorProcedimentos);
}