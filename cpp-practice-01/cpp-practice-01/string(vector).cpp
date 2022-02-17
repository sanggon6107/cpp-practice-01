#include <vector>
#include <cstring>
#include <iostream>
#include <crtdbg.h>

namespace std {
	class StringVector {

	public:
		StringVector() = default; //  �ʱⰪ ���� ���� ���� ��.
		StringVector(const char* b) { // �ʱ�ȭ ���� ���� �� 0.
			// char* b ��ü�� ���ÿ� �ְ�, ���ڿ��� ù ��° ����� �޸� �ּҸ� ��� ���� ���̴�.
			// buff�� vector�̹Ƿ�, �� �ȿ� �� �ڸ� ���ڵ��� �ּҸ� �������Ͽ� ������ �� �ִ�.
			// push_back : �ּҰ� ���� ���� �Ǵ� ������ Ȯ�� �ʿ��ϴ�. ->  ������ �����ϴ� �� ���̰�, �б� �����̶�� ��� ���� �ʳ�?? �׳� �����ص� �� ��! -> ������ ���� ������.
			// �ᱹ strlen�� ����ϴ°�? -> b�� ũ�⸦ ��� ���� �� �ֳ�?

			int i = 0;
			int size = strlen(b) + 1;
			for (i = 0; i < size; i++) {
				buff_.push_back(*b);
				++b;
			}
		}

		~StringVector() = default;

		StringVector(const StringVector& string_vector) {    // ������ ���� :  const �߰�.
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

	std::ostream& operator<<(std::ostream& os, const std::StringVector& string_vector) { // std:: ����.
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
// ������.
// ���������(����, ����)
// ���� ������
// +����
// �ʱ�ȭ ���� �ʾƵ� ��Ʈ�� ������ �� �ֵ���?



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