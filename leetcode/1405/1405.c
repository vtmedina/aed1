#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// estrutura para guardar quantas vezes ainda podemos usar a letra e qual é o caractere
typedef struct {
    int count;
    char ch;
} Item;

// função para ordenar um vetor de tamanho n de forma decrescente pelo count, o caractere com maior quantidade fica na frente
// essa ordenação simula o comportamento de uma max-heap
void sort(Item *arr, int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = i+1; j < n; j++)
            if(arr[i].count < arr[j].count) {
                Item temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
}

char* longestDiverseString(int a, int b, int c) {
    Item items[3] = {{a, 'a'}, {b, 'b'}, {c, 'c'}}; // vetor com cada caractere e quantidade restante
    char *result = (char*)malloc(200 + 1); // buffer para a string com o resultado
    int len = 0;

    result[0] = '\0';

    while (1) {
        sort(items, 3); \\ garantindo que o caractere com mais quantidade restante esteja em items[0].
        int appended = 0;

        // Percorre os 3 itens, do maior para o menor, guarda o tamanho atual da string, se a quantidade daquela letra acabou, pula para o próximo.
        // Se os dois últimos caracteres da string já forem iguais ao caractere que queremos adicionar, pulamos para o próximo.
        for (int i = 0; i < 3; i++) {
            int l = len;
            if (items[i].count == 0) continue;
            if (len >= 2 && result[len-1] == items[i].ch && result[len-2] == items[i].ch)
                continue;
          
        // Adiciona o caractere escolhido na string e incrementa seu tamanho, atualiza o terminador nulo para manter a string válida.
        // Decrementa a quantidade restante desse caractere, pois ele ja foi usado e marca que adicionamos algum caractere nessa rodada do loop.
            result[len++] = items[i].ch;
            result[len] = '\0';
            items[i].count--;
            appended = 1;
            break;
        }

        if (!appended) break; // nenhum caractere foi adicionado porque violou a regra
    }

    return result;
}
