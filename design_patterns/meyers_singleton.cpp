
using namespace std;

struct meyers_singleton {
    int hi;
    int data;

    static meyers_singleton& getInstance(){
        static meyers_singleton singleton;
        return singleton;
    }
};



int main() {

    auto singleton = meyers_singleton::getInstance();

    return 0;
}
