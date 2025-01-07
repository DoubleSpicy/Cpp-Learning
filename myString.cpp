#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstring>

using namespace std;

// a long-short string implementation that is kinda close to libc++
// assume your system is little endian!

class _longStr {
    size_t _cap; // size allocated, smallest bit is long/short str indicator
    size_t _size; // current length
    char *_data;

public:
    _longStr(){
        _size = 0;
        _cap = 0b1111; // 8 with 1 LSB as flag
        _data = new char[8];
    };

    _longStr(char *val){
        _size = strlen(val);
        _cap = _size+1;
        _data = new char[_cap];
        memcpy(_data, val, _size);
        _data[_size+1] = '\0';
    }
    
    size_t size(){
        return _size;
    }
    void operator+=(char c){
        if(_cap - _size <= 1){
            resize(2*_size);
        }
        _size++;
        _data[_size-1] = c;
        _data[_size] = '\0';
    }

    void operator+=(char* c){
        auto newSize = strlen(c) + _size;
        if(_cap - newSize <= 1){
           resize(newSize*2);
        }
        memcpy(_data+_size,c,strlen(c));
        _size = newSize;
        _data[_size] = '\0';
    }

    auto raw(){
        return _data;
    }


private:
    void resize(size_t newSize){
        assert(newSize > 0);
        auto newCap = newSize+1;
        auto newData = new char[newSize+1]; // always reserve 1 more byte for \0
        // copy current data to new
        auto sizeToCopy = min(_size, newSize); // extend or shrink the data
        memcpy(newData, _data, sizeToCopy);
        newData[sizeToCopy+1] = '\0';
        swap(_cap, newSize);
        swap(_data, newData);
        delete [] newData;
    }
};



// class _shortStr{
//     char data[24]; // 1st byte as type flag
//     public:
//         size_t size(){
//             return strlen(data);
//         }
//         void operator+=(const char & c){
//             auto curSize = size();
//             data[curSize+1] = c;
//             data[curSize+2] = '\0';
//         }
//         char* raw(){
//             return &data[1];
//         }
// };

// union _strData{
//     _longStr longStr;
//     _shortStr shortStr;
//     byte raw[24];
// };

// class myStr{
//     _strData rep {  };
//     public:
//         myStr(){
            
//         }
//         char* raw(){
//             return (isLongStr() ? rep.longStr.raw() : rep.shortStr.raw());
//         }
//         size_t size(){
//             if(isLongStr()){
//                 return rep.longStr.size();
//             }
//             else{
//                 return rep.shortStr.size();
//             }
//         }
//         void operator+=(const char c){
//             auto isLongNow = isLongStr();
//             if(isLongNow){
//                 rep.longStr += c;
//             }
//             else if(rep.shortStr.size() < 22){
//                 rep.shortStr += c;
//             }
//         }
//         bool isLongStr(){
//             return strData.raw[0];
//         }
//     private:

// };

// std::ostream& operator<<(std::ostream& os, myStr & s ){
//     // os << s.;
//     os << s.raw();
//     return os;
// }

std::ostream& operator<<(std::ostream& os, _longStr & s ){
    os << s.raw();
    return os;
}


int main(){
    char *word = "abcdefg";
    _longStr ls(word);
    cout << ls << " " << ls.size() <<  endl;
    ls += 'h';
    cout << ls << " after " << ls.size() << " " << strlen(ls.raw()) << endl;

    char *word2 = "123456";
    ls += word2;
    cout << ls << " after3 " << ls.size() << " " << strlen(ls.raw()) << endl;
    // 
}