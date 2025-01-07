#include <bits/stdc++.h>
using namespace std;


int main(){
    unordered_map<int ,int> m;
    m[123] = 456;
    cout << m.load_factor() << ' ' << m.bucket_count() << '\n';
}