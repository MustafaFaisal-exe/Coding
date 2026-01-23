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
    void rotate(ListNode*& head, ListNode* node) {
        ListNode* prev = nullptr;

        while (node && node->next) {
            prev = node;
            node = node->next;
        }

        node->next = head;
        if (prev)
            prev->next = nullptr;
        else
            head->next = nullptr;

        head = node;
    }

    ListNode* rotateRight(ListNode* head, int k) {

        int size = 0;
        ListNode* tmp = head;
        while (tmp) {
            ++size;
            tmp = tmp->next;
        }

        if (size)
            k %= size;

        for (int i = 0; i < k; i++) {
             ListNode* node = head;
             if (head)
                 rotate(head, node);
        }

       return head;
    }
};