#ifndef PRIORITY_QUEUE_H
    #define PRIORITY_QUEUE_H
    #include <stdbool.h>


    //definição das structs necessárias para a implementação da fila de prioridade SEQUENCIAL usando uma heap
    typedef struct no_ NO;
    typedef struct pq_ PQ;
    PQ* criar_pq(); //cria uma priority queue
    void pq_apagar(PQ **pq);  //apaga a priority queue
    bool pq_cheia(PQ *pq); //funcao para verificar se a fila esta cheia
    bool pq_vazia(PQ *pq);  //funcao para verificar se a fila esta vazia
    bool pq_enfileirar(PQ *pq, int id, int urgencia);  //funcao que coloca um no na fila
    int pq_desenfileirar(PQ *pq);  //funcao que tira o proximo no com maior prioridade da fila
    void print_pq(PQ *pq);  //imprime o ID do paciente
#endif