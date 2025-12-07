#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "paciente.h"

#define TAM 250
#define max(a, b) ((a > b) ? a : b)

typedef struct no_{
    int id, urgencia;
    long long int chegada;
}NO;

typedef struct pq_{
    int fim;
    long long int ultima_chegada;
    NO* tree[TAM];
}PQ;

PQ* criar_pq()
{
    PQ* aux = malloc(sizeof(PQ));
    if(aux != NULL){
        aux->fim = -1;
        aux->ultima_chegada = 0;
        for(int i = 0; i < TAM; i++){
            aux->tree[i] = malloc(sizeof(NO));
            if(aux->tree[i] != NULL)aux->tree[i]->urgencia = 6;//a urgencia 6 irá sinalizar que o nó está vazio
        }
    }
    return aux;
}

void pq_apagar(PQ** pq)
{
    for(int i = 0; i < TAM; i++){
        free((*pq)->tree[i]);
        (*pq)->tree[i] = NULL;
    }
    free(*pq);
    *pq = NULL;
}

bool pq_cheia(PQ* pq)
{
    return pq->fim == TAM - 1;
}

bool pq_vazia(PQ* pq)
{
    return pq->fim == -1;
}

int maior_filho(PQ* pq, int a)
{
    int e = a*2 + 1, d = a*2 + 2;
    if(pq->tree[e]->urgencia > pq->tree[d]->urgencia)return e;
    else if(pq->tree[e]->urgencia < pq->tree[d]->urgencia)return d;
    else{//a ordem de chegada será critério de desempate
        if(pq->tree[e]->chegada > pq->tree[d]->chegada)return e;
        else return d;
    }
}

void pq_swap(PQ* pq, int a, int b)
{
    NO* aux = pq->tree[a];
    pq->tree[a] = pq->tree[b];
    pq->tree[b] = aux;
}

void pq_fix_up(PQ* pq)
{
    int cur = pq->fim;
    int pai = (cur - 1)/2;
    while(cur > 0){
        //a ordem de chegada é critério de desempate
        if(pq->tree[cur]->urgencia > pq->tree[pai]->urgencia)break;
        if(pq->tree[cur]->urgencia == pq->tree[pai]->urgencia && pq->tree[cur]->chegada < pq->tree[pai]->chegada)break;
        pq_swap(pq, cur, pai);
        cur = pai;
        pai = (cur - 1)/2;
    }
}

void pq_fix_down(PQ* pq)
{
    int cur = 0;
    int filho = maior_filho(pq, cur);
    while(pq->tree[filho]->urgencia != -1){
        //a ordem de chegada é critério de desempate
        if(pq->tree[cur]->urgencia < pq->tree[filho]->urgencia)break;
        if(pq->tree[cur]->urgencia == pq->tree[filho]->urgencia && pq->tree[cur]->chegada > pq->tree[filho]->chegada)break;
        pq_swap(pq, cur, filho);
        cur = filho;
        filho = maior_filho(pq, cur); 
    }
}

bool pq_enfileirar(PQ* pq, int id, int urgencia)
{
    if(pq_cheia(pq))return false;
    pq->ultima_chegada++;
    pq->fim++;
    pq->tree[pq->fim]->id = id;
    pq->tree[pq->fim]->urgencia = urgencia;
    pq->tree[pq->fim]->chegada = pq->ultima_chegada;
    pq_fix_up(pq);
    return true;
}

int pq_desenfileirar(PQ* pq)
{
    if(pq_vazia(pq))return -1;
    int saida = pq->tree[0]->id;//novo nó raiz
    pq->tree[0] = pq->tree[pq->fim];
    pq->tree[pq->fim]->urgencia = 6;
    pq->fim--;
    pq_fix_down(pq);
    return saida;
}

bool print_pq(PQ* pq)
{
    if (pq_vazia(pq)) return false;
    PQ* copy = criar_pq();
    copy->fim = pq->fim;
    copy->ultima_chegada = pq->ultima_chegada;
    for(int i = 0; i < TAM; i++){
        copy->tree[i] = malloc(sizeof(NO));
        copy->tree[i]->chegada = pq->tree[i]->chegada;
        copy->tree[i]->id = pq->tree[i]->id;
        copy->tree[i]->urgencia = pq->tree[i]->urgencia;
    }
    while(!pq_vazia(copy)){
        printf("%d\n", pq_desenfileirar(copy));
    }
    pq_apagar(copy);
    return true;
}

int get_fim(PQ *pq)
{
    return pq->fim;
}

int get_prioridade_inicio(PQ* pq)
{
    return pq->tree[0]->urgencia;
}

int get_chegada_inicio(PQ* pq)
{
    return pq->tree[0]->chegada;
}

bool buscar_pq(int id, PQ *pq) //função retorna true se o paciente foi achado na fila, false caso contrário
{
    for (int i = 0; i < pq->fim; i++)
    {
        if (id == pq->tree[i]->id)
        {
            return true;
        }
    }
    return false;
}