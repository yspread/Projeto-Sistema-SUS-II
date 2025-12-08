#ifndef HISTORICO_H
    #define HISTORICO_H
    #include "procedimento.h"

    typedef struct historico_ HISTORICO;

    //funçoes que operam no historico do paciente: PILHA
    HISTORICO* criar_historico(); //pra criar um historico caso o paciente nao tenha
    void apagar_historico(HISTORICO** historico); //apagar historico caso paciente morra e pra salvar 
    void print_historico(HISTORICO* historico); //consultar o historico de alguem pelo ID
    bool inserir_procedimento(HISTORICO* historico, PROCEDIMENTO* procedimento); //empilhar
    bool retirar_procedimento(HISTORICO* historico); //desempilhar
    bool historico_vazio(HISTORICO* historico);
    int get_tamanho_historico(HISTORICO* historico); //para acessar o tamanho do historico
    PROCEDIMENTO *get_topo(HISTORICO *historico);
    bool historico_cheio(HISTORICO* historico);
    
#endif