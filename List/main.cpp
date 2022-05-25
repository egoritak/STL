#include<iostream>
#include <string>
#include <cassert>

using namespace std;

class List
{
	private:
	class Node
	{
		public:
		Node() : value_{0}, next_{nullptr} {}
		Node(int value) : value_ {value}, next_ {nullptr} {}

		int value_;
		Node* next_;	
	};

	Node* head_;
	Node* tail_;

	public:

	List() : head_{nullptr}, tail_{nullptr} {}

	bool empty() { return head_ == nullptr; }

	Node* begin() {return head_;}
	Node* end() {return tail_;}

	Node* find(int target)
	{
		if(empty())
			return nullptr;

		for(Node* p = head_; p != nullptr; p = p->next_)
			if(p->value_ == target)
				return p;

		return nullptr;
	}

	bool exists(int target)
	{
		if(empty())
			return false;

		for(Node* p = head_; p != nullptr; p = p->next_)
			if(p->value_ == target)
				return true;

		return false;
	}

	void push_back(int value_)
	{
		Node* p = new Node(value_);
		if(empty())
		{
			head_ = tail_ = p;	
		}
		tail_->next_ = p;
		tail_ = p;
	}

	void push_front(int value_)
	{
		Node* p = new Node(value_);
		p->next_ = head_;
		head_ = p;
	}

	void removeNext(Node* target)
	{
		if(empty())
			return;
		Node* next_of_next = target->next_->next_;

		delete[] target->next_;

		target->next_ = next_of_next;
	}

	void push(int target, int value)
	{
		if(empty())
			return;

		Node* p = head_;

		while(p != nullptr)
		{
			if(p->value_ == target)
			{
				Node* temp = new Node(value);
				temp->next_ = p->next_;
				p->next_ = temp;
				return;
			}
			p = p->next_;
		}
	}

	void remove(int target)
	{
		if(empty())
			return;
		Node* p = head_;

		if(p->value_ == target)
		{
			Node* next_one = head_->next_;
			delete[] head_;
			head_ = next_one;
			return;
		}

		while(p != nullptr)
		{
			if(p->next_->value_	== target)
			{
				removeNext(p);
				return;
			}
			p = p->next_;
		}
	}

	string toString()
	{
		string result = "";

		Node* p = head_;
		while(p != nullptr)
		{
			result += to_string(p->value_) + " ";
			p = p->next_;
		}

		return result;
	}
};

List* devideList(List myList)
{
	List even;
	List odd;

	for(auto p = myList.begin(); p != nullptr; p = p->next_)
	{
		cout << p->value_ << endl;
		if(p->value_ % 2 == 0)
			even.push_back(p->value_);
		else
			odd.push_back(p->value_);
	}

	List* result = new List[2];
	result[0] = even;
	result[1] = odd;
	return	result; 
}

void PushBackTest()
{
	List myList;

	int pushCount = 1e5;
	for(int i = 1; i <= pushCount; i++)
		myList.push_back(i);

	int size = 0;
	int i = 1;
	for(auto p = myList.begin(); p != nullptr; p = p->next_)
	{
		size++;
		assert(p->value_ == i);
		i++;
	}
	assert(size == pushCount); 
}

void PushFrontTest()
{
	List myList;

	int pushCount = 1e5;
	for(int i = 1; i <= pushCount; i++)
		myList.push_front(i);

	int size = 0;
	int i = pushCount;
	for(auto p = myList.begin(); p != nullptr; p = p->next_)
	{
		size++;
		assert(p->value_ == i);
		i--;
	}
	assert(size == pushCount); 
}
template <typename T> std::string type_name();

void RemoveTest()
{
	List myList;

	int pushCount = 1e5;
	for(int i = 1; i <= pushCount; i++)
	{
		if(i % 2 == 0)
			myList.push_back(1);
		else
			myList.push_back(2);
	}

	for(int i = 1; i <= pushCount/2; i++)
	{
		myList.remove(2);
	}

	int size = 0;
	for(auto p = myList.begin(); p != nullptr; p = p->next_)
	{
		size++;
		assert(p->value_ == 1);
	}
	assert(size == pushCount/2); 
}

int main()
{
	PushBackTest();
	PushFrontTest();
	RemoveTest();
	return 0;
}
