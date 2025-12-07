#include "paciente.h"
#include "avl.h"
#include "fila.h"
#include "IO.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* 1-problema da busca
    2- problema da busca
    3-pronto
    4-pronto
    5-pronto
    6-pronto
    7-pronto
*/

void imprime_menu();
void clean_buffer();

int main()
{
    AVL *avl = avl_criar_arvore();
    PQ *pq = criar_pq();
    if (load(&avl, &pq) == false)
    {
        printf("Não foi possível abrir os arquivos salvos.");
    }
    
    int comando;
    imprime_menu();
    while (true) //isso sempre vai acontecer enquanto o programa roda, a nao ser no caso 7, que ai finaliza a função
    {
        scanf("%d", &comando);
        clean_buffer();
        //execução baseada no comando escolhido
        switch (comando)
        {
            case 1: //registrar paciente
            {
                int id, prioridade;
                char nome[100];
                PACIENTE *paciente;
                printf("Digite o ID do paciente:");
                scanf("%d", &id);
                clean_buffer();
                if(id <= 0){
                    printf("ID invalido\n");
                    break;
                }
                if (avl_busca(avl, id) == NULL)
                {
                    printf("Digite o nome do paciente:");
                    fgets(nome, 100, stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    printf("Digite o nível de prioridade do paciente:\n");
                    printf("1. Emergência\n");
                    printf("2. Muito Urgente\n");
                    printf("3. Urgente\n");
                    printf("4. Pouco Urgente\n");
                    printf("5. Não Urgência\n\n");
                    scanf("%d", &prioridade);
                    if (prioridade <= 0 || prioridade > 5)
                    {
                        printf("Prioridade inválida.\n");
                        break;
                    }
                    paciente = criar_paciente(id, nome, prioridade);
                    if (paciente == NULL)
                    {
                        printf("Nao foi possivel registrar o paciente.\n");
                    }
                    else
                    {
                        avl_inserir(avl, paciente);
                        printf("Paciente registrado com sucesso\n");
                    }
                }
                else
                {
                    printf("Paciente já registrado.\n");
                }
                if (pq_cheia(pq) == false)
                {
                    if(buscar_pq(id, pq)){
                        printf("Paciente já está na fila.\n");
                    }
                    else{
                        pq_enfileirar(pq, id, prioridade);
                        printf("Paciente inserido na fila de atendimento.\n");
                    }
                }
                else
                {
                    printf("Fila cheia! Nao foi possivel adicionar o paciente na fila\n");
                }
                break;
            }

            case 2: //remover paciente do sistema
            {
                printf("Digite o ID do paciente a ser removido da lista:");
                int id;
                scanf("%d", &id);
                clean_buffer();
                if(buscar_pq(id, pq)){
                    printf("Paciente está na fila, nao é possivel apagá-lo do sistema.\n");
                }
                else {
                    if (!avl_remover(avl, id))
                    {
                        printf("Não existe um paciente com esse id no sistema\n");
                    }
                    else
                    {
                        printf("Paciente removido do sistema.\n");
                    }
                }
                break;
            }

            case 3://listar pacientes
            {
                if (avl_vazia(avl))
                {
                    printf("Nenhum paciente registrado no sistema.\n");
                    break;
                }
                else
                {
                    imprimir_avl(avl);
                }
                break;
            }

            case 4://buscar paciente por ID
            {
                printf("Digite o ID do paciente");
                int id;
                scanf("%d", &id);
                clean_buffer();
                PACIENTE *paciente = avl_busca(avl, id);
                if (paciente == NULL)
                {
                    printf("Nao existe um paciente com esse ID em nosso sistema\n");
                }
                else
                {
                    imprimir_paciente(paciente);
                }
                break;
            }

            case 5: //mostrar fila de espera
            {
                if (print_pq(pq) == false)
                {
                    printf("A fila esta vazia.\n");
                }
                break;
            }
            case 6: //dar alta a um paciente
            {
                int id = pq_desenfileirar(pq);
                if (id == -1)
                {
                    printf("A fila esta vazia.\n");
                }
                else
                {
                    printf("Paciente de ID %d recebeu alta do hospital.\n", id);
                }
                break;
            }

            case 7: //sai o sistema
            {
                printf("Saindo do sistema.\n");
                if (save(avl, pq) == false)
                {
                    printf("Não foi possível salvar os dados no sistema\n");
                    pq_apagar(&pq);
                    avl_apagar(&avl);
                }
                return 0;
            }
        
            default: //comando invalido inserido pelo usuario
            {
                printf("Comando inválido!\n"); //se o comando for invalido, avisar, reenviar as opcoes e perguntar dnv
                break;
            }
        }
        imprime_menu(); //pede nova inserção de comando
    }
    
}

void imprime_menu()
{
    printf("\nPressione enter para continuar\n");
    clean_buffer();
    printf("Digite o valor correspondente a operacao que você deseja realizar:\n");
    printf("1. Registrar paciente\n");
    printf("2. Remover paciente do sistema\n");
    printf("3. Listar pacientes\n");
    printf("4. Buscar paciente por ID\n");
    printf("5. Mostrar fila de espera\n");
    printf("6. Dar alta a um paciente\n");
    printf("7. Sair\n\n");
    return;
}

void clean_buffer()
{
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}