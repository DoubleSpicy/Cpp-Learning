#include <bits/stdc++.h>
using namespace std;


void fn(int && x){
    x++;
    cout << "addr of x: " << &x << endl;
}

int main(){
    int x = 1;
    fn(move(x));
    cout << &x << endl;
    return 0;
}