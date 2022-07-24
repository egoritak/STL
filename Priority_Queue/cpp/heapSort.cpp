template<typename T = int>
void swap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}

size_t left_child(size_t i) 
{
	return 2 * i;
}

size_t right_child(size_t i) 
{
	return 2 * i + 1;
}

template<typename T = int>
void sift_down(T* a, size_t size, size_t i)
{
	size_t max_id = i;
	size_t child_id = left_child(i);
	if(child_id < size && a[child_id] > a[max_id])
		max_id = child_id;

	child_id = right_child(i);

	if(child_id < size && a[child_id] > a[max_id])
		max_id = child_id;

	if(i != max_id)
	{
		swap(a[max_id], a[i]);
		sift_down(a, size, max_id);
	}
}

template<typename T = int>
void build_heap(T* a, size_t size)
{
	for(int i = size / 2; i >= 0; i--)
		sift_down(a, size, i);
}

template<typename T = int>
void heap_sort(T* a, size_t size)
{
	build_heap(a, size);

	size_t temp_size = size;
	for(int i = 0; i < temp_size; i++)
	{
		swap(a[0], a[size-1]);
		size--;
		sift_down(a, size, 0);
	}
}
