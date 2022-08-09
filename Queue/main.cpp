#include <cassert>
#include <iostream>

template <typename T>
class Queue {
public:
    Queue() {
    }

    explicit Queue(size_t size)
        : size_{size}, capacity_{size * COEF}, front_{-1}, back_{-1} {
        data_ = new T[capacity_];
    }

    Queue(const Queue& other)
        : size_{other.size()},
          capacity_{other.capacity()},
          back_{other.back_id() - 1},
          front_{other.front_id()} {
        data_ = new T[capacity_];

        std::copy(other.data(), other.data() + size_, data_);
    }

    ~Queue() {
        delete[] data_;
    }

    int back_id() const {
        return back_;
    }

    int front_id() const {
        return front_;
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    T* data() const {
        return data_;
    }

    T front() const {
        if (empty())
            throw std::runtime_error("queue is empty");
        return data_[front_];
    }

    T back() const {
        if (empty())
            throw std::runtime_error("queue is empty");
        return data_[back_];
    }

    bool isFull() const {
        return ((back_ + 1) % size_ == front_);
    }

    bool isEmpty() const {
        return front_ == -1;
    }

    T pop() {
        if (isEmpty())
            throw std::runtime_error("Pop failed! Queue is empty\n");

        size_--;

        T data = data_[front_];
        data_[front_] = -1;

        if (front_ == back_) {
            front_ = -1;
            back_ = -1;
        } else if (front_ == size_ - 1)
            front_ = 0;
        else
            front_++;

        return data;
    }

    const Queue& push(T val) {
        if (isFull()) {
            size_ += 1;

            if (size_ < capacity_) {
                capacity_ = size_ * COEF;

                T* temp = new T[capacity_];
                for (int i = 0; i < size_ - 1; i++)
                    temp[i] = data_[i];
                delete[] data_;
                data_ = temp;
            }
        }

        if (front_ == -1) {
            front_ = back_ = 0;
        } else if (back_ == size_ - 1 && front_ != 0) {
            back_ = 0;
        } else {
            back_++;
        }
        data_[back_] = val;

        return *this;
    }

private:
    int COEF = 2;
    int front_;
    int back_;
    size_t size_;
    size_t capacity_;
    T* data_;
};

void PushAndPopTest() {
    // [0 1 2 3]
    //  f     b
    Queue<int> q(4);
    for (int i = 0; i < 4; ++i) {
        q.push(i);
    }
    assert(q.front_id() == 0);
    // [x 1 2 3]
    //    f   b
    q.pop();
    assert(q.front_id() == 1);
    // [4 1 2 3]
    //  b f
    q.push(4);
    // [4 1 2 3 x x x x]
    //  b f
    q.push(5);
    // [4 5 2 3 x x x x]
    //  b f
    assert(q.front_id() == 1);
}

int main() {
    PushAndPopTest();
    return 0;
}
