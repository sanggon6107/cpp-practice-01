#include <vector>
#include <cstring>
#include <iostream>
#include <crtdbg.h>

namespace std {
	class StringVector {

	public:
		StringVector() = default; //  초기값 없이 선언만 했을 때.
		StringVector(const char* b) { // 초기화 하지 않을 때 0.
			// char* b 자체는 스택에 있고, 문자열의 첫 번째 요소의 메모리 주소를 담고 있을 것이다.
			// buff는 vector이므로, 그 안에 각 자리 글자들의 주소를 역참조하여 대입할 수 있다.
			// push_back : 주소가 얕은 복사 되는 것인지 확인 필요하다. ->  어차피 복사하는 것 뿐이고, 읽기 전용이라면 상관 없지 않나?? 그냥 복사해도 될 듯! -> 문제는 대입 연산자.
			// 결국 strlen을 써야하는가? -> b의 크기를 재야 넣을 수 있나?

			int i = 0;
			int size = strlen(b) + 1;
			for (i = 0; i < size; i++) {
				buff_.push_back(*b);
				++b;
			}
		}

		~StringVector() = default;

		StringVector(const StringVector& string_vector) {    // 마지막 수정 :  const 추가.
			buff_.assign(std::begin(string_vector.buff_), std::end(string_vector.buff_));
		}

		StringVector& operator=(const StringVector& string_vector) {
			if (this == &string_vector) {
				return *this;
			}

			buff_.assign(std::begin(string_vector.buff_), std::end(string_vector.buff_));
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const std::StringVector& string_vector);
		friend StringVector operator+(const std::StringVector& string_vector1, const std::StringVector& string_vector2);

	private:
		std::vector<char> buff_;
	};

	std::ostream& operator<<(std::ostream& os, const std::StringVector& string_vector) { // std:: 정리.
		auto string_begin = std::begin(string_vector.buff_);
		auto string_end = std::end(string_vector.buff_);

		while (string_begin != string_end) {
			os << *(string_begin);
			++string_begin;
		}
		return os;
	}

	std::StringVector operator+(const std::StringVector& string_vector1, const std::StringVector& string_vector2) {
		std::StringVector temp;

		(temp.buff_).assign(std::begin(string_vector1.buff_), std::end(string_vector1.buff_));
		(temp.buff_).insert(std::end(temp.buff_), std::begin(string_vector2.buff_), std::end(string_vector2.buff_));

		return temp;
	}
}
// 생성자.
// 복사생성자(대입, 복사)
// 대입 연산자
// +연산
// 초기화 하지 않아도 스트링 선언할 수 있도록?



int main() {

	_CrtMemState s, e, d;
	_CrtMemCheckpoint(&s);

	std::StringVector s1;
	s1 = "STRING_1";
	std::StringVector s2 = "STRING_2";
	std::StringVector s3 = s1 + "STRING_3" + s2;
	s1 = s3;


	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	std::cout << s3 << std::endl;

	s1.~StringVector();
	s2.~StringVector();
	s3.~StringVector();

	_CrtMemCheckpoint(&e);
	if (_CrtMemDifference(&d, &s, &e)) {
		_CrtDumpMemoryLeaks();
		printf("leaks : %d\n", (int)d.lSizes[1]);
	}
	else printf("perfect!\n");
}