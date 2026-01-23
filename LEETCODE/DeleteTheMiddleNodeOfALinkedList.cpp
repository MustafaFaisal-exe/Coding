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
    ListNode* deleteMiddle(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        ListNode* prev = nullptr;

        if (!fast->next) {
            head = nullptr;
            return head;
        }

        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;

            fast = fast->next;
            if (fast) {
                fast = fast->next;
            }
        }

        ListNode* tmp = slow;
        if (prev)
            prev->next = slow->next;
        
        delete tmp;
        return head;

    }
};