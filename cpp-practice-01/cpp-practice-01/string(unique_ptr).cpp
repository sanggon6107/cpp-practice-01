#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <memory>
#include <cstring>
#include <crtdbg.h> 

// 생성자.
// 복사생성자(대입, 복사)
// 대입 연산자
// +연산
// 초기화 하지 않아도 스트링 선언할 수 있도록?

// unique_ptr : 참조계수 기반 허용 안된다. -> 딥카피 기반으로 한다.

// 이동 생성자. : 임시 객체로 초기화 되었을 때, 임시 객체가 생성되고(임시 객체의 생성자) 그것이 아규먼트로 들어가면서 다시 생성자 호출된다. 즉, 생성자가 중복 호출된다.
//               이것을 방지하는 것이 move constructor.
// 이동 대입 연산자.


namespace std {
	class StringUniquePtr {
	public:
		StringUniquePtr() = default;
		StringUniquePtr(const char* s) : buff_(new char[strlen(s) + 1]) { // constructor.
			std::cout << "생성자 : 메모리 할당" << std::endl;
			strcpy(buff_.get(), s);
		}
		StringUniquePtr(const StringUniquePtr& string_unique_ptr) : buff_(new char[strlen(string_unique_ptr.buff_.get()) + 1]) { // 복사생성자. // 이것은 딥 카피인가? // : buff_(new char[strlen(string_unique_ptr.buff_.get())+1])
			std::cout << "복사생성자 : 메모리 할당" << std::endl;
			strcpy(buff_.get(), string_unique_ptr.buff_.get());  // copy constructor 와 constructor : 비슷?
		}
		~StringUniquePtr() {
			std::cout << "소멸자" << std::endl;
		};

		// 이동 생성자. ravlue ref는 임시 객체이다?
		StringUniquePtr(StringUniquePtr&& string_unique_ptr) noexcept : buff_(std::move(string_unique_ptr.buff_)) { // +연산으로 인해 임시 객체가 생성되고, 그 값으로 초기화했을 경우.
			std::cout << "이동 생성자 (" << buff_ << ")" << std::endl; ////
		}

		StringUniquePtr& operator=(const StringUniquePtr& string_unique_ptr) {
			std::cout << "대입 연산자 : 메모리 할당" << std::endl;
			if (buff_.get() == string_unique_ptr.buff_.get()) {
				return *this;
			};
			this->buff_.reset(new char[strlen(string_unique_ptr.buff_.get()) + 1]);
			strcpy(buff_.get(), string_unique_ptr.buff_.get());
			return *this;
		}

		StringUniquePtr& operator=(StringUniquePtr&& string_unique_ptr) noexcept {
			//이동 생성자의 의의? 깊은 복사 굳이 하지 않아도 된다. 들어온 것이 임시 객체이므로 그냥 소유권만 넘겨준다.
			//0. 위키에 의하면 이동 대입 연산자의 경우도 자신을 대입하는 경우에 대한 처리를 해야한다.
			//1. 내가 지금 가리키던 그 주소의 메모리를 해제한다.
			//2. std::move로 string_unique_ptr이 가리키는 주소를 받는다.
			std::cout << "이동 대입 연산자" << std::endl;
			if (buff_.get() == string_unique_ptr.buff_.get()) {
				return *this;
			};
			buff_ = std::move(string_unique_ptr.buff_); // 다시 메모리를 재할당할 필요 없이, move로 소유권만 이전받으면 된다.
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
		//make_shared 안되고 shared_ptr된다..?
		temp.buff_.reset(new char[strlen(string_unique_ptr1.buff_.get()) + strlen(string_unique_ptr2.buff_.get()) + 1]);////// reset? 
		strcpy(temp.buff_.get(), string_unique_ptr1.buff_.get());
		strcat(temp.buff_.get(), string_unique_ptr2.buff_.get());
		return temp; // 리턴용 임시 객체 반환 ->  rvalue ref!
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
		std::StringUniquePtr p4 = p; // copy constructor 호출.
		p2 = p;
		std::StringUniquePtr p3 = p2 + "hh" + p; // 이동 생성자 호출...?
		std::StringUniquePtr p5;
		p5 = p3 + "dd";
		std::cout << p << std::endl;
		std::cout << p2 << std::endl;
		std::cout << p3 << std::endl;
		// new로 새로운 메모리 할당될 때 std::cout 하게 해서 메모리가 따로 할당되지 않는다는 것을 확인하자.
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