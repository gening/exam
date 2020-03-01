//
// Created by Ning Ge on 2018/7/12.
//

#include <string>
#include <vector>
#include <iostream> // cout
#include <gtest/gtest.h>

using namespace std; //在工程中不推荐使用 using namespace 命名空间; 的指令

struct Event {
    bool onA;
    bool onB;
};

static Event events[] = { {true, true}, {false, false}, {true, false}, {false, true} };

bool LookupEvent(Event &e) {
    e = events[3];
    return true;
}

bool CallEvent() {
    Event thisEvent;
    LookupEvent(thisEvent);
    bool ret = thisEvent.onA;
    return ret;
}

void PrintEvent() {
    bool ret = CallEvent();
    cout << ret << endl;
}

TEST(Class, PrintEvent) {
    PrintEvent();
}

// Copy constructor
struct Entity {
    string Name = "unknown";
    int Number = -1;
    vector<int> Key = {0, 0};

    // 构造函数
    Entity() = default;

    // 析构函数
    ~Entity() = default;

    // 拷贝构造函数
    // Entity(const Entity &) = delete;

    // 拷贝赋值函数
    // Entity &operator=(const Entity &) = delete;
};

void PrintEntity(Entity &e) {
    cout << "Name:   " << e.Name << endl;
    cout << "Number: " << e.Number << endl;
    cout << "Key:    ";
    for (int key : e.Key) {
        cout << key << " ";
    }
    cout << endl << endl;
}

void MakeEntity() {
    Entity e;
    PrintEntity(e);
    e.Name = "Studnet";
    e.Number = 2018;
    e.Key.push_back(1);
    e.Key.push_back(1);
    PrintEntity(e);
    Entity f = e;  // compile error: all to deleted constructor
    // Entity f;
    PrintEntity(f);
    f.Name = "Teacher";
    f.Number = 1024;
    f.Key.pop_back();
    f.Key.push_back(9);
    f.Key.push_back(9);
    PrintEntity(f);
    PrintEntity(e);
    cout << "e.Key == f.Key: " << (e.Key == f.Key ? "true" : "false") << endl;
}

TEST(Class, MakeEntity) {
    MakeEntity();
}

// Pointer being freed was not allocated
void InvalidFree() {
    const char *c1 = nullptr;
    auto *p = new char[20];
    strcpy(p, "Xhis is a string!");
    p[0] = 'T';
    c1 = p;
    // c1[0] = 't';  // compile error: c1 is readonly pointer.
    cout << c1 << endl;
    delete[] c1;

    const char *c2 = nullptr;
    c2 = "This is a string!";
    cout << c2 << endl;
    // Cannot be deleted
    // delete[] c2;  // runtime error
}

TEST(Memory, InvalidFree) {
    InvalidFree();
}

// Life time of c_str
const char *ReturnCstr(char *p1) {
    string s1 = p1;
    const char *c1 = s1.c_str();
    return c1;
    // end the lifetime of s1
}

string ReturnString(char *p3) {
    string s3 = p3;
    return s3;
    // end the lifetime of s3
}

void MissingString() {
    const char *c0 = "This is a string.";

    auto *p1 = new char[strlen(c0) + 1];
    strcpy(p1, c0);
    cout << "Valid   char*  1: " << p1 << endl;
    const char *c1 = ReturnCstr(p1);
    // Beyond the lifetime of c1
    // Valgrind: invalid read of memory of c1 from now on!
    cout << "Invalid string 1: " << c1 << endl;
    cout << "Valid   char*  1: " << p1 << endl;
    // Simulate the destructor of another class
    strcpy(p1, "Deleted!");
    delete[] p1;
    // Valgrind: invalid read of memory of p1 from now on!
    cout << "Invalid char*  1: " << p1 << endl;
    cout << "Invalid string 1: " << c1 << endl;

    auto *p2 = new char[strlen(c0) + 1];
    strcpy(p2, c0);
    cout << "Valid   char*  2: " << p2 << endl;
    string s2 = p2;
    const char *c2 = s2.c_str();
    cout << "Valid   string 2: " << c2 << endl;
    // Simulate the destructor of another class
    strcpy(p2, "Deleted!");
    delete[] p2;
    cout << "Valid   string 2: " << c2 << endl;


    auto *p3 = new char[strlen(c0) + 1];
    strcpy(p3, c0);
    cout << "Valid   char*  3: " << p3 << endl;
    string s4 = ReturnString(p3);
    const char *c4 = s4.c_str();
    cout << "Valid   string 4: " << c4 << endl;
    // Simulate the destructor of another class
    strcpy(p3, "Deleted!");
    delete[] p3;
    cout << "Valid   string 4: " << c4 << endl;

    // end the lifetime of s2
    // end the lifetime of s4
}

TEST(Cast, MissingString) {
    MissingString();
}

