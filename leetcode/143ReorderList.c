/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    while (head) {
        struct ListNode* next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

struct ListNode* findMiddle(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void mergeLists(struct ListNode* l1, struct ListNode* l2) {
    while (l2) {
        struct ListNode* tmp1 = l1->next;
        struct ListNode* tmp2 = l2->next;
        l1->next = l2;
        l2->next = tmp1;
        l1 = tmp1;
        l2 = tmp2;
    }
}

void reorderList(struct ListNode* head) {
    if (!head || !head->next || !head->next->next) return;

    struct ListNode* mid = findMiddle(head);
    struct ListNode* second = reverseList(mid->next);
    mid->next = NULL;
    mergeLists(head, second);
}
