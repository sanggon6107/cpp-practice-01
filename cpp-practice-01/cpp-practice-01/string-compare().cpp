#include <iostream>

using namespace std;

/* string::compare() �Լ�.

1. string�� ���ڿ��� ���Ѵ�.

2. �� ����� �ڽź��� ������ ������ �ռ��� 1, �ڿ� ���� -1,
�� ���ڿ��� ������ 0�� ��ȯ�Ѵ�.

3. �پ��� �����ε��� �����ϴµ�, substring�� �񱳵� �����ϴ�.

*/


int main()
{
	string bat = "batman";
	string sup = "superman";

	// 1.
	if (!bat.compare(sup)) { cout << "not same" << endl; }

	// 2.
	if (bat.compare(sup) > 0) { cout << "superman comes before batman." << endl; }
	else if (bat.compare(sup) < 0) { cout << "batman comes before superman" << endl; }

	// 3.
	if (bat.compare(3, 3, sup, 3, 3) > 0) { cout << "erm comes before man" << endl; } // [3, 3 + 3)�� �������� ��.
	if (bat.compare(0, 3, bat, 1, 3) > 0) { cout << "atm comes before bat" << endl; }
	
}