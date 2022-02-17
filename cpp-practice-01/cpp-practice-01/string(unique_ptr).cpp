#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <cstring>
#include <crtdbg.h> 

// ������.
// ���������(����, ����)
// ���� ������
// +����
// �ʱ�ȭ ���� �ʾƵ� ��Ʈ�� ������ �� �ֵ���?

// unique_ptr : ������� ��� ��� �ȵȴ�. -> ��ī�� ������� �Ѵ�.

// �̵� ������. : �ӽ� ��ü�� �ʱ�ȭ �Ǿ��� ��, �ӽ� ��ü�� �����ǰ�(�ӽ� ��ü�� ������) �װ��� �ƱԸ�Ʈ�� ���鼭 �ٽ� ������ ȣ��ȴ�. ��, �����ڰ� �ߺ� ȣ��ȴ�.
//               �̰��� �����ϴ� ���� move constructor.
// �̵� ���� ������.


namespace std {
	class StringUniquePtr {
	public:
		StringUniquePtr() = default;
		StringUniquePtr(const char* s) : buff_(new char[strlen(s) + 1]) { // constructor.
			std::cout << "������ : �޸� �Ҵ�" << std::endl;
			strcpy(buff_.get(), s);
		}
		StringUniquePtr(const StringUniquePtr& string_unique_ptr) : buff_(new char[strlen(string_unique_ptr.buff_.get()) + 1]) { // ���������. // �̰��� �� ī���ΰ�? // : buff_(new char[strlen(string_unique_ptr.buff_.get())+1])
			std::cout << "��������� : �޸� �Ҵ�" << std::endl;
			strcpy(buff_.get(), string_unique_ptr.buff_.get());  // copy constructor �� constructor : ���?
		}
		~StringUniquePtr() {
			std::cout << "�Ҹ���" << std::endl;
		};

		// �̵� ������. ravlue ref�� �ӽ� ��ü�̴�?
		StringUniquePtr(StringUniquePtr&& string_unique_ptr) noexcept : buff_(std::move(string_unique_ptr.buff_)) { // +�������� ���� �ӽ� ��ü�� �����ǰ�, �� ������ �ʱ�ȭ���� ���.
			std::cout << "�̵� ������ (" << buff_ << ")" << std::endl; ////
		}

		StringUniquePtr& operator=(const StringUniquePtr& string_unique_ptr) {
			std::cout << "���� ������ : �޸� �Ҵ�" << std::endl;
			if (buff_.get() == string_unique_ptr.buff_.get()) {
				return *this;
			};
			this->buff_.reset(new char[strlen(string_unique_ptr.buff_.get()) + 1]);
			strcpy(buff_.get(), string_unique_ptr.buff_.get());
			return *this;
		}

		StringUniquePtr& operator=(StringUniquePtr&& string_unique_ptr) noexcept {
			//�̵� �������� ����? ���� ���� ���� ���� �ʾƵ� �ȴ�. ���� ���� �ӽ� ��ü�̹Ƿ� �׳� �����Ǹ� �Ѱ��ش�.
			//0. ��Ű�� ���ϸ� �̵� ���� �������� ��쵵 �ڽ��� �����ϴ� ��쿡 ���� ó���� �ؾ��Ѵ�.
			//1. ���� ���� ����Ű�� �� �ּ��� �޸𸮸� �����Ѵ�.
			//2. std::move�� string_unique_ptr�� ����Ű�� �ּҸ� �޴´�.
			std::cout << "�̵� ���� ������" << std::endl;
			if (buff_.get() == string_unique_ptr.buff_.get()) {
				return *this;
			};
			buff_ = std::move(string_unique_ptr.buff_); // �ٽ� �޸𸮸� ���Ҵ��� �ʿ� ����, move�� �����Ǹ� ���������� �ȴ�.
			return *this;
		}



		friend ostream& operator<<(ostream& os, const StringUniquePtr& string_unique_ptr);
		friend StringUniquePtr operator+(const StringUniquePtr& string_unique_ptr1, const StringUniquePtr& string_unique_ptr2);

	private:
		std::unique_ptr<char> buff_;
	};

	std::ostream& operator<<(ostream& os, const StringUniquePtr& string_unique_ptr) {
		os << string_unique_ptr.buff_;
		return os;
	}
	StringUniquePtr operator+(const StringUniquePtr& string_unique_ptr1, const StringUniquePtr& string_unique_ptr2) {
		StringUniquePtr temp;
		//make_shared �ȵǰ� shared_ptr�ȴ�..?
		temp.buff_.reset(new char[strlen(string_unique_ptr1.buff_.get()) + strlen(string_unique_ptr2.buff_.get()) + 1]);////// reset? 
		strcpy(temp.buff_.get(), string_unique_ptr1.buff_.get());
		strcat(temp.buff_.get(), string_unique_ptr2.buff_.get());
		return temp; // ���Ͽ� �ӽ� ��ü ��ȯ ->  rvalue ref!
	}
}


int main() {

	_CrtMemState s, e, d;
	_CrtMemCheckpoint(&s);
	{

		std::StringUniquePtr str1 = "str1";
		std::StringUniquePtr str2 = "str2";
		std::StringUniquePtr str3 = str1 + str2;
		std::StringUniquePtr str4;
		str4 = str1 + str3;
		std::cout << "str1 : " << str1 << std::endl;
		std::cout << "str2 : " << str2 << std::endl;
		std::cout << "str3 : " << str3 << std::endl;
		std::cout << "str4 : " << str4 << std::endl;
		/*
		std::StringUniquePtr p = "dd";
		std::StringUniquePtr p2;
		std::StringUniquePtr p4 = p; // copy constructor ȣ��.
		p2 = p;
		std::StringUniquePtr p3 = p2 + "hh" + p; // �̵� ������ ȣ��...?
		std::StringUniquePtr p5;
		p5 = p3 + "dd";
		std::cout << p << std::endl;
		std::cout << p2 << std::endl;
		std::cout << p3 << std::endl;
		// new�� ���ο� �޸� �Ҵ�� �� std::cout �ϰ� �ؼ� �޸𸮰� ���� �Ҵ���� �ʴ´ٴ� ���� Ȯ������.
		std::StringUniquePtr p = "aa";
		std::StringUniquePtr p2 = "bb";
		std::StringUniquePtr p3 = p + p2 + "cc";
		std::StringUniquePtr p4;
		p4 = "ddd" + p;
		std::cout << p3 << std::endl;
		*/
	}
	_CrtMemCheckpoint(&e);
	if (_CrtMemDifference(&d, &s, &e)) {
		_CrtDumpMemoryLeaks();
		printf("leaks : %d\n", (int)d.lSizes[1]);
	}
	else printf("perfect!\n");
}