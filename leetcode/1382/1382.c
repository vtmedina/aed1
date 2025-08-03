/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

static int count_nodes(struct TreeNode* root) {
    if (!root) return 0;
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

static void collect_nodes(struct TreeNode* root, struct TreeNode** arr, int* idx) {
    if (!root) return;
    collect_nodes(root->left, arr, idx);
    arr[(*idx)++] = root;
    collect_nodes(root->right, arr, idx);
}

static struct TreeNode* build_balanced(struct TreeNode** arr, int l, int r) {
    if (l > r) return NULL;
    int m = l + (r - l) / 2;
    struct TreeNode* node = arr[m];
    node->left = build_balanced(arr, l, m - 1);
    node->right = build_balanced(arr, m + 1, r);
    return node;
}

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