#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *pBuffer;

void adicionarPessoa();
void removerPessoa();
void buscarPessoa();
void listarPessoas();

int main() {
    // Alocando buffer de 6 inteiros + 5 pessoas (84 bytes cada) + 40 bytes para busca
    // Total: 6 * 4 + 5 * 84 + 40 = 24 + 420 + 40 = 484 bytes
    pBuffer = malloc(sizeof(int) * 6 + 84 * 5 + 40);
    if (!pBuffer) return 1;

    // Organizando o buffer
    *(int *)pBuffer = 0; // [0-3] total de pessoas                   
    *(int *)((char *)pBuffer + 4) = 5; //[4-7] capacidade
    *(int *)((char *)pBuffer + 8) = sizeof(int) * 6 + 84 * 5 + 40; // [8-11] tamanho total do buffer
    *(int *)((char *)pBuffer + 12) = 0; // [12-15] indice de busca  
    *(int *)((char *)pBuffer + 16) = 0; // [16-19] indice para remover  
    int *alt = (int *)((char *)pBuffer + 20); // [20-23] menu de opcoes
    
    // [24-419] (reservado para 5 pessoas, cada uma com 84 bytes: 40 para nome, 4 para idade, 40 para email)
    // [420-459] (reservado para busca de nome, 40 bytes)
    // [460-483] (reservado para outros dados, se necessário)
    
    do {
        printf("\nMenu:\n");
        printf("1- Adicionar Pessoa\n");
        printf("2- Remover Pessoa\n");
        printf("3- Buscar Pessoa\n");
        printf("4- Listar todos\n");
        printf("5- Sair\n");
        printf("Opcao: ");
        scanf("%d%*c", alt);

        switch (*alt) {
            case 1: 
                adicionarPessoa(); break;
            case 2: 
                removerPessoa(); break;
            case 3: 
                buscarPessoa(); break;
            case 4: 
                listarPessoas(); break;
            case 5: 
                printf("Saindo...\n"); break;
            default: 
                printf("Opcao invalida!\n");
        }
    } while (*alt != 5);

    free(pBuffer); // Liberando o buffer alocado
    return 0;
}

void adicionarPessoa() {
    int *total = (int *)pBuffer;
    int *capacidade = (int *)((char *)pBuffer + 4);
    
    if (*total >= *capacidade) {
        printf("Buffer cheio!\n");
        return;
    }

    char *novaPessoa = (char *)pBuffer + sizeof(int) * 6 + (*total) * 84;

    printf("Nome: ");
    fgets(novaPessoa, 40, stdin);
    novaPessoa[strcspn(novaPessoa, "\n")] = '\0';

    printf("Idade: ");
    char *ptrIdade = novaPessoa + 40;
    scanf("%d", (int *)ptrIdade);
    while (getchar() != '\n');

    printf("Email: ");
    char *ptrEmail = novaPessoa + 44;
    fgets(ptrEmail, 40, stdin);
    ptrEmail[strcspn(ptrEmail, "\n")] = '\0';

    (*total)++;
    printf("Pessoa adicionada com sucesso!\n");
}

void removerPessoa() {
    int *total = (int *)pBuffer;
    int *indice = (int *)((char *)pBuffer + 16);
    if (*total == 0) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
    }

    listarPessoas();
    printf("Indice para remover (1-%d): ", *total);

    scanf("%d%*c", indice);

    if (*indice < 1 || *indice > *total) {
        printf("Indice invalido!\n");
        return;
    }

    char *alvo = (char *)pBuffer + sizeof(int) * 6 + (*indice-1) * 84;
    char *proxima = alvo + 84;

    // Desloca as pessoas restantes para preencher o espaço, movendo os dados de cada pessoa para a posição anterior
    memmove(alvo, proxima, (*total - *indice) * 84);
    (*total)--;

    printf("Pessoa removida com sucesso!\n");
}

void buscarPessoa() {
    int *total = (int *)pBuffer;
    if (*total == 0) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
    }

    char *nomeBusca = (char *)pBuffer + sizeof(int) * 6 + 84 * 5;

    printf("Nome para buscar: ");
    fgets(nomeBusca, 40, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int *encontrados = (int *)((char *)pBuffer + 16);
    *encontrados = 0;

    int *indice = (int *)((char *)pBuffer + 12);
    for (*indice = 0; *indice < *total; (*indice)++) {
        char *pessoa = (char *)pBuffer + sizeof(int) * 6 + (*indice) * 84;

        if (strcmp(pessoa, nomeBusca) == 0) {
            printf("\nPessoa %d:\n", (*indice)+1);
            printf("Nome: %s\n", pessoa);
            printf("Idade: %d\n", *(int *)(pessoa + 40));
            printf("Email: %s\n", pessoa + 44);
            (*encontrados)++;
        }
    }

    if (*encontrados == 0) {
        printf("Nenhuma pessoa com o nome '%s' encontrada.\n", nomeBusca);
    }
}

void listarPessoas() {
    int *total = (int *)pBuffer;
    if (*total == 0) {
        printf("Nenhuma pessoa cadastrada!\n");
        return;
    }

    int *i = (int *)((char *)pBuffer + 12);
    for (*i = 0; *i < *total; (*i)++) {
        char *pessoa = (char *)pBuffer + sizeof(int) * 6 + (*i) * 84;
        printf("\nPessoa %d:\n", (*i)+1);
        printf("Nome: %s\n", pessoa);
        printf("Idade: %d\n", *(int *)(pessoa + 40));
        printf("Email: %s\n", pessoa + 44);
    }
}