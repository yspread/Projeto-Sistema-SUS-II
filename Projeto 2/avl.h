#ifndef AVL_H
    #define AVL_H
    #include <stdbool.h>

    //a avl é a estrutura de dados que armazenará todas as informações do sistema
    //definição das structs necessárias para a implementação da avl ENCADEADA
    typedef struct no_ NO;
    typedef struct avl_ AVL;

    AVL* avl_criar_arvore();//função para criar a avl
    void avl_apagar(AVL** arvore);//função para apagar a avl
    void avl_inserir(AVL* arvore, PACIENTE* paciente);//função para inserção de paciente
    bool avl_remover(AVL* arvore, int chave);//funções para remoção de paciente por chave
    PACIENTE* avl_busca(NO* cur, int chave); //busca por chave
    void imprimir_avl(AVL* arvore); //imprime seguindo o percurso EM ORDEM
    bool avl_vazia(AVL* arvore); //verifica se a avl está vazia

    //funções para salvar e carregar a avl
    bool save_avl(AVL* avl);
    bool load_avl(AVL** avl);

#endif