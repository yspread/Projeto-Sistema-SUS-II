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
    3-
    4-
    5-
    6-pronto
    7-pronto
*/

void imprime_menu();
void clean_buffer();

int main()
{
    AVL *avl = avl_criar_arvore();
    PQ *fila = criar_fila();
    if (load(&avl, &fila) == false)
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
                if (pq_cheia(fila) == false)    //VERIFICAR COMO BUSCAR O PACIENTE NA FILA, SÓ FALTA ISSO PRA ESSA FUNÇÃO
                {
                    if(buscar_paciente_fila(fila, id)){
                        printf("Paciente já está na fila.\n");
                    }
                    else{
                        pq_enfileirar(fila, id);
                        printf("Paciente inserido na fila para a triagem.\n");
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
                if(buscar_paciente_fila(fila, id)){ //VER AQUI A FUNÇÃO DE BUSCA TBM
                    printf("Paciente está na fila, nao é possivel registrar seu óbito.\n");
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
                printf("Digite o ID do paciente a adicionar um procedimento no historico:");
                int id;
                scanf("%d", &id);
                clean_buffer();
                PACIENTE *paciente = buscar_paciente(lista, id);
                if (paciente == NULL)
                {
                    printf("Nao existe um paciente com esse ID em nosso sistema\n");
                }
                else
                {
                    char texto[100];
                    printf("Digite o procedimento a ser adicionado:");
                    fgets(texto, 100, stdin);
                    texto[strcspn(texto, "\n")] = '\0';
                    PROCEDIMENTO *procedimento = criar_procedimento(texto);
                    if (inserir_procedimento(get_historico(paciente), procedimento))
                    {
                        printf("Procedimento inserido no historico do paciente com sucesso\n");
                    }
                    else
                    {
                        printf("Nao foi possivel inserir o procedimento.\n");
                    }
                }
                break;
            }

            case 4://buscar paciente por ID
            {
                printf("Digite o ID do paciente a remover um procedimento de seu historico (sera removido o procedimento mais recente):");
                int id;
                scanf("%d", &id);
                clean_buffer();
                PACIENTE *paciente = buscar_paciente(lista, id);
                if (paciente == NULL)
                {
                    printf("Nao existe um paciente com esse ID em nosso sistema\n");
                }
                else
                {
                    if (historico_vazio(get_historico(paciente)))
                    {
                        printf("O historico do paciente esta vazio.\n");
                    }
                    else
                    {
                        if (retirar_procedimento(get_historico(paciente)))
                        {
                            printf("Procedimento retirado com sucesso.\n");
                        }
                        else
                        {
                            printf("Não foi possivel retirar o procedimento.\n");
                        }
                    }    
                }
                break;
            }

            case 5: //mostrar fila de espera
            {
                int id = pq_desenfileirar(fila);
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
            case 6: //dar alta a um paciente
            {
                int id = pq_desenfileirar(fila);
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
                if (save(avl, fila) == false)
                {
                    printf("Não foi possível salvar os dados no sistema\n");
                    pq_apagar(&fila);
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