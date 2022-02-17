#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <cstring>

// ������.
// ���������(����, ����)
// ���� ������
// +����
// �ʱ�ȭ ���� �ʾƵ� ��Ʈ�� ������ �� �ֵ���?

// shared_ptr�� memory leak���� �������� �ʴ�. ���� ��� ����̱� ������ ���� ���θ� ����Ű�� �Ǹ� ��Ŭ�� ����� �ǰ�, ��ü�� ������� 
// ī������ 1���� ���� �ʾƼ� �޸� ���� ����� ��.

// get�ΰ�? ���������� �ּҿ� ������ �� �ְ� ���ִ� ��� �Լ��� �־���.(������...)

namespace std {
	class StringSharedPtr {
	public:
		StringSharedPtr() = default;

		StringSharedPtr(const char* s) : buff_(new char[strlen(s) + 1]) {// : buff_(new char[strlen(s)+1])
			std::cout << "constructor" << std::endl;
			// buff_ = make_shared<char>(s); // make_shared�� ��ü? -> new object�� ����� ��.
			// std::cout << *buff_ << std::endl;
			strcpy(buff_.get(), s);
		}
		StringSharedPtr(const StringSharedPtr& string_shared_ptr) : buff_(string_shared_ptr.buff_) { // ���������. // �̰��� �� ī���ΰ�? // : buff_(new char[strlen(string_shared_ptr.buff_.get())+1])
			// ���� ����
			// buff_ = make_shared<char>( string_shared_ptr);
			// strcpy(buff_.get(), string_shared_ptr.buff_.get()); // ���� shared_ptr�� Ư���� �̿��ϰ� ���� ���� �� ����.

			std::cout << "copy constructor" << std::endl;
			// *this = string_shared_ptr; // -> ����.
			// shared_ptr�� Ư���� ������ ��ī�� �� ���ΰ�, �ƴϸ� shared_ptr�� Ư��(���� ����)�� Ȱ���� ���ΰ�?
		}
		~StringSharedPtr() = default;


		StringSharedPtr& operator=(const StringSharedPtr& string_shared_ptr) {
			// �ڱ� �ڽŰ��� ����.. ����Ű�� �ּҰ� ������... 
			if (buff_.get() == string_shared_ptr.buff_.get()) {
				return *this;
			};
			//this->buff_.reset(new char[strlen(string_shared_ptr.buff_.get()) + 1]); // reset..?? �׳� �ּҸ� �ٲٸ� �Ǵ� �� �ƴѰ�..
			// strcpy(buff_.get(), string_shared_ptr.buff_.get());
			buff_ = string_shared_ptr.buff_;
			return *this;

		}
		friend ostream& operator<<(ostream& os, const StringSharedPtr& string_shared_ptr);
		friend StringSharedPtr operator+(const StringSharedPtr& string_shared_ptr1, const StringSharedPtr& string_shared_ptr2);
	private:
		std::shared_ptr<char> buff_;

	};

	std::ostream& operator<<(ostream& os, const StringSharedPtr& string_shared_ptr) {
		os << string_shared_ptr.buff_;
		return os;
	}
	StringSharedPtr operator+(const StringSharedPtr& string_shared_ptr1, const StringSharedPtr& string_shared_ptr2) {
		StringSharedPtr temp;
		//make_shared �ȵǰ� shared_ptr�ȴ�..?
		temp.buff_.reset(new char[strlen(string_shared_ptr1.buff_.get()) + strlen(string_shared_ptr2.buff_.get()) + 1]);////// reset? 
		strcpy(temp.buff_.get(), string_shared_ptr1.buff_.get());
		strcat(temp.buff_.get(), string_shared_ptr2.buff_.get());
		return temp;
	}
}


int main() {

	_CrtMemState s, e, d;
	_CrtMemCheckpoint(&s);

	std::StringSharedPtr p = "abcd";

	std::StringSharedPtr p2 = p;
	p = p;
	std::StringSharedPtr p3 = "dghewrgwaeg";
	p3 = "aaa";
	p2 = p3;
	std::StringSharedPtr p4 = p2 + p3;
	//p2 + p3;
	std::cout << p << std::endl;
	std::cout << p2 << std::endl;
	std::cout << p3 << std::endl;
	std::cout << p4 << std::endl;

	p.~StringSharedPtr();
	p2.~StringSharedPtr();
	p3.~StringSharedPtr();
	p4.~StringSharedPtr();

	/*
	std::StringSharedPtr p = "aaa";
	std::StringSharedPtr p2 = "bbb";
	std::StringSharedPtr p3 = p2 + p;
	std::cout << p << std::endl;
	std::cout << p2 << std::endl;
	std::cout << p3 << std::endl;
	p.~StringSharedPtr();
	p2.~StringSharedPtr();
	p3.~StringSharedPtr();
	*/

	_CrtMemCheckpoint(&e);
	if (_CrtMemDifference(&d, &s, &e)) {
		_CrtDumpMemoryLeaks();
		printf("leaks : %d\n", (int)d.lSizes[1]);
	}
	else printf("perfect!\n");
}