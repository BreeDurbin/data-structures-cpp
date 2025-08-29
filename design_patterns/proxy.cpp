#include<iostream>
#include<memory>

using namespace std;

class Subject {

    public:

    virtual int do_operation() const = 0;
};

class RealSubject : Subject {

    public:
    int do_operation() const override { return 1; };
};

class ProxySubject : Subject {

    unique_ptr<RealSubject> _target{};

    public:
    ProxySubject(unique_ptr<RealSubject>&& target) : _target{move(target)} {};

    int do_operation() const override { return _target->do_operation(); };
};

int main() {

    cout << "Setting up proxy.\n" ;
    ProxySubject proxy = ProxySubject{make_unique<RealSubject>()};

    cout << "Proxy.do_operation(): " << proxy.do_operation() << ".\n";

    return 0;
}
