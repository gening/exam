#include <iostream>
#include <vector>
#include <string>

/* Hello World!*/
int main()
{
    std::vector<std::string> msg {"Hello", "C++", "World!"};
    for (const std::string& word : msg)
    {
        std::cout << word << " ";
    }
    std::cout << std::endl;
}

/* Calculate running time.
#include <ctime>
int main()
{
    int k = 0, n = 1e8;
    std::clock_t start, end;
    start = std::clock();
    for(int i = 0; i < n; ++i) ++k;
    end = std::clock();
    std::cout << (double)(end - start) / CLOCKS_PER_SEC << std::endl;
}
*/

/* Initialise a vector
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::fill(v.begin(), v.end(), -1);
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}
*/

/* Stack of characters
#include <iostream>
#include <stack>

int main() {
    char ch;
    std::stack<char> s;
    while(true) {
        //std::cin >> ch; // 此处不能使用cin，空格无法输入。
        ch = std::getchar();
        if(ch == ' ' || ch == '\n' || ch == EOF) {
            while(!s.empty()){
                std::cout << s.top();
                s.pop();
            }
            if(ch == '\n' || ch == EOF) {
                break;
            } else {
                std::cout << " ";
            }
        } else {
            s.push(ch);
        }
    }
    std::cout << std::endl;
    return 0;
}
*/

/* Max Area of Rectangular
#include <stack>
int GetMaxRectangular(int hist[], int n){
    std::stack<int> s;
    s.push(-1);
    int height, top, area, maxArea = 0;
    for(int i = 0; i <= n; ++i) {
        height = i==n ? -1 : hist[i];
        while(s.top() >= 0 && height < hist[s.top()]) {
            top = s.top();
            s.pop();
            // rightIndex = i, leftIndex = s.top();
            area = hist[top] * (i - s.top() -1);
            if(area > maxArea) {
                maxArea = area;
            }
        }
        s.push(i);
    }
    return maxArea;
}

int main() {
    int hist[] = {3, 2};
    std::cout << GetMaxRectangular(hist, 2) << std::endl;
    return 0;
}
*/

/* Template specialization
void f(std::vector<int> & v) {
    std::cout << "&" << std::endl;
}

void f(const std::vector<int> & v) {
    std::cout << "const &" << std::endl;
}

void f(std::vector<int> && v) {
    std::cout << "&&" << std::endl;
}

template<typename T>
void f()
{
    std::conditional<std::is_pod<T>::value, int, char> x;
}


template<typename Head, typename... Tail>
Head head(std::tuple<Head, Tail...>& t)
{
    return std::get<0>(t);
}

template<typename Head, typename... Tail>
std::tuple<Tail&...> tail(std::tuple<Head, Tail...>& t)
{
    return std::tuple<Tail&...> {};
}


template<typename Head, typename... Tail>
class Tup : private Tup<Tail...>
{
    using Base = Tup<Tail...>;
public:
    constexpr Tup() { }

    Tup(Head v, Tail... vtail)
        : Base{vtail...}
        , m_head{v}
    { }

    template<typename... VValues>
    Tup(const Tup<VValues...>& other)
        : Base{other.tail()}
        , m_head{other.head()}
    { }

    template<typename... VValues>
    Tup& operator=(const Tup<VValues...>& other)
    {
        m_head = other.head();
        tail() = other.tail();
        return *this;
    }

protected:
    Head m_head;

private:
    Head& head() { return m_head; } 
    const Head& head() const { return m_head; }
    Base& tail() { return *this; }
    const Base& tail() const { return *this; }
};


template<typename Head>
class Tup<Head>  {
public:
    constexpr Tup() { }

    Tup(Head v)
        : m_head(v){ }

    template<typename VValues>
    Tup(const Tup<VValues>& other)
        : m_head(other.head()){ }

    template<typename VValues>
    Tup& operator=(const Tup<VValues>& other) {
        m_head = other.head();
        return *this;
    }

protected:
    Head m_head;

private:
    Head& head() { return m_head; } 
    const Head& head() const { return m_head; }
};

template<>
class Tup<> {
    Tup() {}
};



int main() {
    //f(std::vector<int> {1, 2, 3,});
    Tup<std::string, int, char> {"a", 2, 'c'};
}
*/