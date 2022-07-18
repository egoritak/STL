#include <iostream>
#include <cstring>
#include <cassert>

template <typename T>
class Stack
{
	public:
	Stack() : data_{nullptr}, size_ {0}, capacity_{0}
	{
	}

	Stack(const Stack& other) : size_ {other.size()}, capacity_ {other.capacity()}
	{
		data_ = new T[capacity_];
		std::copy(other.data(), other.data() + size_, data_);
	}

	const Stack& operator=(const Stack& other)
	{
		if(data_ == other.data())
			return *this;

		delete[] data_;
		size_ = other.size();
		capacity_ = other.capacity();
		data_ = new T[capacity_];
		std::copy(other.data(), other.data() + size_, data_);

		return *this;	
	}

	~Stack()
	{
		delete[] data_;
	}

	bool isFull() const 
	{
		return size_ == capacity_;
	}

	const T* data() const
	{
		return data_;
	}

	T& top()
	{
		if(size_ == 0)
			std::runtime_error("stack is empty");

		return data_[size_ - 1];		
	}

	bool empty() const
	{
		return size_ == 0;
	}

	size_t size() const
	{
		return size_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	void push(T val)
	{
		if(isFull())
		{
			int COEFF = 2;
			if(capacity_ == 0)
				capacity_ = 1;
			else
				capacity_ *= COEFF;

			T* temp = new T[capacity_];

			for(int i = 0; i < size_; i++)
				temp[i] = data_[i];
			
			delete[] data_;

			data_ = temp;
		}	
		
		data_[size_++] = val;
	}

	T pop()
	{
		if(empty())
		{
			std::runtime_error("popping empty stack");
		}

		return data_[--size_];
	}

	private:
	T* data_;
	size_t size_;
	size_t capacity_;
};

void CopyConstructorTest()
{
	Stack<int> first;
	for(int i = 0; i < 1e5; i++)
		first.push(i);

	Stack<int> second(first);

	assert(first.size() == second.size());

	for(int i = 0; i < 1e5; i++)
	{
		assert(first.top() == second.top());
		first.pop();
		second.pop();
	}

}

void EqualTest()
{
	Stack<int> first;
	Stack<int> second = first;
	assert(first.empty() || second.empty() == false);
	for(int i = 0; i < 1e5; i++)
		first.push(i);

	second = first;

	assert(first.size() == second.size());

	for(int i = 0; i < 1e5; i++)
	{
		assert(first.top() == second.top());
		first.pop();
		second.pop();
	}

}

void PushTest()
{
	Stack<int> first;
	for(int i = 1; i <= 100000; i++)
		first.push(i);

	assert(first.size() == 100000);	

	for(int i = 100000; i >= 1 ; i--)
	{
		assert(first.top() == i);
		first.pop();
	}
}

void PopTest()
{
	Stack<int> first;
	for(int i = 1; i <= 100000; i++)
		first.push(i);

	assert(first.size() == 100000);	

	for(int i = 1; i <= 100000; i++)
		first.pop();

	assert(first.size() == 0);
}

int main()
{
	PushTest();
	PopTest();
	CopyConstructorTest();
	EqualTest();

	return 0;
}
