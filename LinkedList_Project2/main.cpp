#include <iostream>

using namespace std;

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* link;
};

template <class Type>
class linkedListIterator
{
public:
	linkedListIterator()
	{
		current = nullptr;
	}

	linkedListIterator(nodeType<Type>* ptr)
	{
		current = ptr;
	}

	Type operator*()
	{
		return current->info;
	}

	linkedListIterator<Type> operator++()
	{
		current = current->link;
		return *this;
	}

	bool operator==(const linkedListIterator<Type>& right) const
	{
		return (current == right.current);
	}

	bool operator!=(const linkedListIterator<Type>& right) const
	{
		return (current != right.current);
	}

private:
	nodeType<Type>* current;
};

template <class Type>
class linkedListType
{
public:
	const linkedListType<Type>& operator= (const linkedListType<Type>& otherList)
	{
		if (this != &otherList)
		{
			copyList(otherList);
		}
		return *this;
	}
	void initializeList()
	{
		destroyList();
	}

	bool isEmptyList() const
	{
		return (first == nullptr);
	}

	void print() const
	{
		nodeType<Type>* current;
		current = first;

		while (current != nullptr)
		{
			cout << current->info << " ";
			current = current->link;
		}
	}

	int length() const
	{
		return count;
	}

	void destroyList()
	{
		nodeType<Type>* temp;

		while (first != nullptr)
		{
			temp = first;
			first = first->link;
			delete temp;
		}
		last = nullptr;
		count = 0;
	}

	Type front() const
	{
		assert(first != nullptr);
		return first->info;
	}

	Type back() const
	{
		assert(last != nullptr);
		return last->info;
	}

	virtual bool search(const Type& searchItem) const = 0;
	
	virtual void insertFirst(const Type& newItem) = 0;
	
	virtual void insertLast(const Type& newItem) = 0;
	
	virtual void deleteNode(const Type& deleteItem) = 0;

	// Project 2

	virtual void delSmallest() = 0;

	virtual void deleteAllbyInfo(const Type& deleteItem) = 0;
	
	linkedListIterator<Type> begin()
	{
		linkedListIterator<Type> temp(first);
		return temp;
	}

	linkedListIterator<Type> end()
	{
		linkedListIterator<Type> temp(nullptr);
		return temp;
	}

	linkedListType()
	{
		first = nullptr;
		last = nullptr;
		count = 0;
	}

	linkedListType(const linkedListType<Type>& otherList)
	{
		first = nullptr;
		copyList(otherList);
	}

	~linkedListType()
	{
		destroyList();
	}

protected:
	int count;
	nodeType<Type>* first;
	nodeType<Type>* last;
private:
	void copyList(const linkedListType<Type>& otherList)
	{
		nodeType<Type>* newNode;
		nodeType<Type>* current;

		if (first != nullptr)	destroyList();

		if (otherList.first == nullptr)
		{
			first = nullptr;
			last = nullptr;
			count = 0;
		}
		else
		{
			current = otherList.first;
			count = otherList.count;

			first = new nodeType<Type>;

			first->info = current->info;
			first->link = nullptr;

			last = first;
			
			current = current->link;

			while (current != nullptr)
			{
				newNode = new nodeType<Type>;
				newNode->info = current->info;
				newNode->link = nullptr;

				last->link = newNode;
				last = newNode;

				current = current->link;
			}
		}
	}
};


template <class Type>
class unorderedLinkedList : public linkedListType<Type>
{
public:
	bool search(const Type& searchItem) const
	{
		nodeType<Type>* current;
		bool found = false;

		current = this->first;

		while (current != nullptr && !found)
		{
			if (current->info == searchItem)
				found = true;
			else
				current = current->link;
		}

		return found;
	}

	void insertFirst(const Type& newItem)
	{
		nodeType<Type>* newNode;
		newNode = new nodeType<Type>;

		newNode->info = newItem;
		newNode->link = this->first;

		this->first = newNode;
		this->count++;

		if (this->last == nullptr)
			this->last = newNode;
	}

	void insertLast(const Type& newItem)
	{
		nodeType<Type>* newNode;
		newNode = new nodeType<Type>;

		newNode->info = newItem;
		newNode->link = nullptr;

		if (this->first == nullptr)
		{
			this->first = newNode;
			this->last = newNode;
			this->count++;
		}
		else
		{
			this->last->link = newNode;
			this->last = newNode;
			this->count++;
		}
	}

	void deleteNode(const Type& deleteItem)
	{
		nodeType<Type>* current;
		nodeType<Type>* trailCurrent;
		bool found;

		if (this->first == nullptr)
			cout << "Cannot delete from an empty list." << endl;
		else
		{
			if (this->first->info == deleteItem)
			{
				current = this->first;
				this->first = this->first->link;
				this->count--;

				if (this->first == nullptr)
					this->last = nullptr;

				delete current;
			}
			else
			{
				found = false;
				trailCurrent = this->first;

				current = this->first->link;

				while (current != nullptr && !found)
				{
					if (current->info != deleteItem)
					{
						trailCurrent = current;
						current = current->link;
					}
					else
						found = true;
				}

				if (found)
				{
					trailCurrent->link = current->link;
					this->count--;

					if (this->last == current)
						this->last = trailCurrent;

					delete current;
				}
				else
					cout << "The item to be deleted is not in the list." << endl;
			}
		}
	}
};

int main()
{
	
}
