#include<iostream>
#include <string>
#include <tuple>

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

int main()
{
	List myList;

	for(int i = 1; i <= 10; i++)
		myList.push_back(i);

	for(int i = 0; i >= -12; i--)
		myList.push_front(i);

	for(int i = 11; i <= 12; i++)
		myList.push_back(i);

	cout << myList.toString() << endl;

	myList.remove(0);

	cout << myList.toString() << endl;

	myList.push(-1, 0);

	cout << myList.toString() << endl;

	if(myList.exists(-2))
		cout << "-2 exists" << endl;

	myList.find(-2)->value_ = 9;

	cout << myList.toString() << endl;

	List* devided = devideList(myList);

	cout << devided[0].toString() << endl;
	cout << devided[1].toString() << endl;

	return 0;
}
