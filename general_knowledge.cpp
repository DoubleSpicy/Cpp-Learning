#include <bits/stdc++.h>

using namespace std;

// variadic function kwargs**
template <typename T>
T add(const T & x){
    return x;
}

template <typename T, typename... Ts>
T add(const T & x, const Ts &... args){
    return x + add(args...);
}
// ======

// template specialization
template <>
string add<string>(const string & x){
    return x + "|";
}

// partial template specialization
template <>
string add<string, int>(const string & x, const int & y){
    return x + "+" + to_string(y);
}

template <typename... ints>
string add(const string & x, const ints &... y){
    return x + to_string(add(y...));
}

template <typename... doubles>
string add(const double & x, const doubles &... y){
    return to_string(x) + add(y...);
}

template<>
string add(const double & x){
    return to_string(x);
}

// SPSC queue with lock
template<typename T>
class SpscQueue{
    atomic_int32_t read = 0, write = 0, cnt = 0;
    // [null read x x write null null null]
    vector<T> ringbuf; // ring buffer
    mutex lock;
    public:
        SpscQueue<T>(const int && size){
            ringbuf.resize(size);
        }
        SpscQueue<T>(){
            ringbuf.resize(1000);
        }

        // push an element of type T into end of the queue, return true if success
        bool push(const T && v){
            lock_guard<mutex> guard(lock);
            if(cnt == ringbuf.size()) return false;
            ringbuf[write] = v;
            write = (write + 1) % ringbuf.size();
            cnt++;
            // cout << "WRITE | read: " << read << ", write: " << write << endl;
            return true;
        }

        optional<T> pop(){
            lock_guard<mutex> guard(lock);
            cout << "POP | read: " << read << ", write: " << write << endl;
            if(cnt == 0) return nullopt;
            optional<T> v(ringbuf[read]);
            read = (read + 1) % ringbuf.size();
            cnt--;
            return v;
        }
};

// lock-free SPSC queue
template <typename T>
class lockFreeQueue{
    private:
        vector<T> ringbuf;
        atomic<int> write = 0, read = 0;
    public:
        lockFreeQueue<T>(const int & maxSize){
            ringbuf.resize(maxSize);
        };
        bool push(const T & val){
            int writePos = write.load();
            return true;
        }

        optional<T> pop(){
            
            return oldHead->data;
        }
        
};

// concepts and constraints

// smart pointer
class owner{
    unique_ptr<int> i32p;
    shared_ptr<int> i32ps;
};

// lambdas
// see in main()

// decltype and auto
// auto only deduces type of class, decltype can deduce type of expression
template <typename T>
auto add2(const T & x, const T & y) -> decltype(x+y){
    return x+y;
}
static_assert(is_same_v<int, decltype(123.45 + 456.78)> == false);

// move and forward
// move -> rvalue
// forward -> same type as argument


// inheritance
class A{
    protected:
    A(){
        cout << "construct A" << endl;
    }

    ~A(){
        cout << "destruct A" << endl;
    }
};

class B{
    protected:
    B(){
        cout << "construct B" << endl;
    }

    ~B(){
        cout << "destruct B" << endl;
    }
};

class C:A,B{
    C(){
        cout << "construct B" << endl;
    }

    ~C(){
        cout << "destruct B" << endl;
    }
};

int main(){
    cout << add(1,2,3,4,5) << endl;
    const string a = "a";
    string b = "b", c = "c";
    int one = 1;
    cout << add(a, one, one) << endl;
    cout << add(100.01, 200.02, 300.03) << endl;
    cout << add(100.01) << endl;
    
    SpscQueue<int> q(100);
    q.push(1);
    q.push(2);
    q.push(3);
    for(int i = 0; i < 4; i++){
        cout << "pop: " << q.pop().value_or(-1) << endl;
    }

    const int paramA = 123;
    vector<int> arr = {123,456,789};
    // capture by reference
    std::sort(arr.begin(), arr.end(), [&](const auto & a, const auto & b){
    if(paramA)
        return a <= b;
    });
    // capture by value
    std::sort(arr.begin(), arr.end(), [=](const auto & a, const auto & b){
    if(paramA)
        return a <= b;
    });

    // can constexpr it if possible
    constexpr int paramB = 456;
    std::sort(arr.begin(), arr.end(), [&](const auto & a, const auto & b){
    if(paramB)
        return a <= b;
    });

    lockFreeQueue<int> q2;
    for(int i = 0; i < 3; i++){
        q2.push(i+1);
    }


    return 0;
}