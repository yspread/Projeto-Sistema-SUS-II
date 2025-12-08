#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"
#include "paciente.h"

#define max(a, b) ((a > b) ? a : b)

typedef struct no_
{
    PACIENTE* paciente;
    NO* esq;
    NO* dir;
    int alt;
} NO;

typedef struct avl_
{
    NO* raiz;
} AVL;

AVL* avl_criar_arvore() //aloca memoria para a avl
{
    AVL* arvore = (AVL*) malloc(sizeof(AVL));
    if(arvore != NULL)arvore->raiz = NULL;
    return arvore;
}

void avl_apagar_aux(NO* cur) //função auxiliar para apagar a avl
{
    if(cur != NULL){
        avl_apagar_aux(cur->esq);
        avl_apagar_aux(cur->dir);
        apagar_paciente(&(cur->paciente));
        free(cur);
        cur = NULL;
    }
}

void avl_apagar(AVL** arvore) //apagar avl
{
    avl_apagar_aux((*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

NO* avl_criar_NO(PACIENTE* paciente) //aloca memoria para um nó que irá conter um novo paciente no sistema
{
    NO* aux = (NO*)malloc(sizeof(NO));
    if(aux != NULL){
        aux->alt = 0;
        aux->esq = NULL;
        aux->dir = NULL;
        aux->paciente = paciente;
    }
    return aux;
}

//as 5 funções a seguir correspondem as funções responsáveis por manter a avl balanceada(rotações)
NO* rodar_direita(NO* cur)
{
    NO* aux = cur->esq;
    cur->esq = aux->dir;
    aux->dir = cur;
    cur->alt = max(cur->dir->alt, cur->esq->alt) + 1;
    aux->alt = max(aux->dir->alt, aux->esq->alt) + 1;
    return aux;
}

NO* rodar_esquerda(NO* cur)
{
    NO* aux = cur->dir;
    cur->dir = aux->esq;
    aux->esq = cur;
    cur->alt = max(cur->dir->alt, cur->esq->alt) + 1;
    aux->alt = max(aux->dir->alt, aux->esq->alt) + 1;
    return aux;
}

NO* rodar_esquerda_direita(NO* cur)
{
    cur->esq = rodar_esquerda(cur->esq);
    return rodar_direita(cur);
}

NO* rodar_direita_esquerda(NO* cur)
{
    cur->dir = rodar_direita(cur->dir);
    return rodar_esquerda(cur);
}

NO* balancear_NO(NO* cur)
{
    int fb = cur->esq->alt - cur->dir->alt;
    if(fb == -2){
        if(cur->dir->esq->alt - cur->dir->dir->alt <= 0){
            cur = rodar_esquerda(cur);
        }
        else{
            cur = rodar_direita_esquerda(cur);
        }
    }
    if(fb == 2){
        if(cur->esq->dir->alt - cur->esq->esq->alt <= 0){
            cur = rodar_direita(cur);
        }
        else{
            cur = rodar_esquerda_direita(cur);
        }
    }
    return cur;
}

NO* avl_inserir_NO(NO* cur, PACIENTE* paciente) //função auxiliar para inserir nó na avl
{
    //a função procura o primeiro nó vazio no qual o paciente pode ser inserido
    //a procura segue as propriedades de uma abb (que a avl respeita) 
    if(cur == NULL){
        cur = avl_criar_NO(paciente);
    }
    else if(get_ID(paciente) < get_ID(cur->paciente)){
        cur->esq = avl_inserir_NO(cur->esq, paciente);
    }
    else if(get_ID(paciente) > get_ID(cur->paciente)){
        cur->dir = avl_inserir_NO(cur->dir, paciente);
    }
    cur->alt = max(cur->esq->alt, cur->dir->alt) + 1;
    return cur = balancear_NO(cur);
}

void avl_inserir(AVL* arvore, PACIENTE* paciente) //função principal para inserir nó na avl
{
    arvore->raiz = avl_inserir_NO(arvore->raiz, paciente);
}

//função auxiliar para remoção na avl, para substituir (quando necessário) o nó removido
//pelo maior valor da subárvore esquerda
void troca_max_esq(NO* troca, NO* raiz, NO* ant)
{
    if(troca->dir != NULL){
        troca_max_esq(troca->dir, raiz, troca);
        return;
    }
    if(ant == raiz){
        ant->esq = troca->esq;
    }
    else{
        ant->dir = troca->esq;
    }
    PACIENTE* aux = raiz->paciente;
    raiz->paciente = troca->paciente;
    apagar_paciente(&aux);
    free(troca);
    troca = NULL;
}

NO* avl_remover_NO(NO* cur, int chave) //função auxiliar para remover um paciente da avl, buscando pelo ID
{
    if(cur == NULL)return NULL;
    if(chave == get_ID(cur->paciente)){
        if(cur->esq == NULL || cur->dir == NULL){
            NO* aux = cur;
            if(cur->esq == NULL){
                cur = cur->dir;
            }
            else{
                cur = cur->esq;
            }
            apagar_paciente(aux->paciente);
            free(aux);
            aux = NULL;
        }
        else{
            troca_max_esq(cur->esq, cur, cur);
        }
    }
    else if(chave > get_ID(cur->paciente)){
        avl_remover_NO(cur->dir, chave);
    }
    else{
        avl_remover_NO(cur->esq, chave);
    }
    cur = balancear_NO(cur);
    return cur;
}

bool avl_remover(AVL* arvore, int chave) //função principal para remover um paciente da avl
{
    return ((arvore->raiz = avl_remover_NO(arvore->raiz, chave)) != NULL);
}

PACIENTE* avl_busca(NO* cur, int chave) //função para buscar um paciente por um ID
{
    if(cur == NULL)return NULL;
    if(chave > get_ID(cur->paciente))return avl_busca(cur->dir, chave);
    else if(chave < get_ID(cur->paciente))return avl_busca(cur->esq, chave);
    else return cur->paciente;
}

void imprimir_emordem(NO* cur) //percorre a avl em ordem para gerar uma sequencia em ordem crescente de IDs
{
    if(cur != NULL){
        imprimir_emordem(cur->esq);
        imprimir_paciente(cur->paciente);
        imprimir_emordem(cur->dir);
    }
}

void imprimir_avl(AVL* arvore) //imprime a avl, seguindo o percurso em ordem
{
    imprimir_emordem(arvore->raiz);
}

bool avl_vazia(AVL* arvore) //verifica se a avl está vazia
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        return true;
    }
    else return false;
}

NO* reconstruir_arvore(PACIENTE *vetor, int indice, int qtd_registros) {  //função para reconstruir a AVL a partir de um vetor (auxiliar a load)
    if (indice >= qtd_registros || vetor[indice].ID == -1) {//se o indice ultrapassar o numero de pacientes ou se o ID indicar que não há paciente
        return NULL;
    }
    PACIENTE *novo_paciente = (PACIENTE *) malloc (sizeof(PACIENTE));  //vamos alocar um novo paciente para todo nó existente e válido
    if (novo_paciente == NULL) {
        return NULL;
    }
    *novo_paciente = vetor[indice];
    NO *novo_no = avl_criar_NO(novo_paciente); //vamos colocar o paciente em um nó
    if (novo_no == NULL) {
        free(novo_paciente);
        return NULL;
    }
    novo_no->esq = reconstruir_arvore(vetor, 2 * indice +1, qtd_registros); //o filho à esquerda do nó está na posição 2i+1 do vetor
    novo_no->dir = reconstruir_arvore(vetor, 2 * indice +2, qtd_registros);//o filho à direita do nó está na posição 2i+2 do vetor
    novo_no->alt = 1+ ((get_altura(novo_no->esq)) > get_altura(novo_no->dir) ? get_altura(novo_no->esq) : get_altura(novo_no->dir)); //reajuste da altura
    return novo_no;
}

void preencher_vetor(NO *no, PACIENTE **vetor, int indice, int tamanho_max)  { //funcao auxiliar para colocar os nós da árvore em um vetor; 
    //o tamanho maximo é o tamanho da própria avl considerando-a como uma arvore binaria completa cheia
    if (no == NULL || indice >= tamanho_max) {
        return;
    }
    vetor[indice] = no->paciente; //colocamos as informações do paciente em sua respectiva posicao no vetor
    preencher_vetor(no->esq, vetor, (indice*2) +1, tamanho_max);  //o filho esquerdo estará do nó na posição i estará na posição 2i +1
    preencher_vetor(no->dir, vetor, (indice*2) +2, tamanho_max);  //o filho direito estará na posicao 2i +2
}


bool save_avl(AVL* avl)
{
    if (!avl)
    {
        return false; //salvamento mal sucedido
    }
    //salvamento da avl:
    FILE *fp_avl = fopen("avl_itens.bin", "wb");
    if (!fp_avl)
    {
        return false; //salvamento mal sucedido
    }
    if (avl_vazia(avl)) { //se a avl estiver vazia, nao há o que salvar
        fclose(fp_avl);
    }
    else { //se nao estiver vazia, vamos guardar as informações dos pacientes em um vetor, para facilitar percorrer os nós e suas informações
        int n = avl->raiz->alt; //n será a altura da avl
        int tam_avl = pow(2, n+1) -1; //o tamanho maximo de uma arvore completa com altura n é 2^(n+1)-1 
        PACIENTE **vetor = (PACIENTE **) calloc (tam_avl, sizeof(PACIENTE*)); //vamos alocar um vetor de ponteiros para PACIENTE
        if (vetor==NULL) { //falha na alocação de memória do vetor
            fclose(fp_avl);
            return false;
        }
        preencher_vetor(avl->raiz, vetor, 0, tam_avl); //preenchemos o vetor com as informações da nossa AVL
        PACIENTE* vazio = criar_paciente(-1, ""); //caso o nó seja NULL definimos o paciente vazio
        fwrite(&tam_avl, sizeof(int), 1, fp_avl); //salvamos o tamanho da avl para guiar o load
        for (int i=0; i<tam_avl; i++) {
            if(vetor[i] != NULL) { //se existir paciente naquela posição, salvamos os seus dados
                save_paciente(vetor[i], fp_avl);
            }
            else { //se nao existir, indicamos "vazio" para simbolizar que nao há paciente ali
                save_paciente(vazio, fp_avl);
            }
        }
        free(vetor); //liberamos o espaco da memoria auxiliar (o vetor)
        fclose(fp_avl);
        fp_avl = NULL;
        return true;
    }
}

bool load_avl(AVL** avl)
{ 
    if (!avl || !(*avl)) {  //se nao houver avl, nao é possivel carregá-la
        return false;
    }
    FILE *fp_avl = fopen("avl_itens.bin", "rb");
    if (fp_avl== NULL) {
        return false; //se o arquivo nao existir, retornamos falso
    }
    int tam_avl;
    fread(&tam_avl, sizeof(int), 1, fp_avl);

    PACIENTE** temp = (PACIENTE *) malloc(tam_avl * sizeof(PACIENTE));
    if (temp == NULL) { //em caso de falha de alocação, fecha o arquio e retorna falso
        fclose(fp_avl);
        return false;
    }
    for(int i = 0; i < tam_avl; i++){        
        temp[i] = load_paciente(fp_avl);
    }
    (*avl)->raiz = reconstruir_arvore(temp, 0, tam_avl); //agora vamos reconstruir a AVL
    free(temp);
    fclose(fp_avl); 
    return true;
}