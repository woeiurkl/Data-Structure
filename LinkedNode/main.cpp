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
		cout << " (" << this << ") " << item << " [" << next << "]" << endl;
	}

	void setNext(Node* node)
	{
		next = node;
	}

	void recurPrint()
	{
		cout << " (" << this << ") " << this->item << " [" << this->next << "]" << endl;
		if (this->next != nullptr)
			this->next->recurPrint();
	}
};

int main()
{
	Node first(1);
	Node second(2);
	Node third(3);
	Node fourth(4);
	first.setNext(&second);
	second.setNext(&third);
	third.setNext(&fourth);
	first.recurPrint();
}