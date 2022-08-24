#include "../include/tree.h"

Node::Node(int val) {
    data_ = val;
}

Node* Splay::find(Node* n, int val) {
    return splay(n, val);
}

Node* Splay::find(int val) {
    root_ = find(root_, val);
    return root_;
}

bool Splay::exists(int val) {
    return find(root_, val) ? true : false;
}

Node* Splay::insert(Node* n, int val) {
    if (n == nullptr)
        return new Node(val);
    if (val < n->data_)
        n->left_ = insert(n->left_, val);
    else if (val > n->data_)
        n->right_ = insert(n->right_, val);

    return n;
}

void Splay::insert(int val) {
    root_ = insert(root_, val);
}

Node* Splay::splay(Node* n, int val) {
    if (n == nullptr || n->data_ == val)
        return n;

    //Если искомый нод где-то слева:
    if (val < n->data_) {
        if (n->left_ == nullptr)
            return n;

        //Если мы слева-слева, вращаем деда,
        //если слева-справа - родителя
        // Zig-Zig (лево-лево)
        if (val < n->left_->data_) {
            n->left_->left_ = splay(n->left_->left_, val);
            n = right_rotate(n);
        } else if (val > n->left_->data_)  // Zig-Zag (лево-право)
        {
            n->left_->right_ = splay(n->left_->right_, val);

            if (n->left_->right_ != nullptr)
                n->left_ = left_rotate(n->left_);
        }

        return (n->left_ == nullptr) ? n : right_rotate(n);

        //Иначе, если он где-то справа:
    } else {
        //Если нет искомого нода:
        if (n->right_ == nullptr)
            return n;

        //Если нод справа-справа, будем вращать его деда (текущий нод),
        //Иначе, если он справа-слева, вращаем родителя
        // Zag-Zag (право-право)
        if (val > n->right_->data_) {
            n->right_->right_ = splay(n->right_->right_, val);
            n = left_rotate(n);
        } else if (val < n->right_->data_)  // Zag-Zig (право-лево)
        {
            n->right_->left_ = splay(n->right_->left_, val);

            if (n->right_->left_ != nullptr)
                n->right_ = right_rotate(n->right_);
        }

        return (n->right_ == nullptr) ? n : left_rotate(n);
    }
}

Node* Splay::left_rotate(Node* parent) {
    Node* r = parent->right_;
    parent->right_ = r->left_;
    r->left_ = parent;
    return r;
}

Node* Splay::right_rotate(Node* parent) {
    Node* l = parent->left_;
    parent->left_ = l->right_;
    l->right_ = parent;
    return l;
}

void Splay::inorder(Node* n) const {
    if (!n)
        return;
    inorder(n->left_);
    std::cout << n->data_ << ' ';
    inorder(n->right_);
}

void Splay::print(Node* root, std::string indent, bool last) const {
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
        print(root->left_, indent, false);
        print(root->right_, indent, true);
    }
}

void Splay::print() const {
    print(root_, "", true);
    std::cout << "\n";
}

void Splay::inorder() const {
    inorder(root_);
}
