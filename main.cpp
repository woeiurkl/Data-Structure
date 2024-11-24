#include <cassert>
#include <iostream>

using namespace std;

template<typename T>
class Stack
{
public:
	Stack(int capacity = 1)
	{
		assert(capacity > 0);
		Resize(capacity);
	}

	~Stack()
	{
		if (stack_) delete[] stack_;
	}

	void Resize(int new_capacity)
	{
		T* new_stack = new T[new_capacity];
		memcpy(new_stack, stack_, sizeof(T) * Size());
		if (stack_) delete[] stack_;
		stack_ = new_stack;
		capacity_ = new_capacity;
	}

	bool IsEmpty() const
	{
		return top_ == -1;
	}

	int Size() const
	{
		return top_ + 1;
	}

	void Print()
	{
		using namespace std;

		for (int i = 0; i < Size(); i++)
			cout << stack_[i];
		cout << endl;
	}

	T& Top() const
	{
		assert(!IsEmpty());

		return stack_[top_];
	}

	void Push(const T& item)
	{
		if (top_ == capacity_ - 1)
			Resize(capacity_ * 2);

		stack_[++top_] = item;
	}

	void Pop()
	{
		assert(!IsEmpty());

		top_--;
	}

private:
	T* stack_ = nullptr;
	int top_ = -1;
	int capacity_ = 0;
};

bool checkBrackets(const string test);
void printChecked(const string test);

int main()
{
	printChecked("()");
	printChecked("[]");
	printChecked("{}");

	printChecked("({[]})");
	printChecked("{[()]}");
	printChecked("((()))");

	printChecked("([)]");
	printChecked("{[}]");
	printChecked("([]");

	printChecked("{[()]}(([])){}");
	printChecked("({[]}{()})");
	printChecked("((())){[]}");

	printChecked("(");
	printChecked(")");

	return 0;
}

bool checkBrackets(const string test)
{
	Stack<char> temp;
	for (int i = 0; i < test.size(); i++)
	{
		if (test[i] == '(' || test[i] == '{' || test[i] == '[')
		{
			temp.Push(test[i]);
		}
		else
		{
			if (temp.IsEmpty())
				return false;
			else if (temp.Top() == '(' && test[i] == ')')
			{
				temp.Pop();
			}
			else if (temp.Top() == '{' && test[i] == '}')
			{
				temp.Pop();
			}
			else if (temp.Top() == '[' && test[i] == ']')
			{
				temp.Pop();
			}
			else
			{
				return false;
			}
		}
	}
	return temp.IsEmpty();
}

void printChecked(const string test)
{
	cout << test << endl;
	if (checkBrackets(test))
		cout << "True" << endl << endl;
	else
		cout << "False" << endl << endl;
}