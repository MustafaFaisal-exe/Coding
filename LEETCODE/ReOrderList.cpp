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
    void traverse(ListNode* end, ListNode* prev, ListNode*& start, bool& finish) {
        if (finish){
            return;
        }
        if (end) { 
             traverse(end->next, end, start, finish);
             if (finish)
                 return;

            if (!start->next || start->next == end) {
                finish = true;
                return;
            }

            if (prev)
                prev->next = nullptr;

            end->next = start->next;
            start->next = end;

            if (start)
                start = start->next;
                if (start)
                    start = start->next;
            else
                return;
        }   
    }

    void reorderList(ListNode* head) {
        ListNode* start = head;
        ListNode* prev = nullptr;
        bool finish = false;
        traverse(head, prev, start, finish);
    }
};