#include <iostream>
#include <cstring>
#include <cassert>

template <typename T>
class Stack
{
	public:
	
	Stack()
	{
		data_ = nullptr;
		size_ = 0;
	}
	Stack(const Stack& other)
	{
		size_ = other.size();
		data_ = new T[size_];
		std::copy(other.data(), other.data() + size_, data_);
	}
	const Stack& operator=(const Stack& other)
	{
		delete[] data_;
		size_ = other.size();
		data_ = new T[size_];
		std::copy(other.data(), other.data() + size_, data_);

		return *this;	
	}

	~Stack()
	{
		delete[] data_;
	}

	const T* data() const
	{
		return data_;
	}

	T& top()
	{
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

	void push(T val)
	{
		size_++;
		if(empty())
		{
			data_ = new T[size_];
			data_[0] = val;
		}
		else
		{
			T* temp = new T[size_];
			std::copy(data_, data_+size_-1, temp);	
			delete[] data_;
			temp[size_ - 1] = val;
			data_ = temp;
		}
	}

	void emplace(T& val)
	{
		std::cout << "hizi cho tut delat" << std::endl;	
	}

	void pop()
	{
		if(empty())
			return;

		T* temp = new T[size_-1];
		std::copy(data_, data_+size_-1, temp);	
		delete[] data_;
		data_ = temp;
		size_--;
	}

	private:
	T* data_;
	size_t size_;
};

/*
	 * top() // access the top element
	 * empty()
	 * size()
	 * push(T val)
	 * emplace
	 * pop
*/

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
