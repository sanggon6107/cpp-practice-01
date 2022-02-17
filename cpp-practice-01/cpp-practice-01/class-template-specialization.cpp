#include <iostream>

using namespace std;

/*
template<typename .. > 부분보다
Class< ... > 부분이 더 중요하다. 여기서 필요없어진 typename은 위에서 사라져도 된다.
typename이 모두 사라져도 되는 경우, 즉 템플릿의 모든 타입이 확실하게 정해진 경우를 explicit(full) template specialization이라고 한다.
*/

// primary template
template<typename T, typename U>
class Class
{
public:
    Class(T a, U b) { cout << "T, U" << endl; }
};

// partial template specialization
template<typename T, typename U>
class Class<T&&, U>  // 이 부분이 가장 중요. 이 부분의 인자 개수는 반드시 primary와 같아야 한다.
{
public:
    Class(T&& a, U b) { cout << "T&&, U" << endl; }
};

// partial template specialization
template<typename T>
class Class<T&&, T&> // T만 있으므로 U 는 필요없어진다.
{
public:
    Class(T&& a, T& b) { cout << "T&&, T&" << endl; }
};

template<typename T, typename X, typename Y> // 이 부분은 Class 템플릿 선언부의 인자(아래)를 보고, 필요한 만큼 적는다.
class Class<T&, Class<X, Y>>  // 이 부분의 인자 수는 무조건 primary template와 같아야 한다.
{
public:
    Class(T& a, Class<X, Y> b) { cout << "T&, Class<X, Y>" << endl; }
};


// explicit template specialization
template<>
class Class<double*, int&>
{
public:
    Class(double*, int&) { cout << "double*, int&" << endl; }
};



int main()
{
    int n1 = 1;
    int n2 = 2;
    double d1 = 2.2;
    Class<int, double> c1(1, 2.2);
    Class<int&&, int&> c2(1 + 1, n1);
    Class<int&&, double> c3(1 + 1, d1);
    Class<int&, Class<int, double>> c4(n1, c1);
    Class<double*, int&> c5(&d1, n1);
}