#include <iostream>

union U{
    uint64_t x;
    uint32_t y[2];
};



int main(){
    int x = 0x12345;
    int *xx = &x;
    // std::cout << "hello world \n";
    // U test;
    // test.y[0] = 0xFFFF'FFFF;
    // test.y[1] = 0xFFFF'FFFF;
    // uint64_t y = test.x + (uint64_t)1;
    // // 0xFFFF'FFFF'FFFF'FFFF + 0x0000'0001
    // std::cout << y << std::endl;

    // int x = 3;
    // inline auto add(int a, int b) { return a + (x *= 3) + b; }
    // int y = add(x++, x *= 2);
    return 0;
}