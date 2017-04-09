#include <iostream>

template<typename T>
struct Node {
    T value;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
    Node<T>(const T&val) {
        value = val;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
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

    Node<T>* inserting(const T& value, Node<T>* cur_node) {
        if (cur_node == nullptr) {
            cur_node = new Node<T>(value);
            ++size_;
            return cur_node;
        } else if (value < cur_node->value) {
            cur_node->left = inserting(value, cur_node->left);
        } else if (value > cur_node->value) {
            cur_node->right = inserting(value, cur_node->right);
        }
        return cur_node;
    }

    int height(Node<T>* cur_node, bool& have_bad_node) const {
        int left_tree_height = 0;
        int right_tree_height = 0;
        if (cur_node->left != nullptr) {
            left_tree_height += height(cur_node->left, have_bad_node);
        }
        if (cur_node->right != nullptr) {
            right_tree_height += height(cur_node->right, have_bad_node);
        }
        if (abs(left_tree_height - right_tree_height) > 1) {
            have_bad_node = true;
        }
        return std::max(left_tree_height, right_tree_height) + 1;
    }

public:
    BinTree() : root(nullptr), size_(0) {}
    explicit BinTree(const T& value) : root(new Node<T>(value)), size_(0) {}

    ~BinTree() {
        if (root != nullptr) {
            bfs_del(root);
        }
    }

    void insert(const T& value) {
        if (root == nullptr) {
            root = new Node<T>(value);
            size_ = 1;
        } else {
            inserting(value, root);
        }
    }

    bool is_avl() const {
        bool have_bad_node = false;
        height(root, have_bad_node);
        return !have_bad_node;
    }

    size_t size() const {
        return size_;
    }
};

int main() {
    BinTree<int> my_tree;

    int cur_val;
    while (std::cin >> cur_val) {
        if (cur_val == 0) {
            break;
        }
        my_tree.insert(cur_val);
    }

    if (my_tree.is_avl()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
