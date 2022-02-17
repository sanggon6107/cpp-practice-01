#include <iostream>
#include <string>

using namespace std;

/*
reference collapsing과 template specialization을 응용한
value sorter.
인자가 lvalue이면 false, rvalue이면 true를 반환한다.
*/

template<typename T>
class Value
{
public:
    static constexpr bool value = true;
};

template<typename T>
class Value<T&>
{
public:
    static constexpr bool value = false;
};

template<typename A>
decltype(auto) ValueSorter(A&& a) { return Value<A>().value; }

int main()
{
    int a = 1;
    int& b = a;
    cout << boolalpha
        << ValueSorter(a) << endl
        << ValueSorter(b) << endl
        << ValueSorter(move(a)) << endl
        << ValueSorter(1 + 1) << endl
        << ValueSorter("string"s) << endl;
}
