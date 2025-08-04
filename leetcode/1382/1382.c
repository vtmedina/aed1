// O algoritmo vai percorrer uma árvore desbalanceada em ordem, armazenando os nós em um array, resultando em um array ordenado e conrtuir uma nova árvore onde:
// o elemento do meio do array se torna a raiz, os elementos à esquerda do meio formam a subárvore esquerda, os elementos à direita do meio formam a subárvore direita

// Definindo a estrutura de um nó da árvore
// A estrutura guarda o valor armazenado no nó, um ponteiro para o filho da esquerda e um para o da direita
struct TreeNode {
     int val;
     struct TreeNode *left;
     struct TreeNode *right;
};

// Função para fazer a contagem dos nós
// se a arvore estiver vazia retorna 0, caso contrário retorna 1
static int count_nodes(struct TreeNode* root) {
    if (!root) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right); // se houver nós retorna 1 + contagem dos nós na subárvore esquerda e direita
}

// Coletando os nós
// Percorremos a árvore na ordem esquerda-raiz-direita e armazena os nós em um array
// Root (nó atual), arr (array), idx (ponteiro para índice atual do array)
static void collect_nodes(struct TreeNode* root, struct TreeNode** arr, int* idx) {
    if (!root) return;
    collect_nodes(root->left, arr, idx);
    arr[(*idx)++] = root;
    collect_nodes(root->right, arr, idx);
}

// Construindo a arvore balanceada
// Constrói uma árvore balanceada a partir de um array de nós ordenados
static struct TreeNode* build_balanced(struct TreeNode** arr, int l, int r) {
    if (l > r) return NULL;
    int m = l + (r - l) / 2;
    struct TreeNode* node = arr[m];
    node->left = build_balanced(arr, l, m - 1);
    node->right = build_balanced(arr, m + 1, r);
    return node;
}

// Função principal
// 1. verifica se a árvore está vazia e conta o número total de nós e aloca um array para armazenar todos os nós
// 2. coleta todos os nós em ordem no array e  onstrói uma nova árvore balanceada a partir do array
// 5. libera a memória do array retorna a nova raiz balanceada
struct TreeNode* balanceBST(struct TreeNode* root) {
    if (!root) return NULL;
    int n = count_nodes(root);
    struct TreeNode** nodes = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    if (!nodes) return NULL;
    
    int idx = 0;
    collect_nodes(root, nodes, &idx);
    struct TreeNode* new_root = build_balanced(nodes, 0, n - 1);
    
    free(nodes);
    return new_root;
}
