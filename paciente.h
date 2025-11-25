#ifndef PACIENTE_H
    #define PACIENTE_H
    #include <stdbool.h>
    
    //o paciente funciona como o TAD item do sistema
    typedef struct paciente_ PACIENTE;

    int get_prioridade(PACIENTE *paciente); //função para acessar o nivel de prioridade
    int get_ID(PACIENTE *paciente); //função para que eu consiga acessar o id diretamente do paciente
    char *get_nome_paciente(PACIENTE *paciente); //função para que eu consiga acessar o nome do paciente diretamente
    int get_tamanho_nome_paciente(PACIENTE *paciente);

    bool apagar_paciente(PACIENTE **paciente);
    PACIENTE* criar_paciente(int id, char* nome, int prioridade);
    
#endif