#include <iostream>

using namespace std;

/*
template<typename .. > �κк���
Class< ... > �κ��� �� �߿��ϴ�. ���⼭ �ʿ������ typename�� ������ ������� �ȴ�.
typename�� ��� ������� �Ǵ� ���, �� ���ø��� ��� Ÿ���� Ȯ���ϰ� ������ ��츦 explicit(full) template specialization�̶�� �Ѵ�.
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
class Class<T&&, U>  // �� �κ��� ���� �߿�. �� �κ��� ���� ������ �ݵ�� primary�� ���ƾ� �Ѵ�.
{
public:
    Class(T&& a, U b) { cout << "T&&, U" << endl; }
};

// partial template specialization
template<typename T>
class Class<T&&, T&> // T�� �����Ƿ� U �� �ʿ��������.
{
public:
    Class(T&& a, T& b) { cout << "T&&, T&" << endl; }
};

template<typename T, typename X, typename Y> // �� �κ��� Class ���ø� ������� ����(�Ʒ�)�� ����, �ʿ��� ��ŭ ���´�.
class Class<T&, Class<X, Y>>  // �� �κ��� ���� ���� ������ primary template�� ���ƾ� �Ѵ�.
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