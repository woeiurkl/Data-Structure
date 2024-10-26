#include <iostream>

using namespace std;

class Node
{
public:
	int item = 0;
	Node* next = nullptr;

	Node() {}
	Node(int num) : item(num) {}

	void printNode()
	{
		cout << "(" << this << ") " << item << " [" << next << "]" << endl;
	}

	void setNext(Node* node)
	{
		next = node;
	}

	void recurPrint()
	{
		cout << "(" << this << ") " << this->item << " [" << this->next << "]" << endl;
		if (this->next != nullptr)
			this->next->recurPrint();
	}

	void deleteNode()
	{
		Node* current = this;

		while (current)
		{
			Node* temp = current;
			cout << "Delete ";
			temp->printNode();
			current = current->next;
			delete temp;
		}
	}
};

int main()
{
	Node* first = new Node(1);
	Node* second = new Node(2);
	Node* third = new Node(3);
	Node* fourth = new Node(4);

	first->setNext(second);
	second->setNext(third);
	third->setNext(fourth);

	first->recurPrint();

	first->deleteNode();

	first->printNode();
}
