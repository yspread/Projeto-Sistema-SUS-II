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

    //agora salvamento da fila de prioridade
    FILE *fp_pq = fopen("pq_itens.bin", "wb");
    if (!fp_pq)
    {
        return false; //salvamento mal sucedido
    }
    int tamanhofila = get_fim(pq) + 1;
    
}

bool load(AVL* avl, PQ*pq)
{
    
}