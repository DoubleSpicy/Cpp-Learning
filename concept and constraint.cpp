#include <bits/stdc++.h>
#include <cstddef>
#include <concepts>
#include <functional>
#include <string>
using namespace std;

template<typename Int>
void foo(Int bar) {
    cout << bar << " is an integer" << endl;
}

void foo(float bar) {
    cout << bar << " is a floating point number" << endl;
}

template<typename T>
constexpr bool get_value() { return T::value; }

// template<typename T>
// concept isEven = (get_value<T>() % 2 == 0);
template<typename T>
concept smallerThan = requires(T a)
{
    a<a;
};

template<typename T> requires incrementable<T> && smallerThan<T>
class vec2{
    vector<T> vec;
    public:
        void push(T & val){
            
        }
};

template<typename T>
class base{
    public:
        void print(string str) const
        {
            static_cast<const T*>(this)->printImpl(str); //here the magic is!!!
        }
};


class child: public base<child>{
    public:
        int size = 0;
        void printImpl(string str) const
        {
            cout << str << endl;
        }
};

int main() {
    cout << __cplusplus << endl;
    foo(123);
    foo(123ll);
    foo(123.0f);
    foo(123.0); // huh?
    vec2<int> test1;
    // test1.push();
    child c;
    c.print("test");
}