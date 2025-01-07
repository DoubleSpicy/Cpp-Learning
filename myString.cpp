#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstring>

using namespace std;

// a long-short string implementation that is kinda close to libc++
// short string is pre-allocated 24 bytes in stack
// heap-using long string is converted when necessary
// IMPORTANT: assume your system is little endian!

class _longStr {
    size_t _cap; // size allocated, smallest bit is long/short str indicator
    size_t _size; // current length
    char *_data;

public:
    _longStr(){
        init();
    };

    _longStr(char *val){
        _size = strlen(val);
        _data = new char[_size+1];
        memcpy(_data, val, _size+1);
        _data[_size+1] = '\0';
        saveCap(_size+1);
    }

    constexpr void init(){
        _size = 0;
        _cap = 0b1111; // 8 with 1 LSB as flag
        _data = new char[8];
        _data[0] = '\0';
    }
    
    inline size_t size(){
        return _size;
    }

    inline void operator+=(char c){
        if(getCap() - _size <= 1){
            resize(2*_size);
        }
        _size++;
        _data[_size-1] = c;
        _data[_size] = '\0';
    }

    inline void operator+=(char* c){
        auto newSize = strlen(c) + _size;
        if(getCap() - newSize <= 1){
           resize(newSize*2);
        }
        memcpy(_data+_size,c,strlen(c));
        _size = newSize;
        _data[_size] = '\0';
    }
    

    inline auto raw(){
        return _data;
    }

    inline void clear(){
        // clean all contents to default state
        delete [] _data;
        init();
    }


private:
    inline void resize(size_t newSize){
        assert(newSize > 0);
        auto newData = new char[newSize+1]; // always reserve 1 more byte for \0
        // copy current data to new
        auto sizeToCopy = min(_size, newSize); // extend or shrink the data
        memcpy(newData, _data, sizeToCopy);
        newData[sizeToCopy+1] = '\0';
        saveCap(newSize+1);
        swap(_data, newData);
        delete [] newData;
    }

    inline size_t getCap(){
        return _cap >> 1;
    }

    inline void saveCap(size_t num){
        // store a 31-bit number with LSB flag = 0b1
        constexpr size_t limit = (~0b0) - 1;
        assert(num <= limit);
        _cap = ((num << 1) | 0b1);
    }
};



class _shortStr{
    char data[24]; // 1st byte as type flag
public:
        _shortStr(){
            init();
        }
        _shortStr(char* c){
            init();
            *this+=c;
        }
        inline size_t size(){
            return strlen(raw());
        }
        inline void operator+=(char c){
            assert(size() < 23);
            auto curSize = size();
            raw()[curSize+1] = c;
            raw()[curSize+2] = '\0';
        }
        inline void operator+=(char* c){
            auto newSize = size() + strlen(c);
            assert(newSize <= 23);
            auto curSize = size();
            memcpy(raw()+size(), c, strlen(c));
            raw()[newSize] = '\0';
        }
        inline char* raw(){
            return &data[1];
        }
        inline void clear(){
            init();
        }
private:
    constexpr void init(){
        memset(data, 0, 24);
        data[2] = '\0';
    }
};

union _strData{
    _longStr longStr;
    _shortStr shortStr;
    byte raw[24];
};

class myStr{
    _strData rep {  };
    public:
        myStr(){
            
        }

        myStr(const _shortStr & s){
            rep.shortStr = s;
        }

        myStr(const _longStr & s){
            rep.longStr = s;
        }

        inline char* raw(){
            return (isLongStr() ? rep.longStr.raw() : rep.shortStr.raw());
        }
        inline size_t size(){
            if(isLongStr()){
                return rep.longStr.size();
            }
            else{
                return rep.shortStr.size();
            }
        }
        inline void operator+=(const char c){
            auto isLongNow = isLongStr();
            if(isLongNow){
                rep.longStr += c;
            }
            else if(rep.shortStr.size() < 22){
                rep.shortStr += c;
            }
            else{
                // convert short str to long, then add the char
                convert2long();
                rep.longStr += c;
            }
        }

