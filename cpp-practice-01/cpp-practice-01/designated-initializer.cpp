#include <iostream>

/*
1. aggregate initialization�� Ȯ����.
-> ����, �⺻������ aggregate initialization�� ������ �����ؾ��Ѵ�.

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
	MyStruct s_1(1, 1.1, 2); // ������ �ʱ�ȭ ���.
	
	
	MyStruct s_2{ .x = 1, .y = 1.1, .z = 2 }; // ���� �̸��� ���� ������ �� �ִ�.

	
	MyStruct s_3{ .x = 1, .z = 4 }; // �Ϻ� ������ ������ �� �ִ�.
	
	
	MyStruct s_4 = { .x = 2, .y = 2.2 }; // copy initialization�� ����.
	

	MyStruct s_5{ .x = 1, .z = 4 , .y = 3.3}; // error. ��� �ʱ�ȭ ������ �ٲ� �� ����.
	
}