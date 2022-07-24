template <typename T>
class Priority_Queue
{
public:

	Priority_Queue() : size_ { 0 }, capacity_ { 0 }, data_ { nullptr }
	{}

	explicit Priority_Queue(size_t size) : size_ { 0 }, capacity_ { size * COEF }
	{
		data_ = new T[capacity_];
	}

	Priority_Queue(const Priority_Queue& other) : size_ { other.size() }, capacity_ { other.capacity() }
	{
        data_ = new T[capacity_];

        std::copy(other.data(), other.data() + size_, data_);
    }

	Priority_Queue(const T* data, size_t size) : size_ { size }, capacity_ { size * COEF }
	{
		data_ = new T[capacity_];
        std::copy(data, data + size, data_);
		for(int i = size_ / 2; i >= 0; i--)
			sift_down(i);
	}

	size_t parent(size_t i) const
	{
		return i/2;
	}

	size_t left_child(size_t i) const
	{
		return 2 * i;
	}

	size_t right_child(size_t i) const
	{
		return 2 * i + 1;
	}

	size_t size() const
	{
		return size_;
	}

	size_t capacity() const
	{
		return capacity_;
	}

	T* data() const
	{
        return data_;
    }

	void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	void sift_up(size_t i)
	{
		while(i > 0 && data_[parent(i)] < data_[i])
		{
			swap(data_[parent(i)], data_[i]);
			i = parent(i);
		}
	}

	void sift_down(size_t i)
	{
		size_t max_id = i;
		size_t child_id = left_child(i);	
		if(child_id < size_ && data_[child_id] > data_[max_id])
			max_id = child_id;

		child_id = right_child(i);

		if(child_id < size_ && data_[child_id] > data_[max_id])
			max_id = child_id;

		if(i != max_id)
		{
			swap(data_[max_id], data_[i]);
			sift_down(max_id);
		}
	}

	void insert(T val)
	{
		if(full())
		{
			//Перевыделить память
			if(capacity_ == 0)
				capacity_ = 1;
			
			capacity_ *= COEF;

			T* temp = new T[size_];
			for(int i = 0; i < size_; i++)
				temp[i] = data_[i];
			delete[] data_;
			data_ = temp;
		}

		size_++;
		data_[size_ - 1] = val;
		sift_up(size_ - 1);
	}

	T extract_max()
	{
		T result = data_[0];
		data_[0] = data_[size_ - 1];
		size_--;
		sift_down(0);
		return result;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	bool full() const
	{
		return size_ == capacity_;
	}

	T get_max() const
	{
		if(empty())
			return NULL;
		else
			return data_[0];
	}

	void remove(size_t i)
	{
		data_[i] = data_[0];
		sift_up(i);
		extract_max();
	}

	void change_priority(size_t i, T p)
	{
		T old_p = data_[i];
		data_[i] = p;

		if(p > old_p)
			sift_up(i);
		else
			sift_down(i);
	}

	void print() const
	{
		for(int i = 0; i < size_; i++)
		{
			std::cout << data_[i] << " ";
		}
		std::cout << "\n";
	}

private:
	int COEF = 2;
	T* data_;
	size_t size_;
	size_t capacity_;
};
