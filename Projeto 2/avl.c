#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"
#include "paciente.h"

#define max(a, b) ((a > b) ? a : b)

typedef struct no_
{
    PACIENTE* paciente;
    NO* esq;
    NO* dir;
    int alt;
} NO;

typedef struct avl_
{
    NO* raiz;
} AVL;

AVL* avl_criar_arvore() //aloca memoria para a avl
{
    AVL* arvore = (AVL*) malloc(sizeof(AVL));
    if(arvore != NULL)arvore->raiz = NULL;
    return arvore;
}

void avl_apagar_aux(NO* cur) //função auxiliar para apagar a avl
{
    if(cur != NULL){
        avl_apagar_aux(cur->esq);
        avl_apagar_aux(cur->dir);
        apagar_paciente(&(cur->paciente));
        free(cur);
        cur = NULL;
    }
}

void avl_apagar(AVL** arvore) //apagar avl
{
    avl_apagar_aux((*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

NO* avl_criar_NO(PACIENTE* paciente) //aloca memoria para um nó que irá conter um novo paciente no sistema
{
    NO* aux = (NO*)malloc(sizeof(NO));
    if(aux != NULL){
        aux->alt = 0;
        aux->esq = NULL;
        aux->dir = NULL;
        aux->paciente = paciente;
    }
    return aux;
}

//as 5 funções a seguir correspondem as funções responsáveis por manter a avl balanceada(rotações)
NO* rodar_direita(NO* cur)
{
    NO* aux = cur->esq;
    cur->esq = aux->dir;
    aux->dir = cur;
    cur->alt = max(cur->dir->alt, cur->esq->alt) + 1;
    aux->alt = max(aux->dir->alt, aux->esq->alt) + 1;
    return aux;
}

NO* rodar_esquerda(NO* cur)
{
    NO* aux = cur->dir;
    cur->dir = aux->esq;
    aux->esq = cur;
    cur->alt = max(cur->dir->alt, cur->esq->alt) + 1;
    aux->alt = max(aux->dir->alt, aux->esq->alt) + 1;
    return aux;
}

NO* rodar_esquerda_direita(NO* cur)
{
    cur->esq = rodar_esquerda(cur->esq);
    return rodar_direita(cur);
}

NO* rodar_direita_esquerda(NO* cur)
{
    cur->dir = rodar_direita(cur->dir);
    return rodar_esquerda(cur);
}

NO* balancear_NO(NO* cur)
{
    int fb = cur->esq->alt - cur->dir->alt;
    if(fb == -2){
        if(cur->dir->esq->alt - cur->dir->dir->alt <= 0){
            cur = rodar_esquerda(cur);
        }
        else{
            cur = rodar_direita_esquerda(cur);
        }
    }
    if(fb == 2){
        if(cur->esq->dir->alt - cur->esq->esq->alt <= 0){
            cur = rodar_direita(cur);
        }
        else{
            cur = rodar_esquerda_direita(cur);
        }
    }
    return cur;
}

NO* avl_inserir_NO(NO* cur, PACIENTE* paciente) //função auxiliar para inserir nó na avl
{
    //a função procura o primeiro nó vazio no qual o paciente pode ser inserido
    //a procura segue as propriedades de uma abb (que a avl respeita) 
    if(cur == NULL){
        cur = avl_criar_NO(paciente);
    }
    else if(get_ID(paciente) < get_ID(cur->paciente)){
        cur->esq = avl_inserir_NO(cur->esq, paciente);
    }
    else if(get_ID(paciente) > get_ID(cur->paciente)){
        cur->dir = avl_inserir_NO(cur->dir, paciente);
    }
    cur->alt = max(cur->esq->alt, cur->dir->alt) + 1;
    return cur = balancear_NO(cur);
}

void avl_inserir(AVL* arvore, PACIENTE* paciente) //função principal para inserir nó na avl
{
    arvore->raiz = avl_inserir_NO(arvore->raiz, paciente);
}

//função auxiliar para remoção na avl, para substituir (quando necessário) o nó removido
//pelo maior valor da subárvore esquerda
void troca_max_esq(NO* troca, NO* raiz, NO* ant)
{
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if(ant == raiz){
        ant->esq = troca->esq;
    }
    else{
        ant->dir = troca->esq;
    }
    PACIENTE* aux = raiz->paciente;
    raiz->paciente = troca->paciente;
    apagar_paciente(&aux);
    free(troca);
    troca = NULL;
}

NO* avl_remover_NO(NO* cur, int chave) //função auxiliar para remover um paciente da avl, buscando pelo ID
{
    if(cur == NULL)return NULL;
    if(chave == get_ID(cur->paciente)){
        if(cur->esq == NULL || cur->dir == NULL){
            NO* aux = cur;
            if(cur->esq == NULL){
                cur = cur->dir;
            }
            else{
                cur = cur->esq;
            }
            apagar_paciente(aux->paciente);
            free(aux);
            aux = NULL;
        }
        else{
            troca_max_esq(cur->esq, cur, cur);
        }
    }
    else if(chave > get_ID(cur->paciente)){
        avl_remover_NO(cur->dir, chave);
    }
    else{
        avl_remover_NO(cur->esq, chave);
    }
    cur = balancear_NO(cur);
    return cur;
}

bool avl_remover(AVL* arvore, int chave) //função principal para remover um paciente da avl
{
    return ((arvore->raiz = avl_remover_NO(arvore->raiz, chave)) != NULL);
}

PACIENTE* avl_busca(NO* cur, int chave) //função para buscar um paciente por um ID
{
    if(cur == NULL)return NULL;
    if(chave > get_ID(cur->paciente))return avl_busca(cur->dir, chave);
    else if(chave < get_ID(cur->paciente))return avl_busca(cur->esq, chave);
    else return cur->paciente;
}

void imprimir_emordem(NO* cur) //percorre a avl em ordem para gerar uma sequencia em ordem crescente de IDs
{
    if(cur != NULL){
        imprimir_emordem(cur->esq);
        imprimir_paciente(cur->paciente);
        imprimir_emordem(cur->dir);
    }
}

void imprimir_avl(AVL* arvore) //imprime a avl, seguindo o percurso em ordem
{
    imprimir_emordem(arvore->raiz);
}
