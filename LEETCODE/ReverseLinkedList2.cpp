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
    void reverse(ListNode*& head, ListNode*& prev, ListNode*& curr) {
        if (curr) {
            head = curr;
            reverse(head, curr, curr->next);
            curr->next = prev;  
        }
    }

    void printList(ListNode* head) {
        ListNode* curr = head;
        while (curr != nullptr) {
            cout << curr->val;
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
        cout << endl;
    }

    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode* lefttmp = new ListNode();
        ListNode* leftHead = lefttmp;

        ListNode* righttmp = new ListNode();
        ListNode* rightHead = righttmp;

        ListNode* swaptmp = new ListNode();
        ListNode* swapHead = swaptmp;

        ListNode* it = head;
        int counter = 1;

        while (it) {
            if (counter < left) {
                ListNode* next = new ListNode(it->val);
                lefttmp->next = next;
                lefttmp = next;
                ++counter;
                it = it->next;
            } else if (counter > right) {
                ListNode* next = new ListNode(it->val);
                righttmp->next = next;
                righttmp = next;
                ++counter;
                it = it->next;
            } else {
                ListNode* next = new ListNode(it->val);
                swaptmp->next = next;
                swaptmp = next;
                ++counter;
                it = it->next;
            }
        }

        ListNode* delSwap = swapHead;
        swapHead = swapHead->next;
        delete delSwap;

        ListNode* prev = nullptr;
        ListNode* curr = swapHead;
        swaptmp = swapHead;

        reverse(swapHead, prev, curr);

        lefttmp->next = swapHead;
        rightHead = rightHead->next;
        swaptmp->next = rightHead;

        ListNode* delLeft = leftHead;
        leftHead = leftHead->next;
        delete delLeft;

        return leftHead;

    }
};