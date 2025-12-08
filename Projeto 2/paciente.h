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
    PACIENTE* criar_paciente(int id, char* nome);
    void imprimir_paciente(PACIENTE* paciente);

    //funções para salvar e carregar o paciente em um arquivo
    void save_paciente(PACIENTE* paciente, FILE* fptr);
    PACIENTE* load_paciente(FILE* fptr);

#endif