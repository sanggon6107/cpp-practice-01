#include <iostream>

/*
1. aggregate initialization의 확장판.
-> 따라서, 기본적으로 aggregate initialization의 조건을 만족해야한다.

2. aggregate initialization


An aggregate is one of the following types:

- array type
- class type (typically, struct or union), that has
	no private or protected direct (since C++17)non-static data members
	no user-declared constructors
	(until C++11)

	no user-provided constructors (explicitly defaulted or deleted constructors are allowed)
	(since C++11)
	(until C++17)

	no user-provided, inherited, or explicit constructors (explicitly defaulted or deleted constructors are allowed)
	(since C++17)
	(until C++20)

	no user-declared or inherited constructors
	(since C++20)

	no virtual, private, or protected (since C++17) base classes

	no virtual member functions

	no default member initializers
	(since C++11)
	(until C++14)


*/



struct MyStruct
{
	int x;
	double y;
	int z;
};


int main()
{
	MyStruct s_1(1, 1.1, 2); // 기존의 초기화 방법.
	
	
	MyStruct s_2{ .x = 1, .y = 1.1, .z = 2 }; // 변수 이름을 직접 지정할 수 있다.

	
	MyStruct s_3{ .x = 1, .z = 4 }; // 일부 변수는 생략할 수 있다.
	
	
	MyStruct s_4 = { .x = 2, .y = 2.2 }; // copy initialization도 가능.
	

	MyStruct s_5{ .x = 1, .z = 4 , .y = 3.3}; // error. 멤버 초기화 순서는 바꿀 수 없다.
	
}