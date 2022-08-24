struct Node {
    Node(int val);
    Node* right_{nullptr};
    Node* left_{nullptr};
    int data_{0};
};

class Splay {
public:
    void inorder() const;
    void insert(int val);
    Node* find(int val);
    bool exists(int val);
    void print() const;

private:
    Node* splay(Node* n, int val);
    Node* find(Node* root, int val);
    Node* insert(Node* root, int val);
    Node* left_rotate(Node* n);
    Node* right_rotate(Node* n);
    void inorder(Node* n) const;
    void print(Node* n, std::string indent, bool last) const;

    Node* root_{nullptr};
};
