#include<iostream>
#include<memory>

using namespace std;

class Strategy{
    string _name = "Default strategy";
    public:
    virtual string name() const {return _name; };
    virtual void execute_strategy() const = 0;
};

struct StrategyA : Strategy {
    string _name = "Strategy A";
    public: 
    string name() const override {return _name; };
    void execute_strategy() const override {
        cout << "Executing strategy A" << endl;
    }
};

struct StrategyB : Strategy {
    string _name = "Strategy B";
    public: 
    string name() const override {return _name; };
    void execute_strategy() const override {
        cout << "Executing strategy B" << endl;
    }
};

class Context{
    unique_ptr<Strategy> _strategy;
    public:
    Context(unique_ptr<Strategy>&& strategy) : _strategy{move(strategy)} {
        cout << "Initialized context with strategy: " << _strategy->name() << endl;
    };
    void set_strategy(unique_ptr<Strategy>&& strategy) { 
        cout << "Setting new strategy: " << strategy->name() << endl;
        _strategy = move(strategy); 
    };

    void do_operation(){
        cout << "Doing Operation: " << endl;
        _strategy->execute_strategy();
    }

};


int main() {

    Context context = Context(make_unique<StrategyA>());
    context.do_operation();
    context.set_strategy(make_unique<StrategyB>());
    context.do_operation();

    return 0;
}
