#include<iostream>
#include <string>
#include <cassert>
 
using namespace std;
 
template <typename T>
class List
{
public:
    struct Node
    {
        Node() : value_{ 0 }, next_{ nullptr } {}
        explicit Node(T value) : value_{ value }, next_{ nullptr } {}
 
        T value_;
        Node* next_;
    };
 
    List() : head_{ nullptr }, tail_{ nullptr } {}
 
    ~List()
    {
        Node* currentNode = this->head_;
        while (currentNode)
        {
            Node* nextNode = currentNode->next_;
            delete currentNode;
            currentNode = nextNode;
        }
    }
 
    List(const List& other)
    {
        for (Node* p = other.head_; p != nullptr; p = p->next_)
        {
            push_back(p->value_);
        }
    }
 
    const List& operator=(const List& other)
    {
        for (Node* p = other.head_; p != nullptr; p = p->next_)
        {
            push_back(p->value_);
        }
        return *this;
    }
 
    bool empty() const
    {
        return head_ == nullptr;
    }
 
    Node* begin()
    {
        return head_;
    }
    Node* end()
    {
        return tail_;
    }
 
    Node* find(T target)
    {
        for (Node* p = head_; p != nullptr; p = p->next_)
            if (p->value_ == target)
                return p;
 
        return nullptr;
    }
 
    bool exists(T target) const
    {
        for (Node* p = head_; p != nullptr; p = p->next_)
            if (p->value_ == target)
                return true;
 
        return false;
    }
 
    bool push_back(T value_)
    {
        Node* p = new Node(value_);
        if (empty())
        {
            head_ = tail_ = p;
            return true;
        }
        else
        {
            tail_->next_ = p;
            tail_ = p;
            return true;
        }
        return false;
    }
 
    void push_front(int value_)
    {
        Node* p = new Node(value_);
        p->next_ = head_;
        head_ = p;
    }
 
    bool removeNext(Node* target)
    {
        if (empty())
            return false;
        if (target == nullptr)
            return false;
        if (target->next_ == nullptr)
            return false;
 
        if (target->next_->next_ != nullptr)
        {
            Node* next_of_next = target->next_->next_;
            delete target->next_;
            target->next_ = target->next_->next_;
        }
        else
        {
            delete target->next_;
            tail_ = target;
        }
        return true;
    }
 
    void push(T target, T value)
    {
        Node* p = head_;
 
        while (p != nullptr)
        {
            if (p->value_ == target)
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
        Node* p = nullptr;
        Node* walk = head_;
 
        while (walk->value_ != target)
        {
            p = walk;
            walk = walk->next_;
        }
 
        if (p == nullptr)
            head_ = walk->next_;
        else
            p->next_ = walk->next_;
    }
 
    string toString()
    {
        string result = "";
 
        Node* p = head_;
        while (p != nullptr)
        {
            result += to_string(p->value_) + " ";
            p = p->next_;
        }
 
        return result;
    }
private:
    Node* head_;
    Node* tail_;
};
 
template <typename T>
pair<List<T>, List<T>> devideEvenOdd(List<T> myList)
{
    List<T> even;
    List<T> odd;
 
    for (auto p = myList.begin(); p != nullptr; p = p->next_)
    {
        cout << p->value_ << endl;
        if (p->value_ % 2 == 0)
            even.push_back(p->value_);
        else
            odd.push_back(p->value_);
    }
 
    pair<List<T>, List<T>> result;
    result.first = even;
    result.second = odd;
    return	result;
}
 
void PushBackTest()
{
    List<int> myList;
 
    myList.push_back(1);
 
    assert(myList.begin()->value_ == 1);
 
    int pushCount = 1e5;
    for (int i = 2; i <= pushCount; i++)
        myList.push_back(i);
 
    int size = 0;
    int i = 1;
    for (auto p = myList.begin(); p != nullptr; p = p->next_)
    {
        size++;
        assert(p->value_ == i);
        i++;
    }
    assert(size == pushCount);
}
 
void PushFrontTest()
{
    List<int> myList;
 
    int pushCount = 1e5;
    for (int i = 1; i <= pushCount; i++)
        myList.push_front(i);
 
    int size = 0;
    int i = pushCount;
    for (auto p = myList.begin(); p != nullptr; p = p->next_)
    {
        size++;
        assert(p->value_ == i);
        i--;
    }
    assert(size == pushCount);
}
 
void RemoveTest()
{
    List<int> myList;
 
    int pushCount = 1e5;
    for (int i = 1; i <= pushCount; i++)
    {
        if (i % 2 == 0)
            myList.push_back(1);
        else
            myList.push_back(2);
    }
 
    for (int i = 1; i <= pushCount / 2; i++)
    {
        myList.remove(2);
    }
 
    int size = 0;
    for (auto p = myList.begin(); p != nullptr; p = p->next_)
    {
        size++;
        assert(p->value_ == 1);
    }
    assert(size == pushCount / 2);
 
 
}
 
int main()
{
    PushBackTest();
    PushFrontTest();
    RemoveTest();
 
    return 0;
}
