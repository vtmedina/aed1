#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *pBuffer;

void adicionarPessoa();
void removerPessoa();
void buscarPessoa();
void listarPessoas();
void expandirBuffer(int novaCapacidade);

int main() {
    pBuffer = malloc(sizeof(int) * 5 + 84 * 5);
    if (!pBuffer) return 1;

    *(int *)pBuffer = 0;                        
    *(int *)((char *)pBuffer + 4) = 5;       
    *(int *)((char *)pBuffer + 8) = sizeof(int) * 5 + 84 * 5;

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4- Listar todos\n");
        printf("5- Sair\n");
        printf("Opcao: ");

        scanf("%d", &opcao);
        while(getchar() != '\n');
      
        switch (opcao) {
            case 1: 
                adicionarPessoa(); 
                break;
            case 2: 
                removerPessoa(); 
                break;
            case 3: 
                buscarPessoa(); 
                break;
            case 4: 
                listarPessoas(); 
                break;
            case 5: 
                printf("Saindo...\n"); 
                break;
            default: 
                printf("Opcao invalida!\n");
        }
    } while (opcao != 5);

    free(pBuffer);
    return 0;
}

void expandirBuffer(int novaCapacidade) {
    int novoSize = sizeof(int) * 5 + 84 * novaCapacidade;
    void *novo = realloc(pBuffer, novoSize);
    if (!novo) {
        printf("Erro ao expandir buffer!\n");
        exit(1);
    }
    pBuffer = novo;
    *(int *)((char *)pBuffer + 4) = novaCapacidade;
    *(int *)((char *)pBuffer + 8) = novoSize;
}

void adicionarPessoa() {
    int *total = (int *)pBuffer;
    int *capacidade = (int *)((char *)pBuffer + 4);

    if (*total == *capacidade) {
        expandirBuffer(*capacidade * 2);
    }

    char *novaPessoa = (char *)pBuffer + sizeof(int) * 5 + (*total) * 84;

    printf("Nome: ");
    fgets(novaPessoa, 40, stdin);
    novaPessoa[strcspn(novaPessoa, "\n")] = 0;

    printf("Idade: ");
    scanf("%d%*c", (int *)(novaPessoa + 40));

    printf("Email: ");
    fgets(novaPessoa + 44, 40, stdin);
    novaPessoa[44 + strcspn(novaPessoa + 44, "\n")] = 0;

    (*total)++;
    printf("Pessoa adicionada com sucesso!\n");
}

void removerPessoa() {
    int *total = (int *)pBuffer;
    if (*total == 0) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
    }

    listarPessoas();
    printf("Indice para remover (1-%d): ", *total);

    int indice;
    scanf("%d%*c", &indice);

    if (indice < 1 || indice > *total) {
        printf("Indice invalido!\n");
        return;
    }

    char *alvo = (char *)pBuffer + sizeof(int) * 5 + (indice-1) * 84;
    char *proxima = alvo + 84;

    memmove(alvo, proxima, (*total - indice) * 84);
    (*total)--;

    printf("Pessoa removida com sucesso!\n");
}

void buscarPessoa() {
    int *total = (int *)pBuffer;
    if (*total == 0) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
    }

    char nome[40];
    printf("Nome para buscar: ");
    fgets(nome, 40, stdin);
    nome[strcspn(nome, "\n")] = 0;

    int encontrados = 0;
    for (int i = 0; i < *total; i++) {
        char *pessoa = (char *)pBuffer + sizeof(int) * 5 + i * 84;
        if (strcmp(pessoa, nome) == 0) {
            printf("\nPessoa %d:\n", i+1);
            printf("Nome: %s\n", pessoa);
            printf("Idade: %d\n", *(int *)(pessoa + 40));
            printf("Email: %s\n", pessoa + 44);
            encontrados++;
        }
    }

    if (!encontrados) {
        printf("Nenhuma pessoa encontrada!\n");
    }
}

void listarPessoas() {
    int *total = (int *)pBuffer;
    if (*total == 0) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
    }

    for (int i = 0; i < *total; i++) {
        char *pessoa = (char *)pBuffer + sizeof(int) * 5 + i * 84;
        printf("\nPessoa %d:\n", i+1);
        printf("Nome: %s\n", pessoa);
        printf("Idade: %d\n", *(int *)(pessoa + 40));
        printf("Email: %s\n", pessoa + 44);
    }
}
