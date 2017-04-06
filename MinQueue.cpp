#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
struct element {
    T value;
    T current_min;
    element<T>* next;
};

template <typename T>
class MinStack {
 private:
    size_t size_stack;
    element<T>* top_ptr;
    T current_min_in_stack;

 public:
    MinStack() : size_stack(0), top_ptr(NULL) {}
    ~MinStack() {
        while (size_stack > 0) {
            this->pop();
        }
    }

    void push(T value) {
        if (top_ptr == NULL || current_min_in_stack > value) {
            current_min_in_stack = value;
        }
        element<T>* next = top_ptr;
        top_ptr = new element<T>;
        *top_ptr = {value, current_min_in_stack, next};
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
        if (size_stack > 0) {
            current_min_in_stack = top_ptr->current_min;
        }
    }

    size_t size() const {
        return size_stack;
    }

    T minimum() const {
        return current_min_in_stack;
    }
};

template <typename T>
class MinQueue {
 private:
    MinStack<T> in;
    MinStack<T> out;

 public:
    void push(T value) {
        in.push(value);
    }

    void pop() {
        if (out.size() == 0) {
            while (in.size() > 0) {
                out.push(in.top());
                in.pop();
            }
        }

        out.pop();
    }

    T front() const {
        return in.top();
    }

    T back() const {
        return out.top();
    }

    size_t size() {
        return in.size() + out.size();
    }


    T minimum() {
        if (in.size() == 0) {
            return out.minimum();
        }

        if (out.size() == 0) {
            return in.minimum();
        }

        return min(in.minimum(), out.minimum());
    }
};

int main() {
    MinQueue<int> sequence;

    int number_of_elements;
    int size_of_window;
    cin >> number_of_elements >> size_of_window;

    for (int i = 0; i < size_of_window - 1; ++i) {
        int current_element;
        cin >> current_element;
        sequence.push(current_element);
    }

    for (int i = size_of_window - 1; i < number_of_elements; ++i) {
        int currrent_element;
        cin >> currrent_element;
        sequence.push(currrent_element);
        cout << sequence.minimum() << endl;
        sequence.pop();
    }

    return 0;
}

