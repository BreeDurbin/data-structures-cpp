#include<iostream>
#include<memory>
#include<unordered_map>
#include<functional>

using namespace std;

template<typename T, typename U, typename V>
class Subject {

    unordered_map<T, function<U(V)>> observers;

    public:

    vector<T> getObserverNames() const { 
        vector<T> ans; 
        ans.reserve(observers.size());
        for(auto& [key, val] : observers) ans.push_back(key);
        return ans;
    }

    void registerObserver(T id, function<U(V)> observer){
        observers[id] = observer;
    };

    void unregisterObserver(T id){ observers.erase(id); }

    void notifyObserver(T id, V val){
        if(observers.find(id) != observers.end()){
            V result = observers[id](val);
            cout << "Notified observer: " << id << " and received response: " << result << "\n";
        } else {
            cout << "Observer " << id << " is not registered. \n";
        }
    }

    void notifyObservers(V val){
        for(auto& [_, observer] : observers){
            V result = observers[_](val);
            cout << "Notified observer: " << _ << " and received response: " << result << "\n";
        }
    }
};

int main() {

    cout << "Setting up Subject.\n" ;
    Subject subject = Subject<string, int, int>{};

    cout << "Registering observers.\n";
    subject.registerObserver("ob3", [](int i){ return i + 3; } );
    subject.registerObserver("ob1", [](int i){ return i + 1; } );
    subject.registerObserver("ob2", [](int i){ return i + 2; } );

    vector<string> observer_ids = subject.getObserverNames();
    cout << "Ids registered: ";
    for(string id : observer_ids) cout << id << " ";
    cout << "\n";

    subject.notifyObserver("ob1", 42);

    subject.notifyObservers(42);

    return 0;
}
