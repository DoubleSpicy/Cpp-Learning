#include <bits/stdc++.h>
using namespace std;

int main(){
    long long num = 862508045, q = 8;
    cout << num % q << " " << (num & ((1 << 3)-1)) << endl;
}