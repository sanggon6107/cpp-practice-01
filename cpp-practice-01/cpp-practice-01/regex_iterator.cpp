#include <iostream>
#include <string>
#include <regex>

using namespace std;

// regex_iterator는 regex_search 반복수행한다.
// delimiter 기준으로 토큰화할 때는 regex_token_iterator가 편리하다.

int main()
{
	string text = "1, 2, 3, 4, 5, 6, 7, 8";

	regex re(",");
	regex re2(",([^,]*)");

	auto itr_text_bgn = begin(text);
	auto itr_text_end = end(text);
	
	
	// sregex_iterator
	auto itr_begin = sregex_iterator(itr_text_bgn, itr_text_end, re2); 
	auto itr_end = sregex_iterator();

	while ( itr_begin != itr_end )
	{
		cout << (*itr_begin)[1] << " ";  // 2부터 8까지.
		++itr_begin;
	}
	cout << endl;

	itr_text_bgn = begin(text);


	auto itr_token_begin = sregex_token_iterator(itr_text_bgn, itr_text_end, re, -1); // 마지막 인자 -1은 regex 객체에 매치되지 않는 문자를 찾겠다는 뜻.
	auto itr_token_end = sregex_token_iterator();

	while (itr_token_begin != itr_token_end)
	{
		cout << itr_token_begin->str() << " ";  // 1부터 8까지.
		cout << *itr_token_begin << " "; // 암시적 형변환?
		++itr_token_begin;
	}
	cout << endl;

}