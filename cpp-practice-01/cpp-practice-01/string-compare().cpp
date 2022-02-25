#include <iostream>

using namespace std;

/* string::compare() 함수.

1. string의 문자열을 비교한다.

2. 비교 대상이 자신보다 사전적 순위가 앞서면 1, 뒤에 오면 -1,
두 문자열이 같으면 0을 반환한다.

3. 다양한 오버로딩을 제공하는데, substring의 비교도 가능하다.

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
	if (bat.compare(3, 3, sup, 3, 3) > 0) { cout << "erm comes before man" << endl; } // [3, 3 + 3)의 범위끼리 비교.
	if (bat.compare(0, 3, bat, 1, 3) > 0) { cout << "atm comes before bat" << endl; }
	
}