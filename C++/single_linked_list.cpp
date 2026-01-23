#include<iostream>
#include <string>
using namespace std;

class LinkedList {
private: 
	class Node {
	public:
		int ID;
		string type;
		Node* next;
		Node() : ID(-1), type(""), next(nullptr) {}
		Node(int IDp, string typeP, Node* nextP) {
			ID = IDp;
			type = typeP;
			next = nextP;
		}
	};

	Node* head;

public:
	LinkedList() : head(nullptr) {}

	void addStart(int IDp, string typeP);
	void addEnd(int IDp, string typeP);
	bool addMiddle(int IDp, int targetID, string typeP);
	void Detach(int IDp);
	bool search(int IDp);
	void display();
	int countCompart();
	void Swap(int ID1, int ID2);

};

int main() {
	LinkedList train;

	int choice = -1;
	while (choice != 0) {
		cout << "\n\n=== Thomas & Friends: Train Compartment Manager ===\n";
		cout << "1. Attach Compartment at Start (VIP)\n";
		cout << "2. Attach Compartment at End (Normal)\n";
		cout << "3. Attach Compartment After a Specific Compartment\n";
		cout << "4. Detach Compartment\n";
		cout << "5. Search Compartment\n";
		cout << "6. Display Train\n";
		cout << "7. Count Compartments\n";
		cout << "8. Swap Two Compartments\n";
		cout << "0 Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

        if (choice == 1) {
            int ID;
    		string type;
    		cout << "Enter Compartment ID: ";
    		cin >> ID;
    		cout << "Enter Cargo Type (Passenger, Coal, Mail, Toys): ";
            cin >> type;
    		train.addStart(ID, type);
    		cout << "Compartment " << ID << " (" << type << ") attached at start\n";
        } else if (choice == 2) {
            int ID;
    		string type;
    		cout << "Enter Compartment ID: ";
    		cin >> ID;
    		cout << "Enter Cargo Type (Passenger, Coal, Mail, Toys): ";
            cin >> type;
    		train.addEnd(ID, type);
    		cout << "Compartment " << ID << " (" << type << ") attached at end\n";

        } else if (choice == 3) {
            int ID, targetID;
    		string type;
    		cout << "Enter Target Compartment ID: ";
    		cin >> targetID;
    		cout << "Enter New Compartment ID: ";
    		cin >> ID;
    		cout << "Enter Cargo Type (Passenger, Coal, Mail, Toys): ";
            cin >> type;
    		if (train.addMiddle(ID, targetID, type)) {
                cout << "Compartment " << ID << " (" << type << ") attached at " << targetID << endl;
            } else {
                cout << "Target compartment " << targetID << " not found\n\n";
            }

        } else if (choice == 4) {
            int ID;
    		cout << "Enter Compartment ID to detach: ";
    		cin >> ID;
    		train.Detach(ID);
    		cout << "Compartment " << ID << " detached\n";

        } else if (choice == 5) {
            int ID;
    		cout << "Enter Compartment ID to search: ";
    		cin >> ID;
    		if (train.search(ID)) {
    			cout << "Compartment " << ID << " is in the train\n";
    		}
    		else {
    			cout << "Compartment " << ID << " is not in the train\n";
    		}

        } else if (choice == 6) {
            train.display();
        } else if (choice == 7) {
            cout << "Total Compartments: " << train.countCompart() << endl;
        } else if (choice == 8) {
            int ID1;
    		int ID2;
    		cout << "Enter first Compartment ID: ";
    		cin >> ID1;
    		cout << "Enter second Compartment ID: ";
    		cin >> ID2;
    		train.Swap(ID1, ID2);
    		cout << "Compartments  " << ID1 << " and " << ID2 << " swapped\n";
        } else {
            cout << "EXIT\n";
        }

	}

}

void LinkedList::addStart(int IDp, string typeP)
{
	if (!head) {
		head = new Node(IDp, typeP, nullptr);
	}
	else {
		head = new Node(IDp, typeP, head);
	}
}

void LinkedList::addEnd(int IDp, string typeP)
{
	if (!head) {
		head = new Node(IDp, typeP, nullptr);
	}
	else {
		Node* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new Node(IDp, typeP, nullptr);
	}
}

bool LinkedList::addMiddle(int IDp, int targetID, string typeP)
{
	if (!head) {
		head = new Node(IDp, typeP, nullptr);
	}
	else {
		Node* temp = head;
		bool found = 0;
		while (!found && temp) {
			if (temp->ID == targetID) {
				found = 1;
			}
			else {
				temp = temp->next;
			}
		}

		if (!found) {
			return found;
		}
		else {
			temp->next = new Node(IDp, typeP, temp->next);
            return found;
		}
	}
}

void LinkedList::Detach(int IDp)
{
	if (!head) {
		cout << "Linked list aleady empty!\n\n";
		return;
	} else if (head->ID == IDp) {
        Node* temp = head;
        head = head->next;
        delete temp;
    } else {
		Node* current = head;
		Node* prev = nullptr;
		bool found = 0;
		while (!found) {
			if (current->ID == IDp) {
				found = 1;
			}
			else {
				prev = current;
				current = current->next;
			}
		}
		prev->next = current->next;
		delete current;
	}
}

bool LinkedList::search(int IDp)
{
	Node* temp = head;
	while (temp) {
		if (temp->ID == IDp) {
			return true;
		}
        temp = temp->next;
	}
	return false;
}

void LinkedList::display()
{
	Node* temp = head;
	cout << "\n\nTrain Composition:\n";
	while (temp) {
		cout << temp->ID << " " << "(" << temp->type << ") -> ";
        temp = temp->next;
	}
	cout << " NULL\n\n";
}

int LinkedList::countCompart()
{
	int count = 0;

	Node* temp = head;
	while (temp) {
		++count;
        temp = temp->next;
	}

	return count;
}

void LinkedList::Swap(int ID1, int ID2) {
    Node* prev1 = nullptr;
    Node* prev2 = nullptr;
    Node* curr1 = head;
    Node* curr2 = head;

    while (curr1 && curr1->ID != ID1) {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    while (curr2 && curr2->ID != ID2) {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (!curr1 || !curr2) {
        cout << "One or both compartments not found\n";
        return;
    }

    if (prev1) prev1->next = curr2;
    else head = curr2;

    if (prev2) prev2->next = curr1;
    else head = curr1;

    Node* temp = curr1->next;
    curr1->next = curr2->next;
    curr2->next = temp;
}