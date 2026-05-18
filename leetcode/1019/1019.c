#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int* nextLargerNodes(struct ListNode* head, int* returnSize) {
    int nums[10000];
    int n = 0;
    
    while (head) {
        nums[n++] = head->val;
        head = head->next;
    }
    
    int* res = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        res[i] = 0;
    }
    
    int stack[10000];
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        while (top != -1 && nums[i] > nums[stack[top]]) {
            res[stack[top--]] = nums[i];
        }
        stack[++top] = i;
    }
    
    *returnSize = n;
    return res;
}

int main() {
    struct ListNode n1, n2, n3;
    n1.val = 2;
    n1.next = &n2;
    n2.val = 1;
    n2.next = &n3;
    n3.val = 5;
    n3.next = NULL;
    
    int returnSize;
    int* result = nextLargerNodes(&n1, &returnSize);
    
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    
    free(result);
    return 0;
}