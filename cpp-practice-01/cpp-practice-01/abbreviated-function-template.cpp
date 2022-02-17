#include <iostream>
#include <string>

using namespace std;

// C++20 문법. 함수 인자에 auto 써서 템플릿 만들 수 있다.
// 다만 퍼펙트 포워딩에서 decltype을 써야하는 번거로움이 생겼다.

// abbreviated function template
decltype(auto) abb1(auto a, auto b)
{
	return a + b;
}


// perfect forwarding
decltype(auto) abb2(auto&& f, auto&& a)
{
	return invoke(forward<decltype(f)>(f), forward<decltype(a)>(a));
}


// cppreference 예시
//void f1(auto); // same as template<class T>
//void f2(C1 auto); // same as template<C1 T> void f2(T), if C1 is a concept
//void f3(C2 auto...); // same as template<C2... Ts> void f3(Ts...), if C2 is a concept
//void f4(const C3 auto*, C4 auto&); // same as template<C3 T, C4 U> void f4(const T*, U&);

int main()
{
	cout << abb1(1, 2) << endl; // 3
	cout << abb1("string1"s, "string2"s) << endl; // "string1stirng2"
}