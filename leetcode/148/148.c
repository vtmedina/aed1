/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// Função para encontrar o nó do meio e dividir em duas partes
// essa divisão vai permitir ordenadar cada metade pra depois combinarmos elas
// uso de ponteiros pra percorrer a lista só uma vez
struct ListNode* middle(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// função merge para juntar as duas listas (metades) ja ordenadas em ordem crescente
// sempre escolhendo o menor valor entre os primeiros elementos de cada lista
// se uma das listas acabar, ela pega o que sobrou da outra e coloca no final (recursivamente)
// ex: cartas de baralho: podemos pegar sempre a menor carta de cima de cada pilha e colocando na mesa até juntar tudo em ordem
struct ListNode* mergesort(struct ListNode* esq, struct ListNode* dir) {
    if (!esq)
        return dir;
    if (!dir)
        return esq;

    struct ListNode* res = NULL;
    if (esq->val < dir->val) {
        res = esq;
        res->next = mergesort(esq->next, dir);
    } else {
        res = dir;
        res->next = mergesort(esq, dir->next);
    }
    return res;
}

// função principal para ordenar a lista
// 1. verifica se a lista tá vazia ou tem só um elemento
// 2. se não for, ela acha o meio da lista e corta a lista no meio
// 3. ela chama a si mesma pra ordenar cada metade e depois junta as duas metades já ordenadas
// 4. retorna a lista toda organizada do menor pro maior valor
struct ListNode* sortList(struct ListNode* head) {
    // caso base: lista vazia ou com apenas um elemento
    if (head == NULL || head->next == NULL) {
        return head;
    }
    
    // Encontrar o meio da lista
    struct ListNode* mid = middle(head);
    struct ListNode* meioProx = mid->next;
    
    // Dividir a lista em duas partes
    mid->next = NULL;
    
    // Ordenar recursivamente cada metade
    struct ListNode* esq = sortList(head);
    struct ListNode* dir = sortList(meioProx);
    
    // Juntar as duas metades ordenadas
    return mergesort(esq, dir);
}
