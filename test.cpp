#include <iostream>

#include <generator.hpp>

using std::cout;
using std::endl;

class test: public generator
{
protected:
    void body() {
        cout << "1" << endl;
        yield();
        cout << "2" << endl;
        yield();
        cout << "3" << endl;
        yield();
        cout << "4" << endl;
        yield();
        cout << "5" << endl;
        yield();
        cout << "6" << endl;
    }
};

int main(){
    test t;
    while(true) {
        try {
            t.next();
        }
        catch(const generator::stop_iteration& e) {
            cout << "end" << endl;
            break;
        }
    }
}


