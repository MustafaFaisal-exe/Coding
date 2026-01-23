/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    void traverse(ListNode*& head, ListNode*& prev, ListNode*& curr, int& n) {
        if (curr) {
            traverse(head, curr, curr->next, n);
            --n;
            if (n == 0) {
                if (curr == head) {
                    ListNode* tmp = curr;
                    head = head->next;
                    delete tmp;
                } else {
                    ListNode* tmp = curr;
                    prev->next = curr->next;
                    delete tmp;
                }
            }
        }
    }

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        traverse(head, prev, head, n);
        return head; 
    }
};