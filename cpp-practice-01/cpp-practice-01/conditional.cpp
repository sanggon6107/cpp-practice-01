#include <iostream>

/* conditional : template specialization���� �����Ǿ��ִ�.
1. ������ ������ ���캸�� <>���� ù ��° ��Ұ� false�� ���� specialize�Ͽ�, 
�ش� subset�� �ش�Ǹ� <>���� �� ��° ��Ұ� using�ǵ��� �����ϰ��ִ�.
2. �� ���� ������ primary�� _Ty1�� using �ϰ� �ȴ�.
*/


int main()
{
	std::conditional<false, int, double>::type a = 1.1;

	//template <bool _Test, class _Ty1, class _Ty2>
	//struct conditional { // Choose _Ty1 if _Test is true, and _Ty2 otherwise
	//	using type = _Ty1;
	//};

	//template <class _Ty1, class _Ty2>
	//struct conditional<false, _Ty1, _Ty2> {
	//	using type = _Ty2;
	//};

	//template <bool _Test, class _Ty1, class _Ty2>
	//using conditional_t = typename conditional<_Test, _Ty1, _Ty2>::type;

	std::cout << a << std::endl;

}