#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
struct element {
    T value;
    element<T>* next;
};

template <typename T>
class Stack {
 private:
    size_t size_stack;
    element<T>* top_ptr;

 public:
    Stack() : size_stack(0), top_ptr(NULL) {}
    ~Stack() {
        while (size_stack > 0) {
            this->pop();
        }
    }

    void push(T value) {
        element<T>* next = top_ptr;
        top_ptr = new element<T>;
        *top_ptr = {value, next};
        ++size_stack;
    }

    T top() const {
        return top_ptr->value;
    }

    void pop() {
        element<T>* next = top_ptr->next;
        delete top_ptr;
        top_ptr = next;
        --size_stack;
    }

    size_t size() const {
        return size_stack;
    }
};

template <typename T>
struct node {
    T value;
    node<T>* next;
};

template <typename T>
class List {
 private:
    node<T>* front_ptr;
    size_t size_of_list;

 public:
    List() : front_ptr(NULL), size_of_list(0) {}
    List(node<T>* ptr, size_t list_size) : front_ptr(ptr), size_of_list(list_size) {}
    ~List() {
        while (!empty()) {
            pop_front();
        }
    }

    void push_front(T& value) {
        if (front_ptr == NULL) {
            front_ptr = new node<T>;
            *front_ptr = {value, NULL};
        } else {
            node<T>* new_head = new node<T>;
            *new_head = {value, front_ptr};
            front_ptr = new_head;
        }
        ++size_of_list;
    }

    void pop_front() {
        node<T>* new_head = front_ptr->next;
        delete front_ptr;
        front_ptr = new_head;
        --size_of_list;
    }

    void push_back(T& value) {
        if (front_ptr == NULL) {
            front_ptr = new node<T>;
            *front_ptr = {value, NULL};
        } else {
            node<T>* last_node = front_ptr;
            while (last_node->next != NULL) {
                last_node = last_node->next;
            }
            node<T>* current_last_node = last_node;
            last_node = new node<T>;
            *last_node = {value, NULL};
            current_last_node->next = last_node;
        }
        ++size_of_list;
    }

    void pop_back() {
        node<T>* last_node = front_ptr;
        if (size() == 1) {
            delete last_node;
            front_ptr = NULL;
        } else {
            while (last_node->next->next != NULL) {
                last_node = last_node->next;
            }
            delete (last_node->next);
            last_node->next = NULL;
        }
        --size_of_list;
    }

    void change_front(node<T>* new_front) {
        front_ptr = new_front;
    }

    T& front() const {
        return front_ptr->value;
    }

    size_t size() const {
        return size_of_list;
    }

    bool empty() const {
        return (size() == 0);
    }

    node<T>* get_front_ptr() const {
        return front_ptr;
    }
};

template <typename T>
node<T>* merge(node<T>* current_node_first_list,
              node<T>* current_node_second_list) {
    node<T>* front_of_result;
    if (current_node_first_list->value < current_node_second_list->value) {
        front_of_result = current_node_first_list;
        current_node_first_list = current_node_first_list->next;
    } else {
        front_of_result = current_node_second_list;
        current_node_second_list = current_node_second_list->next;
    }

    node<T>* current_node_result = front_of_result;

    while (current_node_first_list != NULL && current_node_second_list != NULL) {
        if (current_node_first_list->value < current_node_second_list->value) {
            current_node_result->next = current_node_first_list;
            current_node_result = current_node_first_list;
            current_node_first_list = current_node_first_list->next;
        } else {
            current_node_result->next = current_node_second_list;
            current_node_result = current_node_second_list;
            current_node_second_list = current_node_second_list->next;
        }
    }

    if (current_node_first_list != NULL) {
        current_node_result->next = current_node_first_list;
    } else {
        current_node_result->next = current_node_second_list;
    }

    return front_of_result;
}

template <typename T>
bool can_merge(Stack<pair<node<T>*, int>>& my_stack) {
    if (my_stack.size() < 2) {
        return false;
    }
    pair<node<T>*, int> top_first = my_stack.top();
    my_stack.pop();
    pair<node<T>*, int> top_second = my_stack.top();
    my_stack.push(top_first);

    return (top_first.second == top_second.second);
}

template <typename T>
void merge_sort(List<T>& my_list) {
    Stack<pair<node<T>*, int>> sorting;
    node<T>* current_node = my_list.get_front_ptr();
    while (current_node != NULL) {
        node<T>* next_node = current_node->next;
        current_node->next = NULL;
        sorting.push(make_pair(current_node, 0));
        current_node = next_node;
        while (can_merge(sorting)) {
            node<T>* first_list = sorting.top().first;
            sorting.pop();
            node<T>* second_list = sorting.top().first;
            int level = sorting.top().second;
            sorting.pop();
            node<T>* merge_result = merge(first_list, second_list);
            sorting.push(make_pair(merge_result, level + 1));
            level = level + 1;
        }
    }

    while (sorting.size() > 1) {
        node<T>* first_list = sorting.top().first;
        sorting.pop();
        node<T>* second_list = sorting.top().first;
        int level = sorting.top().second;
        sorting.pop();
        sorting.push(make_pair(merge(first_list, second_list), level + 1));
    }

    my_list.change_front(sorting.top().first);
}

int main() {
    int number_of_elements;
    cin >> number_of_elements;
    List<int> my_list;

    for (int i = 0; i < number_of_elements; ++i) {
        int element;
        cin >> element;
        my_list.push_front(element);
    }

    merge_sort(my_list);

    node<int>* current_node = my_list.get_front_ptr();

    while (current_node != NULL) {
        cout << current_node->value << ' ';
        current_node = current_node->next;
    }

    return 0;
}

