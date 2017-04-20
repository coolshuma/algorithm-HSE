#include <iostream>

template<typename T>
struct Node {
    T value;
    char color;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
    Node<T>(const T&val) : value(val) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = 'B';
    }
};

template<typename T>
class BinTree {
private:
    Node<T>* root;
    size_t size_;

    void bfs_del(Node<T>* cur_node) {
        if (cur_node->left != nullptr) {
            bfs_del(cur_node->left);
        }
        if (cur_node->right != nullptr) {
            bfs_del(cur_node->right);
        }
        delete cur_node;
    }

    Node<T>* inserting(const T& value, Node<T>* cur_node, Node<T>* parent) {
        if (cur_node == nullptr) {
            cur_node = new Node<T>(value);
            cur_node->color = 'R';
            cur_node->parent = parent;
            ++size_;
            fix(cur_node);
            return cur_node;
        } else if (value < cur_node->value) {
            cur_node->left = inserting(value, cur_node->left, cur_node);
        } else if (value > cur_node->value) {
            cur_node->right = inserting(value, cur_node->right, cur_node);
        }
        return cur_node;
    }

    void fix(Node<T>* node) {
        while (node->parent != nullptr && node->parent->color == 'R') {
            Node<T>* grand = node->parent->parent;
            if (grand == nullptr) {
                return;
            }
            Node<T>* uncle;
            if (grand->left == node->parent) {
                uncle = grand->right;
            }
        }
        root->color = 'B';
    }

    bool finding(Node<T>* cur_node, T& value) const {
        bool is_find_left = false;
        bool is_find_right = false;
        if (cur_node == nullptr) {
            return false;
        }
        if (cur_node->value == value) {
            return true;
        }
        if (value < cur_node->value) {
            return finding(cur_node->left, value);
        } else if (value > cur_node->value) {
            return finding(cur_node->right, value);
        }
    }

    void showing(Node<T>* cur_node) const {
        if (cur_node->left != nullptr) {
            showing(cur_node->left);
        }
        if (cur_node->right != nullptr) {
            showing(cur_node->right);
        }
        std::cout << cur_node->value << ' ' << cur_node->left << ' ' << cur_node->right;
        std::cout << ' ' << cur_node->color << std::endl;
    }

public:
    BinTree() : root(nullptr), size_(0) {}
    explicit BinTree(const T& value) : root(new Node<T>(value)), size_(0) {}

    ~BinTree() {
        if (root != nullptr) {
            bfs_del(root);
        }
    }

    void insert(const T& value, const size_t number) {
        if (root == nullptr) {
            root = new Node<T>(value);
            size_ = 1;
        } else {
            inserting(value, root, nullptr);
        }
    }

    bool find(T value) const {
        if (root->value == value)
            return true;
        return finding(root, value);
    }

    size_t size() const {
        return size_;
    }

    void show() const {
        std::cout << size() << std::endl;
        showing(root);
    }
};

int main() {
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
    int number_of_requests;
    BinTree<int> my_tree;

    std::cin >> number_of_requests;

    for (size_t i = 0; i < number_of_requests; ++i) {
        int operation;
        int key;
        std::cin >> operation >> key;
        if (operation == 0) {
            my_tree.insert(key, i);
        } else {
            if (my_tree.find(key)) {
                std::cout << "Yes" << std::endl;
            } else {
                std::cout << "No" << std::endl;
            }
        }
    }

    return 0;
}
