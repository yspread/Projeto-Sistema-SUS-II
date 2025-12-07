#include "IO.h"
#include "avl.h"
#include "fila.h"
#include "paciente.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool save(AVL* avl, PQ* pq)
{
    if (!avl || !pq)
    {
        return false; //salvamento mal sucedido
    }
    PACIENTE *paciente; //auxiliar

    //primeiro, salvamento da avl
    FILE *fp_avl = fopen("avl_itens.bin", "wb");
    if (!fp_avl)
    {
        return false; //salvamento mal sucedido
    }
    
    
    //FAZER AQUI O SALVAMENTO DA AVL


    avl_apagar(&avl);
    fclose(fp_avl);
    fp_avl = NULL;

    //agora salvamento da fila de prioridade
    FILE *fp_pq = fopen("pq_itens.bin", "wb");
    if (!fp_pq)
    {
        return false; //salvamento mal sucedido
    }
    int tamanhofila = get_fim(pq) + 1;
    int id; //vai armazenar o id do paciente a ser salvo atual
    int prioridade;
    fwrite(&tamanhofila, sizeof(int), 1, fp_pq); //salvamos o tamanho da fila para ler adequadamente no load
    while(!pq_vazia(pq))
    {
        //no arquivo, os ids estarão na ordem de prioridade
        prioridade = get_prioridade_inicio(pq);
        fwrite(&prioridade, sizeof(int), 1, fp_pq); //salvo a ordem de prioridade do paciente
        id = pq_desenfileirar(pq);
        fwrite(&id, sizeof(int), 1, fp_pq);
    }
    pq_apagar(&pq);
    fclose(fp_pq);
    fp_pq = NULL;
    return true; //salvamento sucedido
    
}

bool load(AVL** avl, PQ** pq)
{
    if (!*avl || !*pq)
    {
        return false; //carregamento mal sucedido
    }

    //primeiro, carregamento da avl

    //agora carregamento da fila de prioridade
    FILE *fp_pq = fopen("pq_itens.bin", "rb");
    if (!fp_pq)
    {
        return false; //carregamento mal sucedido
    }
    int tamanhofila;
    fread(&tamanhofila, sizeof(int), 1, fp_pq); //leio o tamanho da fila salva
    int id, prioridade;
    for (int i = 0; i < tamanhofila; i++)
    {
        fread(&prioridade, sizeof(int), 1, fp_pq); //leio a prioridade do paciente
        fread(&id, sizeof(int), 1, fp_pq); //leio o id do paciente
        pq_enfileirar(*pq, id, prioridade);
    }
    fclose(fp_pq);
}