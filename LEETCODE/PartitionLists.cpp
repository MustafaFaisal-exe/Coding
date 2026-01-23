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
    ListNode* partition(ListNode* head, int x) {
        queue<ListNode*> less;
        queue<ListNode*> great;

        ListNode* it = head;

        while (it) {
            if (it->val < x) {
                less.push(it);
            } else {
                great.push(it);
            }
            it = it->next;
        }

        ListNode* tmp = new ListNode();
        ListNode* tmpHead = tmp;

        while (!less.empty()) {
            ListNode* next = new ListNode(less.front()->val);
            tmp->next = next;
            tmp = next;
            less.pop();
        }

        while (!great.empty()) {
            ListNode* next = new ListNode(great.front()->val);
            tmp->next = next;
            tmp = next;
            great.pop();
        }

        ListNode* del = tmpHead;
        tmpHead = tmpHead->next;
        delete del;

        return tmpHead;
    }
};