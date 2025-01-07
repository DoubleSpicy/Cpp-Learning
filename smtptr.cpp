#include <bits/stdc++.h>
using namespace std;

template<typename T>
class uni_ptr{
    public:
        uni_ptr(T*&& p){
            data = p;
        }

        ~uni_ptr(){
            if(data)
                delete data;
            cout << "data deleted!" << endl;
        }

        // remove copy constructor
        uni_ptr(const uni_ptr & p) = delete;
        // remove copy-assignment constructor
        uni_ptr& operator=(const uni_ptr & p) = delete;
        
        // Returns a pointer to the managed object or nullptr if no object is owned.
        T* get(){
            return data;
        }

        T* operator->(){
            return data;
        }

        T& operator*(){
            return *data;
        }
    private:
        // actual data
        T* data = nullptr;
};

class cntWrapper{
    public:
        cntWrapper(){val = new atomic<long>(1);}
        cntWrapper(cntWrapper* && v){
            val = v->val++;
        }
        ~cntWrapper(){
            val--;
            if(val == 0){
                delete val;
            }
        }
        long getVal() const noexcept {
            return (*val).load();
        }

        friend ostream& operator<<(ostream & os, cntWrapper cnt){
            os << cnt.getVal();
            return os;
        }
        
    private:
        atomic<long> *val;    
};

template<typename T>
class share_ptr{
    public:
        share_ptr(T*&& p){
            data = p;
            cnt = new cntWrapper();
        }

        // copy constructor
        share_ptr(share_ptr & ptr){
            data = ptr.get();
            cnt = new cntWrapper(ptr._getRefCnt());
        }

        // copy assignment operator
        share_ptr& operator=(share_ptr & ptr){
            data = ptr.get();
            cnt = new cntWrapper(ptr._getRefCnt());
        }

        ~share_ptr(){
            cout << "ref after = " << cnt->getVal() << endl;
            if(cnt->getVal() == 1){
                delete data;
                cout << "ref = 0!\n";
            }
            delete cnt;
        }

        T* operator->(){
            return data;
        }

        T operator*(){
            return *data;
        }

        T* get(){
            return data;
        }

        long getRefCnt(){
            return cnt->getVal();
        }


    private:
        cntWrapper *cnt;
        T* data;
        auto _getRefCnt(){
            return cnt;
        }
};



class content{
    public:
        content(int&& x, int&& y, int&& z): x(x), y(y), z(z){};
        int x;
        int y;
        int z;

        bool operator==(const content & rhs) const {
            return x==rhs.x && y==rhs.y && z==rhs.z;
        }

        bool operator<(const content & rhs) const {
            return x+y+z < rhs.x+rhs.y+rhs.z;
        }
        bool operator>(const content & rhs) const {
            return !(*this == rhs) && !(*this < rhs);
        }
};

void test(){
    uni_ptr<content> uPtr(new content(1,2,3));
    content *v = uPtr.get();
    cout << v->x << " " << uPtr->y << " " << (*uPtr).z << endl;
    
}

void test2(){
    share_ptr<content> sPtr(new content(1,2,3));
    auto sPtr2 = sPtr;
    cout << sPtr.getRefCnt() << " " << sPtr2.getRefCnt() << endl;
    // cout << (sPtr.getRefCnt()) << " " << sPtr2.getRefCnt() << endl;
}

template<>
struct std::hash<content>{
    std::size_t operator()(const content& c) const noexcept{
        return (c.x + c.y + c.z) % 37;
    }
};




int main(){
    test2();
    unordered_map<content, string> content2string;
    content c1(1,2,3), c2(4,5,6), c3(7,8,9);
    // content2string.insert({c1, "a"});
    content2string[c1] = "a";
    content2string[c2] = "b";
    content2string[c3] = "c";
    vector<content> arr = {c1, c2, c3};
    sort(arr.begin(), arr.end(), greater<content>());
    cout << "get c1: " << content2string[c1] << endl;
    // shared_ptr<content> sp(new content(1,2,3));
    // sp._M_refcount._M_get_use_count

    vector<int> arr2 = {1,2,3};
    int i = 0;
    while(i < arr2.size()){
        cout << arr2[i++] << " ";
    }

    int limit = 1;
    sort(arr.begin(), arr.end(), [&limit](const content & a, const content & b){
        return (a.x > limit ? a > b : false);
    });

    return 0;

    
}