#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

template <typename T>
class MyVector
{
public:

    MyVector() : size_{ 0 }, capacity_{ 0 } {}

    explicit MyVector(size_t size) : size_{ size }, capacity_{ size }
    {
        data_ = new T[size];

        fill(data_, data_ + size_, 0);

        size_ = size;
        capacity_ = size;
    }

    MyVector(const MyVector& other)
    {
        size_ = other.size();
        capacity_ = other.capacity();
        data_ = new T[capacity_];

        memcpy(&data_, other.data(), size_);
    }

    ~MyVector()
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

    MyVector& operator=(const MyVector& other)
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

    MyVector& operator=(initializer_list<T> ilist)
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

    void push_back(T val)
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

    friend ostream& operator<<(ostream& os, const MyVector& myVec);
private:
    T* data_ = nullptr;
    size_t size_;
    size_t capacity_;
};

template <typename T>
ostream& operator<<(ostream& os, const MyVector<T>& myVec)
{
    for (size_t i = 0; i < myVec.size(); i++) {
        os << myVec[i];
    }
    return os;
}


void PushBackTest() {
    MyVector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
        assert(v.size() == i);
    }
}

void ClearTest() {
    MyVector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
    }

    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() == 0);
    assert(v.data() == nullptr);
}


void EqualTest() {
    MyVector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
    }
    MyVector<int> v1;
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
    MyVector<int> v;
    for (size_t i = 1; i <= 1e5; ++i) {
        v.push_back(rand());
    }
    MyVector<int> v1;
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
