
#include<memory>
#include<initializer_list>
#include<iostream>
#include<vector>

using namespace std;

template<typename T>
class Vector {
    private:
    size_t _size{};
    size_t _capacity{};
    T*  _data{ nullptr };

    void expand_if_needed(){
        if(_size == _capacity){
            int new_capacity = (int)(1.5 * capacity);
            reserve(new_capacity);
            capacity = new_capacity;
        }
    }

    public:
    Vector() : _size{0}, _capacity{0} {};
    Vector(const T& t){
        clear();
        reserve(t.capacity());
        for(int i=0; i<t.size(); i++){
            _data[i] = T{t};
        }
        _size = t.size();
        _capacity = t.capacity();
    }
    Vector& operator=(const T& t){
        if(this == t) return this;
        return Vector(t);
    }
    Vector(const T&& t){
        clear();
        _data = t.data();
        _size = t.size();
        _capacity = t.capacity();
    }
    Vector& operator=(const T&& t){
        if(this == t) return this;
        return Vector(t);
    }

    ~Vector() noexcept {
        clear();
        allocator<T> alloc;
        alloc.deallocate(_data, _capacity);
    }

    Vector(const size_t size, const T& t){
        reserve(size);
        for(int i=0; i<size; i++) push_back(t);
        _size = size;
    }

    Vector(const std::initializer_list<T> items){
        reserve(items.size());
        for(auto && i : items) push_back(i);
        _size = items.size();
    }

    bool empty() const { return _size == 0; }
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    T& data() const { return _data ;}
    allocator<T> get_allocator() const { return {}; }

    void clear(){
        if(_data == nullptr) return;
        for(int i=0; i<_size; i++) delete _data[i].~T();
        _size = 0;
    }

    void reserve(int capacity) { 
        if(capacity > _capacity){
            std::allocator<T> alloc;
            T* new_data = alloc.allocate(capacity);
            if(_data != nullptr){
                for(int i=0; i<size; i++) new_data[i] = _data[i];
                for(int i=0; i<size; i++) _data[i].~T();
                alloc.deallocate(_data, _capacity);
            }
            _capacity = capacity;
            _data = new_data;
        }
    }

    void push_back(const T& t){
        expand_if_needed();
        _data[size++] = T{t}; 
    }

    template<typename... Args>
    void emplace_back(Args&&... args){
        expand_if_needed();
        _data[size++] = T{std::forward<Args>(args) ...};
    }

};



int main() {

    cout << "Vector size: " << sizeof(Vector<int>) << endl;
    cout << "std::vector size: " << sizeof(vector<int>) << endl;

    return 0;
}
