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
    bool pq_enfileirar(PQ *pq, int id, int urgencia);  //funcao que coloca um paciente na fila
    int pq_desenfileirar(PQ *pq);  //chama o proximo da fila para atendimento
    int get_fim(PQ *pq); //retorna o indice do ultimo elemento da fila
    bool print_pq(PQ *pq);  //imprime o ID do paciente
    bool buscar_pq(int id, PQ* pq); //verifica se um paciente ja está na fila
    
    //funçoes para salvar e carregar a fila
    bool save_pq(PQ* pq);
    bool load_pq(PQ** pq);
#endif