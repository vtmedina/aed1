/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    if (!head || left == right)
        return head;

    struct ListNode dummy;
    dummy.next = head;

    struct ListNode* beforeReverse = &dummy;
    struct ListNode* startReverse = head;

    for (int i = 1; i < left; i++) {
        beforeReverse = beforeReverse->next;
        startReverse = startReverse->next;
    }

    struct ListNode* prev = NULL;
    struct ListNode* curr = startReverse;

    for (int i = 0; i <= right - left; i++) {
        struct ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }

    beforeReverse->next = prev;
    startReverse->next = curr;

    return dummy.next;
}
