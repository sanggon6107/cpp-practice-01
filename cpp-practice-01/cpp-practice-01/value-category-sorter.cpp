#include <iostream>
#include <string>

using namespace std;

/*
reference collapsing�� template specialization�� ������
value sorter.
���ڰ� lvalue�̸� false, rvalue�̸� true�� ��ȯ�Ѵ�.
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
