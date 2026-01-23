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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int sum = 0;
        int carry = 0;
        ListNode* tempres = new ListNode ();
        ListNode* result = tempres;
        while (l1 != nullptr && l2 != nullptr) {
            sum = (l1->val + l2->val + carry);
            carry = sum / 10;
            sum = sum % 10; 
            tempres->val = sum;
            if (l1->next != nullptr || l2->next != nullptr) {
                tempres->next = new ListNode();
                tempres = tempres->next;
            }
            l1 = l1->next;
            l2 = l2->next;
        }

        while (l1 != nullptr) {
            sum = l1->val + carry;
            tempres->val = sum % 10;
            carry = sum / 10;
            if (l1->next != nullptr) {
                tempres->next = new ListNode();
                tempres = tempres->next;
            }
            l1 = l1->next;
        }

        while (l2 != nullptr) {
            sum = l2->val + carry;
            tempres->val = sum % 10;
            carry = sum / 10;
            if (l2->next != nullptr) {
                tempres->next = new ListNode();
                tempres = tempres->next;
            }
            l2 = l2->next;
        }

        if (carry) {
            ListNode* tmp = new ListNode(1);
            tempres->next = tmp;
        } 

        return result;
    }
};