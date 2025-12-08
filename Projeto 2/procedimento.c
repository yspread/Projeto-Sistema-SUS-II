#include "paciente.h"
#include "fila.h"
#include "historico.h"
#include "avl.h"
#include "procedimento.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_CHARS 100 //quantidade maxima de caracteres no procedimento

typedef struct procedimento_
{
    char* nome;
    int size;
}PROCEDIMENTO;

PROCEDIMENTO* criar_procedimento(char* str)
{
    if(str == NULL) return NULL;
    
    PROCEDIMENTO* aux = malloc(sizeof(PROCEDIMENTO));
    if(aux == NULL) return NULL;
    
    aux->nome = malloc((strlen(str) + 1) * sizeof(char));
    if(aux->nome == NULL) {
        free(aux);
        return NULL;
    }
    
    strcpy(aux->nome, str);
    aux->size = strlen(str);
    return aux;
}

void apagar_procedimento(PROCEDIMENTO** p)
{
    free((*p)->nome);
    (*p)->nome = NULL;

    free(*p);
    *p = NULL;
}

void print_procedimento(PROCEDIMENTO* p)
{
    printf("%s\n", p->nome);
}

char* get_nome_procedimento(PROCEDIMENTO* p)//funcao para acessar o nome do procedimento
{
    if (p != NULL) {
        return p->nome;
    }
    return NULL;
}

int get_size_procedimento(PROCEDIMENTO *p) //acessar o tamanho do procedimeto
{
    if(p != NULL){
        return(p->size);
    }
    return -1;
}

bool procedimento_cheio(PROCEDIMENTO* p)
{
    return p->size >= MAX_CHARS;
}

