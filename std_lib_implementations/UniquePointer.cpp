#include<iostream>


template<typename T>
class UniquePointer{
private:
    T* _t = nullptr;

public:
    UniquePointer() = default;
    UniquePointer(T* t) : _t(t) {}

    ~UniquePointer() noexcept {
        delete _t;
    }

    UniquePointer(const UniquePointer& rhs) = delete;
    UniquePointer& operator=(const UniquePointer& rhs) = delete;

    UniquePointer(const UniquePointer&& rhs) {
        if(&rhs == this) return;
        if(_t != nullptr) delete _t;
        _t = rhs._t;
        rhs._t = nullptr;
    }

    UniquePointer& operator=(const UniquePointer&& rhs){
        if(&rhs == this) return *this;
        if(_t != nullptr) delete _t;
        _t = rhs._t;
        rhs._t = nullptr;
        return *this;
    }

    inline T& operator*(){ return *_t; }
    inline T& operator&(){ return &_t; }
    inline bool operator==(UniquePoionter lhs, UniquePointer rhs){ return lhs == rhs; }
    inline T& operator->(){ return t-> }


    friend std::ostream& operator<<(std::ostream& o, UniquePointer& rhs){
        o << rhs._t;
        return o;
    }

    T* get() const { return _t; }

    T* release() noexcept {
        T* temp = _t;
        _t = nullptr;
        return temp;
    }

    void reset(T* t){
        if(_t == nullptr) delete _t;
        _t = t;
    }

};

template<typename T, typename ... args>
UniquePointer make_unique(Args&& ... args){
    T* t = new T(std::forward<Args>(args) ...);
    return { t };
}
