#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definição da estrutura do nó (arvore binária)
typedef struct No
{
    char valor[50];
    struct No *esquerda;
    struct No *direita;
    struct No *pai;
} No;

// Função para criar um novo nó
No* criarNo (char valor[50]) {
    No* novo = (No*) malloc(sizeof(No)); //Alocação na memória
    if (novo == NULL) {
        printf("Erro ao alocar memória!");
        exit(1); //Sai do sistema
    }
    strcpy(novo->valor, valor); //Copia o valor para o nó
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->pai = NULL;
    return novo;
}

No* Casa (No* raiz, const char* valor) {
    //Cria uma raiz caso ela não exista
    if (raiz == NULL) {
        return criarNo(valor);
    }
    //Comparação para decidir se o novo nó vai para a esquerda ou direita
    //Esquerda se o valor for menor
    if (strcmp(valor, raiz->valor) < 0) {
        No* filho = Casa(raiz->esquerda, valor);
        raiz->esquerda = filho;
        filho->pai = raiz;
    }
    //Direita se o valor for maior ou igual
     else {
        No* filho = Casa(raiz->direita, valor);
        raiz->direita = filho;
        filho->pai = raiz;
    }
    return raiz; //Retorna a raiz para a estrutura da árvore
}

//Função para percorrer a árvore em pré-ordem
void preordem (No* raiz) {
    if (raiz != NULL) {
        printf("%s ", raiz->valor);
        preordem(raiz->esquerda);
        preordem(raiz->direita);
    }
}

//Função para percorrer a árvore em ordem
void emordem (No* raiz) {
    if (raiz != NULL) {
        emordem(raiz->esquerda);
        printf("\n%s ", raiz->valor);
        emordem(raiz->direita);
    }
}

//Função para percorrer a árvore em pós-ordem
void posordem (No* raiz) {
    if (raiz != NULL){
        posordem(raiz->esquerda);
        posordem(raiz->direita);
        printf("%s ", raiz->valor);
    }
}

//Função para liberar a memória alocada para a árvore
void liberar (No* raiz) {
    if (raiz!=NULL) {
        liberar(raiz->esquerda);
        liberar(raiz->direita);
        free(raiz);
    }
}

//Definição da função esquerda para percorrer a árvore
No* esquerda (No* raiz) {
    //Caso a raiz não seja nula e tenha um filho à esquerda, o ponteiro é atualizado para o filho à esquerda
    if (raiz != NULL && raiz->esquerda != NULL) {
        printf("\n Você foi da %s para a %s ", raiz->valor, raiz->esquerda->valor);
        printf("\n Você está atualmente na %s ", raiz->esquerda->valor);
        getchar(); getchar(); //Pausa para o usuário ver a mensagem
        return raiz->esquerda; //Atualiza o valor da raiz para seu filho à esquerda
    } else {
        //Caso não haja um filho à esquerda, uma mensagem é exibida e a raiz não muda
        printf("\n Não há mais elementos à esquerda.\n");
        return raiz;
    }
}

//Definição da função voltar para percorrer a árvore
No* voltar(No* raiz) {
    //Caso a raiz não seja nula e tenha um pai, o ponteiro é atualizado para o pai
    if (raiz != NULL && raiz->pai != NULL) {
        printf("Voltando de %s para o %s\n", raiz->valor, raiz->pai->valor);
        printf("Você está atualmente na %s\n", raiz->pai->valor);
        getchar(); getchar(); //Pausa para o usuário ver a mensagem
        return raiz->pai; //Atualiza o valor da raiz para seu pai
    } else {
        //Caso o usuário esteja na raiz da árvore, uma mensagem é exibida
        printf("Você está na %s e não pode sair da casa (é a raiz).\n", raiz->valor);
        return raiz;
    }
}

//Definição da função direita para percorrer a árvore
No* direita (No* raiz) {
    //Caso a raiz não seja nula e tenha um filho à direita, o ponteiro é atualizado para o filho à direita
    if (raiz != NULL && raiz->direita != NULL) {
        printf("\n Você foi da %s para a %s ", raiz->valor, raiz->direita->valor);
        printf("\n Você está atualmente na %s ", raiz->direita->valor);
        getchar(); getchar(); //Pausa para o usuário ver a mensagem
        return raiz->direita; //Atualiza o valor da raiz para seu filho à direita
    } else {
        //Caso não haja um filho à direita, uma mensagem é exibida e a raiz não muda
        printf("\n Não há mais elementos à direita.\n");
        return raiz;
    }
}

//Função principal do programa
int main () {
    //Define a raiz da árvore como nula
    No* raiz = NULL;
    int opcao;

    //Definição da casa com seus cômodos, utilizando a função Casa para criar os nós da árvore
    raiz = Casa(raiz, "Entrada da casa");
    raiz = Casa(raiz, "Sala de estar");
    raiz = Casa(raiz, "Sala de jantar");
    raiz = Casa(raiz, "Cozinha");
    raiz = Casa(raiz, "Corredor");
    raiz = Casa(raiz, "Quarto");

    //Exibição do menu e suas opções
    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Esquerda\n");
        printf("2. Direita\n");
        printf("3. Voltar\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                raiz = esquerda(raiz);
                break;
            case 2:
                raiz = direita(raiz);
                break;
            case 3:
                raiz = voltar(raiz);
                break;
            case 0:
                printf("Saindo...\n");
                liberar(raiz);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);
      return 0; //Define que enquanto o usuário não selecionar a opção de sair, o programa continuará em loop
}
