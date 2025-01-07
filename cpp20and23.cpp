#include <coroutine>
#include <iostream>
#include <expected>
#include <vector>
#include <ranges>
#include <iterator>
#include <print>
#include <generator>
struct promise;

using namespace std;
 
struct coroutine : std::coroutine_handle<promise>
{
    using promise_type = ::promise;
};
 

struct promise
{
    coroutine get_return_object() { return {coroutine::from_promise(*this)}; }
    std::suspend_always initial_suspend() noexcept { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
};
 

struct S
{
    int i;
    coroutine f()
    {
        std::cout << i;
        co_return;
    }
};

void good()
{
    coroutine h = [](int i) -> coroutine // make i a coroutine parameter
    {
        std::cout << i;
        co_return;
    }(0);
    // lambda destroyed
    h.resume(); // no problem, i has been copied to the coroutine
                // frame as a by-value parameter
    h.destroy();
}

void iterate(){
    coroutine h = [](int i) -> coroutine
    {
        while(i--){
            std::cout << i << std::endl;
        }
        co_return;
    }(10);
    h.resume();
    h.destroy();
}

enum class oddOrEven
{
    odd,
    even,
};

auto getOdd(int val) -> expected<int, oddOrEven>{
    if(val % 2 != 0)
        return val;
    else
        return unexpected(oddOrEven::even);
}

// auto getOddOnly(){
//     vector arr{1,2,3,4,5};
//     return arr;
// }

char convertIntToChar(const int x){
    return 'a'+x;
}

struct generatorTest{
    int cnt = 5;
    generator<int> gen()
    {
        while(cnt--){
            co_yield cnt;
        }
    }
};

int main(){
    good();

    iterate();

    auto res = getOdd(2);
    if(res){
        cout << res.value() << endl;
    }
    else{
        cout << "GG : " << (int)(res.error()) << endl;
    }

    vector arr{0,1,2,3,4,5};
    cout << arr[0] << endl;

    cout << "stream..." << endl;
    auto oddOnly = arr | std::views::filter([](const auto & v){return v % 2 == 0;})
                       | std::views::transform(convertIntToChar)
                       | std::ranges::to<vector>();
                    //    | std::views::join_views
    
    for(auto & v : oddOnly){
        cout << v << endl;
    }

    println("no more cout bro");
    println("test formatting: from C++{}", 23);

    println("testing geneators in C++23");
    generatorTest g;
    for(auto i: g.gen()){
        println("{}", i);
    }
}