#include <iostream>
#include <cassert>

template <typename T>
class Queue
{
	public:
	Queue() : size_ {0}, capacity_{0}, data_ {nullptr}, front_{0}, back_{-1}
	{
		
	}

	explicit Queue(size_t size) : size_{size}
	{
		capacity_ = size_;
		data_ = new T[size_];

		if(size_ != 0)
		{
			front_ = data[0];
			back_ = data[size_ - 1];
		}
	}

	Queue(const Queue& other)
	{
		size_ = other.size();
        capacity_ = other.capacity();
        data_ = new T[capacity_];

		if(size_ != 0)
		{
			front_ = data[0];
			back_ = data[size_ - 1];
		}

        memcpy(&data_, other.data(), size_);
	}

	bool empty() const
	{
		return size_ == 0;
	}

	size_t capacity() const
    {
        return capacity_;
    }

    size_t size() const
    {
        return size_;
    }

    T* data() const
    {
        return data_;
    }

	T front() const
	{
		if(empty())
			std::runtime_error("queue is empty");
		return data_[front_];
	}

	T back() const
	{
		if(empty())
			std::runtime_error("queue is empty");
		return data_[back_];
	}

	int pop()
	{
		if(empty())
			std::runtime_error("popping empty queue");

		front_++;
		size_--;

		return data_[front_ - 1];
	}

	const Queue& push(T val)
	{
		int COEFF = 2;
        size_t newCapacity;
        if (capacity_ == 0)
            newCapacity = 1;
        else
            newCapacity = capacity_ * COEFF;

        if (size_ < capacity_)
        {
            data_[size_] = val;
            size_++;
        }
        else
        {
            if (size_ != 0)
            {
                T* temp = new T[newCapacity];
                for (size_t i = 0; i < size_; ++i)
                {
                    temp[i] = data_[i];
                }

                temp[size_] = val;

                delete data_;
                data_ = temp;
            }
            else
            {
                delete data_;
                data_ = new T[1];
                data_[0] = val;
            }

            capacity_ = newCapacity;
            size_++;
        }

		back_++;

		return *this;
	}

	~Queue()
	{
		delete[] data_;
	}

	private:
	int front_;
	int back_;
	size_t size_;
	size_t capacity_;
	T* data_;	
};

void PushTest()
{
	Queue<int> first;
	for(int i = 1; i <= 100000; i++)
		first.push(i);

	assert(first.size() == 100000);

	for(int i = 1; i <= 100000 ; i++)
	{
		std::cout << first.front() << std::endl;
		assert(first.front() == i);
		first.pop();
	}

	assert(first.size() == 0);
}

void PopTest()
{
	Queue<int> first;

	assert(first.size() == 0 && first.capacity() == 0);

	for(int i = 1; i <= 100000; i++)
	{
		first.push(i);
		assert(first.back() == i);
	}

	assert(first.size() == 100000);

	for(int i = 1; i <= 100000; i++)
		first.pop();

	assert(first.size() == 0);
}

int main()
{
	PushTest();
	PopTest();
	return 0;
}
