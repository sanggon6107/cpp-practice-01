#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <cstring>

// 생성자.
// 복사생성자(대입, 복사)
// 대입 연산자
// +연산
// 초기화 하지 않아도 스트링 선언할 수 있도록?

// shared_ptr도 memory leak에서 안전하지 않다. 참조 계수 기반이기 때문에 서로 서로를 가리키게 되면 서클이 생기게 되고, 객체가 사라져도 
// 카운팅이 1에서 줄지 않아서 메모리 릭이 생기는 것.

// get인가? 직접적으로 주소에 접근할 수 있게 해주는 멤버 함수가 있었다.(생성자...)

namespace std {
	class StringSharedPtr {
	public:
		StringSharedPtr() = default;

		StringSharedPtr(const char* s) : buff_(new char[strlen(s) + 1]) {// : buff_(new char[strlen(s)+1])
			std::cout << "constructor" << std::endl;
			// buff_ = make_shared<char>(s); // make_shared의 정체? -> new object를 만드는 것.
			// std::cout << *buff_ << std::endl;
			strcpy(buff_.get(), s);
		}
		StringSharedPtr(const StringSharedPtr& string_shared_ptr) : buff_(string_shared_ptr.buff_) { // 복사생성자. // 이것은 딥 카피인가? // : buff_(new char[strlen(string_shared_ptr.buff_.get())+1])
			// 얕은 복사
			// buff_ = make_shared<char>( string_shared_ptr);
			// strcpy(buff_.get(), string_shared_ptr.buff_.get()); // 전혀 shared_ptr의 특성을 이용하고 있지 않은 것 같다.

			std::cout << "copy constructor" << std::endl;
			// *this = string_shared_ptr; // -> 실패.
			// shared_ptr의 특성을 버리고 딥카피 할 것인가, 아니면 shared_ptr의 특성(얕은 복사)을 활용할 것인가?
		}
		~StringSharedPtr() = default;


		StringSharedPtr& operator=(const StringSharedPtr& string_shared_ptr) {
			// 자기 자신과의 조사.. 가리키는 주소가 같으면... 
			if (buff_.get() == string_shared_ptr.buff_.get()) {
				return *this;
			};
			//this->buff_.reset(new char[strlen(string_shared_ptr.buff_.get()) + 1]); // reset..?? 그냥 주소만 바꾸면 되는 것 아닌가..
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
		//make_shared 안되고 shared_ptr된다..?
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