#include <iostream>

/* conditional : template specialization으로 구현되어있다.
1. 구현된 내용을 살펴보면 <>내의 첫 번째 요소가 false인 경우로 specialize하여, 
해당 subset에 해당되면 <>안의 세 번째 요소가 using되도록 구현하고있다.
2. 그 외의 내용은 primary인 _Ty1을 using 하게 된다.
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