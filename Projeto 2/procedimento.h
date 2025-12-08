#ifndef PROCEDIMENTO_H
    #define PROCEDIMENTO_H

    //procedimento funciona como o item a ser usado apenas no historico
    typedef struct procedimento_ PROCEDIMENTO;
    PROCEDIMENTO* criar_procedimento(char* str);
    void apagar_procedimento(PROCEDIMENTO** p);
    char *get_nome_procedimento(PROCEDIMENTO *p);
    int get_size_procedimento(PROCEDIMENTO *p);
    void print_procedimento(PROCEDIMENTO* p);
    bool procedimento_cheio(PROCEDIMENTO* p);
#endif