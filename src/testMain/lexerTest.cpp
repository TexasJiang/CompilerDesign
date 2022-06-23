#include "lexer.h"
#include<string.h>
#include<iostream>
using namespace std;

int main() {
	string sourseFile;
	cin >> sourseFile;
	Tokenizer lexer;
	lexer.load_source_file(sourseFile.c_str());
	lexer.scan();
	while (1) {
		if (lexer.token_index == lexer.tokens_buffer.len)
			break;
		Token* token = lexer.token();
		string result = token_to_desc(token);
		cout << result << endl;
		lexer.eat();
	}
}
