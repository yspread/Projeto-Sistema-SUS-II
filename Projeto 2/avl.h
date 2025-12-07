#ifndef AVL_H
    #define AVL_H
    #include <stdbool.h>

    //a avl é a estrutura de dados que armazenará todas as informações do sistema
    //definição das structs necessárias para a implementação da avl ENCADEADA
    typedef struct no_ NO;
    typedef struct avl_ AVL;

    //funções para criar e apagar avl
    AVL* avl_criar_arvore();
    void avl_apagar_aux(NO* cur);
    void avl_apagar(AVL** arvore);

    NO* avl_criar_NO(PACIENTE* paciente);//cria nó

    //funções para rotações e balanceamento da avl
    NO* rodar_direita(NO* cur);
    NO* rodar_esquerda(NO* cur);
    NO* rodar_esquerda_direita(NO* cur);
    NO* rodar_direita_esquerda(NO* cur);
    NO* balancear_NO(NO* cur);
    
    //funções para inserção de nó
    NO* avl_inserir_NO(NO* cur, PACIENTE* paciente);
    void avl_inserir(AVL* arvore, PACIENTE* paciente);
    
    //funções para remoção de nó
    void troca_max_esq(NO* troca, NO* raiz, NO* ant);
    NO* avl_remover_NO(NO* cur, int chave);
    bool avl_remover(AVL* arvore, int chave);
    
    //funçoes de busca e percurso na avl
    PACIENTE* avl_busca(NO* cur, int chave);
    void imprimir_emordem(NO* cur);
    void imprimir_avl(AVL* arvore);

#endif