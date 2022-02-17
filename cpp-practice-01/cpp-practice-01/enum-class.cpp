#include <iostream>
#include <type_traits>
#include <typeinfo>

using namespace std;


enum Color { Yellow, Red, Green };
enum Number { One, Two, Three };

enum class Fruits { Apple, Orange, Banana };


int main()
{
	cout << Color::Yellow << endl;  // enum�� ��ҵ��� �⺻ const int ����Ѵ�.

	if (Color::Yellow == 0)
	{
		cout << typeid(Color::Yellow).name() << endl;
		cout << "Color same" << endl;
	}
	
	if (Color::Yellow == Number::One)
	{
		cout << "Yellow == One" << endl;
	}

	/*if (Fruits::Apple == 0) // error. int ��� �ƴ�.
	{
		cout << "fruits same" << endl;
	}*/
}