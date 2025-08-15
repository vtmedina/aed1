//148

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode {
    int val; //declarando valores inteiros
    struct ListNode *prox; //estrutra com ponteiro para ordenação
}

//merge (esquerda, direita)
void sortList(struct ListNode *left, struct ListNode *right){
    if (!left) return right;
    if (!right) return left;

    struct ListNode*res=NULL;
    if(esq->val<dir->val)
    {
        res=left;res->prox=mergesort(left,right->next,right);
    }else{
        res=right;
        res->prox=mergesort(left,right->next);
    }
    return res;
}

struct LisNode* middle(struct ListNode *head){
    struct ListNode*slow=head;
    struct ListNode*fast=head->next;
    while(fast!=NULL && fast!->next!=NULL){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
    }

struct ListNode* sort(struct ListNode* head){
    if(head==NULL || head->next==NULL)
}
}