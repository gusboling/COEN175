#include <iostream>
#include <string>
#include "tokens.h"
#include "lexer.h"

using namespace std;

int main(){
	string lexbuf;
	
	int lookahead = lexan(lexbuf);
	cout << "lookahead => " << lookahead << endl;
	
	while(lookahead != DONE){
		lookahead = lexan(lexbuf);
		cout << "lookahead => " << lookahead << endl;
	}
	
	return 0;
}
