#include <bits/stdc++.h>
using namespace std;

template<typename T>
void moveSwap(T & x, T & y){
    T z = move(x);
    x = move(y);
    y = move(z);
}

int main(){
    int x = 0, y = 1;
    cout << x << " " << y << endl;
    moveSwap(x, y);
    cout << x << " " << y << endl;
}