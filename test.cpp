#include <iostream>
#include <string>
#include <sstream>
#include <generator.hpp>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

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

class test2: public generic_generator<string>
{
protected:
    void body() {
        for(int i=0; i<5; i++) {
            stringstream ss;
            ss << "send: " << i;
            yield_send(ss.str());
        }
    }
};

int main(){
    test t;
    while(true) {
        try {
            t.next();
        }
        catch(const stop_iteration& e) {
            cout << "end" << endl;
            break;
        }
    }

    test2 t2;
    while(true) {
        try {
            string data;
            t2.next();
            if(t2.receive(&data)) {
                cout << "next ret: " << data << endl;
            }
        }
        catch(const stop_iteration& e) {
            cout << "end" << endl;
            break;
        }
    }
}


