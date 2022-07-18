#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

template <typename T>
class Vector
{
public:

    Vector() : size_{ 0 }, capacity_{ 0 } {}

    explicit Vector(size_t size) : size_{ size }, capacity_{ size }
    {
        data_ = new T[size];

        fill(data_, data_ + size_, 0);

        size_ = size;
        capacity_ = size;
    }

    Vector(const Vector& other)
    {
        size_ = other.size();
        capacity_ = other.capacity();
        data_ = new T[capacity_];

        memcpy(&data_, other.data(), size_);
    }

    ~Vector()
    {
        delete[] data_;
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

    T& operator[](size_t i) const
    {
        return data_[i];
    }

    Vector& operator=(const Vector& other)
    {
        if (data_ != other.data())
        {
            delete[] data_;
            size_ = other.size();
            capacity_ = other.capacity();
            data_ = new T[capacity_];

            for (size_t i = 0; i < other.size(); i++)
                data_[i] = other[i];
        }
        return *this;
    }

    Vector& operator=(initializer_list<T> ilist)
    {
        delete[] data_;
        size_ = ilist.size();
        data_ = new T[size_];
        for (size_t i = 0; i < size_; i++)
        {
            data_[i] = *(ilist.begin() + i);
        }

        return *this;
    }

	bool isFull() const
	{
		return size_ == capacity_;
	}

	void push_back(T val)
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

    void clear()
    {
        size_ = 0;
        capacity_ = 0;
        delete[] data_;
        data_ = nullptr;
    }

    string toString()
    {
        string str;
        std::ostringstream os;
        for (int i = 0; i < size_; i++) {
            os << data_[i];
        }
        return string(os.str());
    }

private:
    T* data_ = nullptr;
    size_t size_;
    size_t capacity_;
};

void PushBackTest() {
    Vector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
        assert(v.size() == i);
    }
}

void ClearTest() {
    Vector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
    }

    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == 0);
    assert(v.data() == nullptr);
}


void EqualTest() {
    Vector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
    }
    Vector<int> v1;
    v1 = v;

    assert(v.size() == v1.size());
    assert(v.capacity() == v1.capacity());
    assert(v.data() != v1.data());

    for (size_t i = 0; i <= v.size(); ++i)
        assert(v[i] == v1[i]);

    v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

    for (int i = 0; i < 15; ++i)
        assert(v[i] == i + 1);
}

void BracketsTest() {
    Vector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
    }
    Vector<int> v1;
    v1 = v;
    for (size_t i = 1; i < 1e5; ++i) {
        v[i] = v[i - 1];
    }
    for (int i = 1; i < 1e5; ++i) {
        v1[i] = v1[i - 1];
    }
    for (int i = 1; i < 1e5; ++i)
        assert(v[i] == v1[i]);
}

int main()
{
    PushBackTest();
    ClearTest();
    EqualTest();
    BracketsTest();
    return 0;
}
