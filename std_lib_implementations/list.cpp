
//--------------------------WIP----------------------------

#include<iostream>
#include<memory>
#include<list>
#include<initializer_list>

using namespace std;


template<typename T>
class Node {
    Node<T>* next;
    Node<T>* prev;
    T* val{};
};

template<typename T>
class List{

    private:
    size_t _size{};
    Node<T>* _front{nullptr};
    Node<T>* _back{nullptr};

    public:

    List() {
        _front = new Node{};
        _back = new Node{};
        _front->next = _back;
        _back->prev = _front;
    };

    List(initializer_list<T> items){
        _size = items.size();
        for(auto & item : items){
            push_front(item);
        }
    }

    const_iterator begin() const { return const_iterator(&(_back->prev)); }
    const_iterator end() const { return const_iterator(&(_front->next)); }
    T& front() const { return _front->next->val; }
    T& back() const { return _back->next->val; }
    size_t size() const { return _size ; }
    bool empty() const { return _size == 0; }

    template<typename T>
    void push_front(T&& t){
        //initialize new node
        Node<T> new_node = new Node();
        new_node->next = _front->next;
        new_node->prev = _front;
        new_node->val = T(std::forward<T>(t));

        // tie other nodes to new node
        _front->next = new_node;
        new_node->next->prev = new_node;
    }

    template<typename T>
    void push_back(T&& t){
        //initialize new node
        Node<T> new_node = new Node();
        new_node->next = _back;
        new_node->prev = _back->prev;
        new_node->val = T(std::forward<T>(t));

        // tie other nodes to new node
        _back->prev = new_node;
        new_node->prev->next = new_node;
    }

    template<typename T>
    void emplace_front(T&& t){
        //initialize new node
        Node<T> new_node = new Node();
        new_node->next = _front->next;
        new_node->prev = _front;
        new_node->val = new T(std::forward<Args>(args) ...);

        // tie other nodes to new node
        _front->next = new_node;
        new_node->next->prev = new_node;
    }

    template<typename T, typename ... args>
    void emplace_back(Args&& args){
        Node<T> new_node = new Node();
        new_node->next = _back;
        new_node->prev = _back->prev;
        new_node->val = new T(std::forward<Args>(args) ...);

        // tie other nodes to new node
        _back->prev = new_node;
        new_node->prev->next = new_node;
    }

}


};

int main() {

    cout << "sizeof list: " << sizeof(list<int>) << ".\n";

    return 0;
}
