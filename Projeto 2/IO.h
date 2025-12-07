#ifndef IO_H
    #define IO_H
    #include <stdbool.h>

    bool save(AVL* avl, PQ* pq); //função para salvar os dados em arquivos
    bool load(AVL** avl, PQ** pq); //função para carregar os dados dos arquivos
#endif