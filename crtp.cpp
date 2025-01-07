#include <bits/stdc++.h>
#include <iterator>
// import print; // not yet in gcc!
#include <generator>
#include <print>
#include <coroutine>
using namespace std;

template<typename T>
class base{
    void printName(){
        cout << "base" << endl;
    }
};

struct coroutine : std::coroutine_handle<promise>
{
    using promise_type = ::promise;
};


class child1: base<child1>{
    // singelton class of base B
    static base<child1> *ptr;
    public:
        child1() = default;
        // delete copy constructor/copy-assignment constructor
        child1(const child1 & ref) = delete;
        child1 operator=(const child1 & ref) = delete;
        child1(child1 && rvalue) = delete;
        child1 operator=(child1 && rvalue) = delete;

        base<child1>* get(){
            if (!ptr) {
                ptr = new base<child1>();
            }
            return ptr;
        }
        
};

template<typename T>
class writer{
    static writer* ptr; // singleton writer to a log file
    public:
        void write() const{
            cout << static_cast<const T*>(this)->format() << endl;
            
        }
};

class fillLogger: public writer<fillLogger>{
    public:
        string format() const{
            return string("Fill Cash Order"); // prvalue
        }
};

class bidAskLogger: public writer<bidAskLogger>{
    public:
        string format() const{
            return string("BidAskQueue of NVDA");
        }
};

template<incrementable T>
class NeoWriter{
    T cnt;
    public:
        NeoWriter(T && x):cnt(x){}
        NeoWriter(){cnt = T(0);}
        void output(this auto& self){
        }
        void test(){

        }

};

// class Logger: NeoWriter{
//     public:
//         string getStr(){
//             return "TEST MSG: ";
//         }
// };

struct foo{
    int left = -1, right = 1, cnt = 0;

    foo traverse_inorder(this auto& self) {
        for(int i = 0; i < 10; i++)
            co_yield i;
    }
};

int main(){
    cout << __cplusplus << endl;
    fillLogger   logger1;
    bidAskLogger logger2;
    logger1.write();
    logger2.write();
    coroutine h = foo{}.traverse_inorder();
}