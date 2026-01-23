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
    ListNode* swapPairs(ListNode* head) {
        ListNode* tempHead = head;
        ListNode* prev = nullptr;
        while (tempHead != nullptr && tempHead->next != nullptr) {
            //head case
            if (tempHead == head && tempHead->next != nullptr) {
                head = tempHead->next;
                ListNode* tmp = tempHead->next->next;
                tempHead->next->next = tempHead;
                tempHead->next = tmp;
                prev = tempHead;
                tempHead = tempHead->next;
            } else {
                if (prev && tempHead && tempHead->next) {
                    prev->next = tempHead->next;
                    ListNode* tmp = tempHead->next->next;
                    tempHead->next->next = tempHead;
                    tempHead->next = tmp;
                    prev = tempHead;
                    tempHead = tempHead->next;
                }
            }
        }
        return head;
    }
};