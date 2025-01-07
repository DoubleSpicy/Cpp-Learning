#include <atomic>
#include <bits/stdc++.h>
#include <cstddef>
#include <deque>
#include <queue>
#include <type_traits>

using namespace std;

template<typename T>
struct node{
    T val;
    node<T>* next;
};

template<typename T>
class lockfree_stack{
    atomic<node<T>*> top;
    public:
    void push(T v){
        node<T>* new_node = new node<T>{v, NULL};
        new_node->next = top.load(memory_order_relaxed);
        while (!atomic_compare_exchange_weak(&top, &new_node->next, new_node)) {
        
        }
    }
    T pop(){
        if(!top.load()) return NULL;
        auto old_head = top.load(memory_order_acquire);
        node<T>* new_head = old_head->next;
        while(!top.compare_exchange_weak(old_head, new_head, memory_order_acquire)){
            old_head = top.load();
            new_head = old_head->next;
        }
        auto val = old_head->val;
        return val;
    }

};


template<typename T>
class lockfree_queue{
    atomic<node<T>*> head, tail;
    public:
        lockfree_queue() = default;
        void push(T val){
            node<T>* old_head, new_node = new node<T>{val, nullptr};
            do{
                old_head = head.load(memory_order_acquire);
            }while (!head.compare_exchange_weak(old_head, new_node));
        }
        T front(){
            if(!head) return NULL;
            return head->val;
        }
        void pop(){

        }
};

int main(){
    lockfree_stack<int> s;
    s.push(11);
    s.push(22);
    s.push(33);
    int i = 3;
    while(i--){
        cout << s.pop() << endl;
    }
}