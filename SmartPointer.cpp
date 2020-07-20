#include <iostream>
using namespace std;

template <typename T> // forward declaration
class counter_ptr;

template <typename T>
class int_array_cell {
    friend class counter_ptr<T>;

    int_array_cell(T* arr)
        : _memory(arr)
        , _counter(1)
    {

        cout << "int_array_cell is allocated\n";
    }
    ~int_array_cell()
    {
        --_counter;
        if (_counter == 0) {
            delete[] _memory;
            _memory = nullptr;
            cout << "int_array_cell counter 0: deleted\n";
        } else {
            cout << "int_array_cell counter is decreased: counter " << _counter << '\n';
        }
    }
    int _counter;
    T* _memory;
};

template <typename T>
class counter_ptr {
public:
    counter_ptr(const char* name, T* arr)
        : _name(name)
    {
        _cell_ptr = new int_array_cell(arr);
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->_counter << "\n";
    }
    counter_ptr(const char* name)
        : _name(name)
    {
        _cell_ptr = nullptr;
        cout << "counter_ptr " << _name << " is not assigned to an int_array_cell\n";
    }
    ~counter_ptr()
    {
        cout << "counter_ptr " << _name << " is deleted\n";
        delete _cell_ptr;
        _cell_ptr = nullptr;
    }
    T& operator[](const T& idx)
    {
        return _cell_ptr->_memory[idx];
    }
    void operator=(counter_ptr& that)
    {
        if (!_cell_ptr) {
            delete _cell_ptr;
        }
        _cell_ptr = that._cell_ptr;
        ++_cell_ptr->_counter;
        cout << "int_array_cell counter is increased: counter " << _cell_ptr->_counter << "\n";
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->_counter << '\n';
    }
    void operator=(T* arr)
    {
        delete _cell_ptr;
        _cell_ptr = new int_array_cell(arr);
        cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->_counter << "\n";
    }
    void release()
    {
        delete _cell_ptr;
        _cell_ptr = nullptr;
        cout << "counter_ptr " << _name << " is not assigned to an int_array_cell\n";
    }

private:
    const char* _name;
    int_array_cell<T>* _cell_ptr;
};

int main()
{

    // PART 一  (40分)

    counter_ptr<int> b("b", new int[10]);
    // stdout 輸出: int_array_cell is allocated
    // stdout 輸出: counter_ptr b is assigned to an int_array_cell: counter 1

    {
        cout << "\tEntering new scope\n";
        b = new int[100];
        // stdout 輸出: int_array_cell counter 0: deleted
        // stdout 輸出: int_array_cell is allocated
        // stdout 輸出: counter_ptr b is assigned to an int_array_cell: counter 1

        counter_ptr<int> a("a");
        // stdout 輸出: counter_ptr a is not assigned to an int_array_cell

        a = b;
        // stdout 輸出: int_array_cell counter is increased: counter 2
        // stdout 輸出: counter_ptr a is assigned to an int_array_cell: counter 2
        cout << "\tLeaving new scope\n";
    }
    // a leaves it scope:
    // stdout 輸出: counter_ptr a is deleted
    // stdout 輸出: int_array_cell counter is decreased: counter 1

    // PART 二  (40分)

    for (int i = 0; i < 10; i++)
        b[i] = i;

    for (int i = 0; i < 10; i++)
        cout << b[i] << ' ';
    cout << endl;
    // stdout 輸出 : 0 1 2 3 4 5 6 7 8 9

    counter_ptr<int> c("c");
    // stdout 輸出: counter_ptr c is not assigned to an int_array_cell

    c = b;
    // stdout 輸出: int_array_cell counter is increased: counter 2
    // stdout 輸出: counter_ptr c is assigned to an int_array_cell: counter 2

    b.release();
    cout << "Main end\n";
    // stdout 輸出: int_array_cell counter is decreased: counter 1
    // stdout 輸出: counter_ptr b is not assigned to an int_array_cell
}

// stdout 輸出: counter_ptr c is deleted
// stdout 輸出: int_array_cell counter 0: deleted
// stdout 輸出: counter_ptr b is deleted

/*
PART 三 (20分)
	1) 用 template 改寫 class counter_ptr
	2) 重覆 PART 一  二 的測試
*/

/*
PART 四 (20分)
用 template counter_ptr 寫 stack

1.	輸入資料為BIG5漢字(character)：
		BIG5內碼包含兩個位元組
		例子:
		我	內碼 (-89 -38)

2. 輸入資料功能：
用I開頭表示 


3.	列印stack資料功能:
用P開頭表示 


4.	列印stack料內碼功能:
用B開頭表示 

	依照r順序將目前的資料的BIG5內碼列印出來 
	例子:
	stack資料順序
	我是		
	內碼列印 =>	 
	(-89 -38) (-84 79)

5.	拿一個資料
用R表示 

6.	完全清除stack資料功能
用C表示 

7. 查尋資料功能:
用?開頭表示 
	查尋一個BIG5漢字是否在stack中：
	結果:	是		否


=======================================================================
test example
I 程式必須要能讀入測試檔
I 程式要徹底清除樹中資料使用的記憶體
? 程
? 體
R
? 程
? 體
P
B
C
P
I 程式要徹底清除樹中資料使用的記憶體
P
B
? 讀
=======================================================================
 

*/