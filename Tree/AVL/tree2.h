template <typename T>
struct Node {
    Node* left_;
    Node* right_;
    size_t height_;
    size_t size_;
    T data_;

    Node()
        : left_{nullptr}, right_{nullptr}, data_{NULL}, height_{1}, size_{1} {
    }

    Node(T val)
        : left_{nullptr}, right_{nullptr}, data_{val}, height_{1}, size_{1} {
    }

    Node& operator=(const Node& other) {
        if (this == &other)
            return *this;

        left_ = other.left_;
        right_ = other.right_;
        data_ = other.data_;
        height_ = other.height_;
        size_ = other.size_;

        return *this;
    }
};

template <typename T>
class AVLTree {
public:
    ~AVLTree() {
        destroy(root_);
    }

    T& operator[](const size_t& key) {
        if (key >= size_node(root_) || key < 0)
            throw std::runtime_error("Index out of range");

        return order_stat_node(root_, key)->data_;
    }

    AVLTree& operator=(const AVLTree& other) {
        if (other.root() != root_) {
            destroy(root_);
            root_ = copy_helper(other.root());
        }

        return *this;
    }

    AVLTree(const AVLTree& other) {
        if (other.root() != root_)
            root_ = copy_helper(other.root());
    }

    void insert(T val) {
        root_ = insert_node(root_, val);
    }

    void remove(T val) {
        root_ = remove_node(root_, val);
    }

    size_t height() const {
        if (root_ == nullptr)
            return 0;

        return root_->height_;
    }

    Node<T>* find(T val) {
        return find_node(root_, val);
    }

    bool exists(T val) const {
        return exists_node(root_, val);
    }

    void print() const {
        print_node(root_, "", true);
        std::cout << "\n";
    }

    void inorder() const {
        inorder_node(root_);
        std::cout << "\n";
    }

    Node<T>* root() const {
        return root_;
    }

    size_t size() const {
        if (root_)
            return root_->size_;
        else
            return 0;
    }

private:
    Node<T>* right_rotate(Node<T>* parent) {
        Node<T>* l = parent->left_;
        Node<T>* lr = l->right_;
        l->right_ = parent;
        parent->left_ = lr;

        update_size_node(parent);
        update_height_node(parent);

        update_size_node(l);
        update_height_node(l);

        return l;
    }

    Node<T>* left_rotate(Node<T>* parent) {
        Node<T>* r = parent->right_;
        Node<T>* rl = r->left_;
        r->left_ = parent;
        parent->right_ = rl;

        update_size_node(parent);
        update_height_node(parent);

        update_size_node(r);
        update_height_node(r);

        return r;
    }

    void update_size_node(Node<T>* n) {
        n->size_ = 1 + size_node(n->left_) + size_node(n->right_);
    }

    Node<T>* order_stat_node(Node<T>* n, size_t k) {
        size_t left_size = size_node(n->left_);

        if (k == left_size)
            return n;

        if (k < left_size)
            return order_stat_node(n->left_, k);
        else
            return order_stat_node(n->right_, k - left_size - 1);
    }

    void update_height_node(Node<T>* n) {
        n->height_ =
            1 + std::max(height_node(n->left_), height_node(n->right_));
    }

    int balance_factor(Node<T>* n) {
        if (n == nullptr)
            return 0;

        return height_node(n->left_) - height_node(n->right_);
    }

    Node<T>* balance(Node<T>* n) {
        int balanceFactor = balance_factor(n);

        if (balanceFactor > 1) {
            if (balance_factor(n->left_) >= 0) {
                return right_rotate(n);
            } else {
                n->left_ = left_rotate(n->left_);
                return right_rotate(n);
            }
        }
        if (balanceFactor < -1) {
            if (balance_factor(n->right_) <= 0) {
                return left_rotate(n);
            } else {
                n->right_ = right_rotate(n->right_);
                return left_rotate(n);
            }
        }

        return n;
    }

    Node<T>* min_node(Node<T>* n) {
        Node<T>* current = n;
        while (current->left_ != nullptr)
            current = current->left_;
        return current;
    }

    size_t size_node(Node<T>* n) const {
        if (n == nullptr)
            return 0;

        return n->size_;
    }

    size_t height_node(Node<T>* n) const {
        if (n == nullptr)
            return 0;

        return n->height_;
    }

    Node<T>* insert_node(Node<T>* n, T val) {
        if (n == nullptr)
            return new Node<T>(val);
        if (val < n->data_)
            n->left_ = insert_node(n->left_, val);
        else if (val > n->data_)
            n->right_ = insert_node(n->right_, val);
        else
            return n;

        update_height_node(n);
        update_size_node(n);

        n = balance(n);

        return n;
    }

    Node<T>* remove_node(Node<T>* n, int val) {
        if (n == nullptr)
            return n;

        if (val < n->data_)
            n->left_ = remove_node(n->left_, val);
        else if (val > n->data_)
            n->right_ = remove_node(n->right_, val);
        else {
            if ((n->left_ == nullptr) || (n->right_ == nullptr)) {
                Node<T>* temp = n->left_ ? n->left_ : n->right_;

                if (temp == nullptr) {
                    temp = n;
                    n = nullptr;
                } else
                    *n = *temp;

                delete temp;
            } else {
                Node<T>* temp = min_node(n->right_);
                n->data_ = temp->data_;
                n->right_ = remove_node(n->right_, temp->data_);
            }
        }

        if (n == nullptr)
            return n;

        update_size_node(n);
        update_height_node(n);

        n = balance(n);

        return n;
    }

    Node<T>* find_node(Node<T>* n, T val) {
        if (n == nullptr || n->data_ == val)
            return n;

        if (val > n->data_)
            return find_node(n->right_, val);

        return find_node(n->left_, val);
    }

    bool exists_node(Node<T>* n, T val) const {
        if (n == nullptr)
            return false;

        if (n->data_ == val)
            return true;

        if (val > n->data_)
            return exists_node(n->right_, val);

        return exists_node(n->left_, val);
    }

    void print_node(Node<T>* root, std::string indent, bool last) const {
        if (root != nullptr) {
            std::cout << indent;
            if (last) {
                std::cout << "R----";
                indent += "   ";
            } else {
                std::cout << "L----";
                indent += "|  ";
            }
            std::cout << root->data_ << std::endl;
            print_node(root->left_, indent, false);
            print_node(root->right_, indent, true);
        }
    }

    void inorder_node(Node<T>* n) const {
        if (n == nullptr)
            return;
        inorder_node(n->left_);
        std::cout << n->data_ << " ";
        inorder_node(n->right_);
    }

    void destroy(Node<T>* node) {
        if (node) {
            destroy(node->left_);
            destroy(node->right_);
            delete node;
        }
    }

    Node<T>* copy_helper(const Node<T>* other) {
        if (other == nullptr)
            return nullptr;

        Node<T>* new_node = new Node<T>(other->data_);
        new_node->height_ = other->height_;
        new_node->size_ = other->size_;

        new_node->left_ = copy_helper(other->left_);
        new_node->right_ = copy_helper(other->right_);

        return new_node;
    }

    Node<T>* root_{nullptr};
};
