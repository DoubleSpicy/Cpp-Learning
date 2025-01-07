#include <iostream>
#include <memory>
using namespace std;

template<class A, class B>
class NeoPair{
    private:
        A first;
        B second;
    public:
        NeoPair();
        NeoPair(A, B);
        A getFirst();
        B getSecond();
        void print();
};

template<class A, class B>
NeoPair<A, B>::NeoPair(A fst, B snd){
    first = std::move(fst);
    second = std::move(snd);
}



template<class A, class B>
A NeoPair<A, B>::getFirst(){
    return first;
}

template<class A, class B>
B NeoPair<A, B>::getSecond(){
    return second;
}

template<class A, class B>
void NeoPair<A, B>::print(){
    cout << getFirst() << " " << getSecond() << endl;
}

int main(){
    NeoPair<int, int> test(4, 5);
    shared_ptr<NeoPair<int, int>> ptr(new NeoPair<int, int>(6, 8));
    ptr->print();
}