        inline void operator+=(char* c){
            auto isLongNow = isLongStr();
            auto len = strlen(c);
            if(size() + len <= 22){
                rep.shortStr += c;
                return;
            }
            if(size() + len > 22)
                convert2long();
            rep.longStr += c;
        }

        inline bool isLongStr(){
            constexpr byte flag {1};
            return (rep.raw[0] & flag) == flag;
        }

        inline void clear(){
            isLongStr() ? rep.longStr.clear() : rep.shortStr.clear();
        }
    private:
        void convert2long(){
            assert(!isLongStr());
            auto size = rep.shortStr.size();
            auto heapData = new char[size+1];
            memcpy(heapData, rep.shortStr.raw(), size+1);
            // low-level operations writing byte data as longStr representation
            auto capAddr = reinterpret_cast<size_t*>(&rep.raw[0]);
            *capAddr = (((size+1) << 1) | 0b1);
            auto sizeAddr = reinterpret_cast<size_t*>(&rep.raw[sizeof(size_t)]);
            *sizeAddr = size;
            auto dataAddr = reinterpret_cast<char**>(&rep.raw[sizeof(size_t)*2]);
            *dataAddr = heapData;
        }
};

std::ostream& operator<<(std::ostream& os, myStr & s ){
    os << s.raw();
    return os;
}

std::ostream& operator<<(std::ostream& os, _longStr & s ){
    os << s.raw();
    return os;
}

std::ostream& operator<<(std::ostream& os, _shortStr & s ){
    os << s.raw();
    return os;
}


void testLongStr(){
    char *word = "abcdefg"; // abcdefg
    _longStr ls(word);
    cout << ls << " " << ls.size() <<  endl;
    ls += 'h';
    cout << ls << " after " << ls.size() << " " << strlen(ls.raw()) << endl; // abcdefgh

    char *word2 = "123456";
    ls += word2;
    cout << ls << " after3 " << ls.size() << " " << strlen(ls.raw()) << endl; // abcdefgh123456

    ls.clear();
    cout << ls << " after clear " << ls.size() << " " << strlen(ls.raw()) << endl; // empty string

    int multiplyHowManyTimes = 3;
    while(multiplyHowManyTimes--){
        ls += "123456|";
    }
    cout << ls << " after add " << ls.size() << " " << strlen(ls.raw()) << endl; // 123456|123456|123456|

    cout << "sizeof ls = " << sizeof(ls) << '\n';
}

void testShortStr(){
    _shortStr ss("123456");
    cout << ss << ", len is " << ss.size() <<  endl; // 123456|, len is 6
    ss += "789";
    cout << ss << ", len is " << ss.size() <<  endl; // 123456789, len is 9
    ss.clear(); 
    cout << ss << ", len is " << ss.size() <<  endl; //  , len is 0

    ss += "12345678912345678912345"; // 23 chars, OK
    cout << ss << ", len is " << ss.size() <<  endl; // 12345678912345678912345 , len is 23
    // ss += "6"; // 24 chars will overflow!
    ss.clear();
}

string typeHelper(myStr & s){
    return (s.isLongStr() ? " long str " : " short str ");
}

void testMyStr(){
    char *word = "abcdefg"; // abcdefg
    _longStr ls(word);
    _shortStr ss("123456");

    myStr s1(ls), s2(ss);

    cout << "s1 is" << typeHelper(s1) << ", s2 is" << typeHelper(s2) << '\n';  // long and short
    cout << "values are: " << s1 << ", " << s2 << endl;

    s2.clear();
    int multiplyHowManyTimes = 3;
    while(multiplyHowManyTimes--){
        s2 += "123456789";
    }
    cout << "s2 is" << typeHelper(s2) << ", values = " << s2 << ", size = " << s2.size() << '\n';  // long and short
}

int main(){
    printf("=====TEST LONG STR======\n");
    testLongStr();
    printf("===============\n\n");
    printf("=====TEST SHORT STR======\n");
    testShortStr();
    printf("===============\n\n");
    printf("=====TEST MY STR======\n");
    testMyStr();
    printf("===============\n\n");
}