// CastString
void CastString() {
    // string
    string s1 = "This is the string.";
    // --> const char*
    const char *c1 = s1.c_str();
    // --> char *
    auto *p1 = const_cast<char *>(s1.c_str());
    // --> char[]
    char a1[11] = {0};  // 未赋值部分自动设为0
    for (int i = 0; i < s1.length() && i < sizeof(a1) - 1; ++i) {
        a1[i] = s1[i];
    }
    cout << "Cast string: " << c1 << endl;
    cout << "Cast string: " << p1 << endl;
    cout << "Cast string: " << a1 << endl;

    // const char*
    // char * const [const修饰的是指针，代表不能改变指针]
    // const char * [const修饰的是char，代表字符不能改变，但是指针可以变]
    const char *c2 = "This is the const char*.";
    // --> string
    string s2 = c2;
    // --> char*
    // static_cast from 'const char *' to 'char *' is not allowed
    // auto *p2 = static_cast<char *>(c2);
    auto *p2 = const_cast<char *>(c2);
    // --> char[]
    char a2[11] = {0};
    strncpy(a2, c2, sizeof(a2) - 1);
    cout << "Cast const char*: " << s2 << endl;
    cout << "Cast const char*: " << p2 << endl;
    cout << "Cast const char*: " << a2 << endl;

    // char*
    // char* 是一个char型指针变量，其值（指向）可以改变。
    // char* 指向的区域有时可写，有时只读。
    // ISO C++11 does not allow conversion from string literal to 'char *'
    // char *p3 = "This is a char *.";
    // 这时指向的是一个字符串常量，即指向的内存区域只读。一旦strcpy(p3,”string2”)试图向只读的内存区域写入，程序会崩溃.
    auto *p3 = const_cast<char *>("This is the char *.");
    // --> string
    string s3 = p3;
    // --> const char*
    const char *c3 = p3;
    // --> char[]
    char a3[11] = {0};
    // Array is not assignable: a3 = p3; // error
    strncpy(a3, c3, sizeof(a3) - 1);
    cout << "Cast char*: " << s3 << endl;
    cout << "Cast char*: " << c3 << endl;
    cout << "Cast char*: " << a3 << endl;

    // char[]
    // char[] 是一个char型数组的名字，也是该数组首元素的地址，是常量，其值不可以改变。
    // char[] 对应的内存区域总是可写。
    char a4[] = "This is the char[].";
    // --> string
    string s4 = a4;
    // --> const char*
    const char *c4 = a4;
    // --> char*
    char *p4 = a4;
    cout << "Cast char[]: " << s4 << endl;
    cout << "Cast char[]: " << c4 << endl;
    cout << "Cast char[]: " << p4 << endl;
}

TEST(Cast, CastString) {
    CastString();
}

// CastEnum
void Print(int i) {
    cout << "int: " << i << endl;
}

void Print(char c) {
    cout << "char: " << c << endl;
}

void CastEnum() {
    enum ColorInt : int {
        White = 0,
        Black = 255
    };
    enum ColorCh : char {
        Red = 'R',
        Green = 'G',
        Blue = 'B'
    };

    // 可兼容的类型转换用static_cast即可
    Print(static_cast<int>(ColorInt::Black));
    Print(static_cast<char>(ColorCh::Green));
}

TEST(Cast, CastEnum) {
    CastEnum();
}

// 数组仅在定义其的范围内可确定大小
// sizeof on array function parameter will return size of 'int *' instead of 'int []'
// 用'const int * arrB'代替'int arrB[]'作为参数，并配合size参数使用
void ReferArraySize(int (&arrA)[3], const int *arrB, int arrBSize) {
    cout << "Refer   sizeof arrA = " << sizeof arrA << endl;
    cout << "Refer   sizeof arrB = " << sizeof arrB << endl;
    cout << "Refer   sizeof arrB = " << arrBSize << endl;
}

void DeclareArraySize() {
    int arrA[3] = {0, 2, 4};
    int arrB[3] = {1, 3, 5};
    cout << "Declare sizeof arrA = " << sizeof arrA << endl;
    cout << "Declare sizeof arrB = " << sizeof arrB << endl;
    ReferArraySize(arrA, arrB, 1);
}

TEST(Array, DeclareArraySize) {
    DeclareArraySize();
}

void ReferenceRightValue() {
    string s1 = "Test";
    // non-const lvalue reference cannot bind to a temporary value
    // string& r2 = s1 + s1;  // 左值需要在内存中有实体 ，而不能指向临时变量。
    const string& r2 = s1 + s1;  // 可行：到常值的左值引用延长生存期
    // 右值引用可以转为 const 修饰的左值引用
    // 右值在CPU寄存器中
    string&& r3 = s1 + s1;  // 可行：右值引用延长生存期
    r3 += "Test";  // 可行：右值引用延长生存期
    cout << s1 << endl;
    cout << r2 << endl;
    cout << r3 << endl;
}

TEST(Reference, ReferenceRightValue) {
    ReferenceRightValue();
}

// main
int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
