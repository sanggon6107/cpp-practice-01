#include <iostream>
#include <string>
#include <regex>

using namespace std;

// regex_iterator�� regex_search �ݺ������Ѵ�.
// delimiter �������� ��ūȭ�� ���� regex_token_iterator�� ���ϴ�.

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
		cout << (*itr_begin)[1] << " ";  // 2���� 8����.
		++itr_begin;
	}
	cout << endl;

	itr_text_bgn = begin(text);


	auto itr_token_begin = sregex_token_iterator(itr_text_bgn, itr_text_end, re, -1); // ������ ���� -1�� regex ��ü�� ��ġ���� �ʴ� ���ڸ� ã�ڴٴ� ��.
	auto itr_token_end = sregex_token_iterator();

	while (itr_token_begin != itr_token_end)
	{
		cout << itr_token_begin->str() << " ";  // 1���� 8����.
		cout << *itr_token_begin << " "; // �Ͻ��� ����ȯ?
		++itr_token_begin;
	}
	cout << endl;

}