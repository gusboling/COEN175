#include <iostream>
#include "tokens.h"
#include "lexer.h"

using namespace std;

string lex_buff;

void print_token(int token){

  //Check token category, then print the appropriate output and debugging messages.

  if(token == ERROR){
    cout << "[ERROR] Error token detected. Exiting (" << token << ")." << endl;
    exit(1);
  }
  else if(token >= AUTO && token <= WHILE){
    cout << "keyword: " << lex_buff << endl;
    cerr << "[INFO] Keyword token detected (" << token << ")." << endl;
  }
  else if(token == NUM){
    cout << "keyword: " << lex_buff << endl;
    cerr << "[INFO] Number token detected (" << token << ")." << endl;
  }
  else if(token == STRING){
    cout << "string: " << lex_buff << endl;
    cerr << "[INFO] Number token detected (" << token << ")." << endl;
  }
  else if(token == ID){
    cout << "identifier: " << lex_buff << endl;
    cerr << "[INFO] Identifier token detected (" << token << ")." << endl;
  }
  else{
    cout << "operator: " << lex_buff << endl;
    cerr << "[INFO] Operator token detected (" << token << ")." << endl;
  }

  return;
}

int main(){

  //Get initial token
  int lookahead = lexan(lex_buff);

  //While EOF token not encountered, print current token, then get next token.
  while(lookahead != DONE){
    print_token(lookahead);
    lookahead = lexan(lex_buff);
  }

  //All done.
  return 0;
}
