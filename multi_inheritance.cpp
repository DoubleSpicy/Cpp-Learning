#include <bits/stdc++.h>
using namespace std;

class A{
    public:
        A(){
            cout << "A constructor\n";
        }
        void print(){
            cout << "A printing: \n";
        }
        ~A(){
            cout << "A destructor\n";
        }
};

class B{
    public:
        B(){
            cout << "B constructor\n";
        }
        void print(){
            cout << "B printing: \n";
        }
        ~B(){
            cout << "B destructor\n";
        }
};

class C: A, B{
    public:
        C(){
            cout << "C constructor\n";
        }
        void print(){
            cout << "C printing: \n";
        }
        ~C(){
            cout << "C destructor\n";
        }
};

int main(){
    C c = C();
}