#ifndef PACIENTE_H
    #define PACIENTE_H
    #include <stdbool.h>
    
    //nao colocamos a prioridade no tad paciente, mas sim no nó da priority queue, por não ser
    //uma característica intrinseca do paciente
    //o paciente funciona como o TAD item do sistema
    typedef struct paciente_ PACIENTE;

    //funçoes auxiliares para acessar valores
    int get_ID(PACIENTE *paciente);
    char *get_nome_paciente(PACIENTE *paciente);

    //funçoes principais relacionadas ao paciente
    bool apagar_paciente(PACIENTE **paciente);
    PACIENTE* criar_paciente(int id, char* nome, int prioridade);
    void imprimir_paciente(PACIENTE* paciente);

#endif