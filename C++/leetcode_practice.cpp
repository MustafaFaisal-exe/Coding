#include<iostream>
#include<cmath>
#include<vector>
#include<list>
#include<stack>
#include<string>
#include<iomanip>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
            cout << "Start: " << start->val << endl;
            cout << "End: " << end->val << endl;
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

// helper to print list (for debugging)
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

int main() {
    // Build input list: [1,2,3,4]
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);

    cout << "Before reorder:" << endl;
    printList(head);

    Solution sol;
    sol.reorderList(head);

    cout << "\nAfter reorder:" << endl;
    printList(head);

    return 0;
}