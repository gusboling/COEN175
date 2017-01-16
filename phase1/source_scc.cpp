#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

string read_input();

bool find_at_front(string source, string target);
bool is_letter(char c);
bool is_identifier(char c);

size_t grab_whitespace(string &parse_input);
size_t grab_comment(string &parse_input);
size_t grab_number(string &parse_input);
size_t grab_operator(string &parse_input);
size_t grab_keyword(string &parse_input);
size_t grab_string(string &parse_input);
size_t grab_identifier(string &parse_input);

int main(){
	size_t buffer_position = 0;
	size_t token_length = 0;
	string token = "";
	string parse_buffer = read_input();

	while(parse_buffer.length() > 0){

		token = "";

		const size_t len_char = 1;

		size_t len_whitespace = grab_whitespace(parse_buffer);
		size_t len_comment = grab_comment(parse_buffer);
		size_t len_number = grab_number(parse_buffer);
		size_t len_operator = grab_operator(parse_buffer);
		size_t len_keyword = grab_keyword(parse_buffer);
		size_t len_identifier = grab_identifier(parse_buffer);
		size_t len_string = grab_string(parse_buffer);

		//DEBUGGING CODE: DELETE AT WILL

		//END OF DEBUGGING CODE


		if(len_whitespace){
			//Erase consecutive whitespaces starting at the first character of parse_buffer
			parse_buffer.erase(0,len_whitespace);
			//Log activity
			cerr << "[INFO] whitespace: " << len_whitespace << " spaces" << endl;
		}

		else if(len_comment){
			//Grab token
			parse_buffer.substr(0, len_comment);
			//Erase comment
			parse_buffer.erase(0, len_comment);
			//Log activity
			cerr << "[INFO] comment: " << token << endl;
		}

		else if(len_number){
			//Get the number token starting at the first character of parse_buffer
			token = parse_buffer.substr(0, len_number);
			//Erase token from buffer
			parse_buffer.erase(0, len_number);
			//Provide output
			cout << "number: " << token << endl;
			//Log activity
			cerr << "[INFO] number: " << token << endl;
		}

		else if(len_operator){
			token = parse_buffer.substr(0, len_operator);
			parse_buffer.erase(0, len_operator);
			cout << "operator: " << token << endl;
			cerr << "[INFO] operator: " << token << endl;
		}

		else if(len_keyword){
			token = parse_buffer.substr(0, len_keyword);
			parse_buffer.erase(0, len_keyword);
			cout << "keyword: " << token << endl;
			cerr << "[INFO] operator: " << token << endl;
		}

		else if(len_identifier){ //Always have this clause below the 'len_keyword' clause, in order to ensure that keywords get matched before identifiers
			token = parse_buffer.substr(0, len_identifier);
			parse_buffer.erase(0, len_identifier);
			cout << "identifier: " << token << endl;
			cerr << "[INFO] identifier: " << token << endl;
		}

		else{
			//If none of the prior checks found a valid token starting at the first character of parse_buffer,
			//then delete the first character and move on.
			token = parse_buffer.substr(0,1);
			parse_buffer.erase(0, 1);
			//Log activity
			cerr << "[INFO] illegal: " << token << endl;
		}
	}

	return 0; //END OF MAIN
}



//Returns the input of cin.get() until cin.eof()==true
string read_input(){
	string input_buffer = "";
	while(!cin.eof()){
		input_buffer += cin.get();
	}
	return input_buffer;
}

//Returns true if the string 'target' can be found in the string 'source', starting with the first character of 'source'.
bool find_at_front(string source, string target){
	bool result = (target==source.substr(0,target.length()));
	return result;
}

//Returns true if the character 'c' is within the set [_a-zA-Z], returns false otherwise (Note: a underscore is considered a letter within this function)
bool is_letter(char c){
	if( (c>96) && (c<123) ) return true; //lowercase clause
	else if( (c>64) && (c<91) ) return true; //uppercase clause
	else if( c==95 ) return true;
	else return false;
}

//Returns true if the character 'c' is within the set [_a-zA-Z0-9], returns false otherwise.
bool is_identifier(char c){
	if( is_letter(c) || isdigit(c) ) return true;
	else return false;
}

//Returns 0 if first character of the string is not a number. Otherwise, returns the number of consecutive digits following the first character.
size_t grab_number(string &parse_input){
	size_t result = 0;
	char front = parse_input[0];

	while((result < parse_input.length()) && (isdigit(front)) ){
		if(result==0) cerr << "[GRAB_NUMBER][START] Starting numbers parse sub-loop; ";
		front = parse_input[result];
		result++;
	}
	if(result>0) result--;
	if(result!=0) cerr << "[STOP] Exited numbers parse sub-loop; Returned " << result << endl;
	return result;
}

//Returns 0 if first character of the string is not whitespace. Otherwise returns the number of consecutive whitespace characters following the first character.
size_t grab_whitespace(string &parse_input){
	size_t result = 0;
	char front = parse_input[0];
	while( (result < parse_input.length()) && ( (front==' ')||(front=='\t')||(front=='\n')||(front=='\f')||(front=='\v')||(front=='\r') ) ){
		if(result==0) cerr<<"[GRAB_WHITESPACE][START] Entered whitespace parse sub-loop; ";
		front = parse_input[result];
		result++;
	}
	if(result>0) result--;
	if(result!=0) cerr << "[STOP] Exited whitespace parse sub-loop; Returned " << result << endl;
	return result;
}

//Returns 0 if first character is not part of a valid operator. Otherwise returns the number of characters in the operator at the front of the string.
size_t grab_operator(string &parse_input){
	size_t result = 0;
	char front = parse_input[0];
	switch(front){
		//Note: no 'break' statements are used in this switch statement, due to the way the function returns.
		//Single-character operators; a.k.a. low-hanging fruit
		case '*':
		case '/':
		case '.':
		case ',':
		case '%':
		case ':':
		case ';':
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
			result=1;
			break;

		//Double-character operators
		case '+':
			//Tests for '+' and '++'
			if((parse_input.length()>1) && (parse_input[1]==front)) result=2;
			else result=1;
			break;

		case '-':
			//Tests for '-', '--', and '->'
			if((parse_input.length()>1) && ((parse_input[1]=='>')||(parse_input[1]==front))) result=2;
			else result=1;
			break;

		case '!':
			//Tests for '!' and '!='
			if((parse_input.length()>1) && (parse_input[1]=='=')) result=2;
			else result=1;
			break;

		case '>':
		case '<':
			//Tests for '<', '>', '<=', and '>='
			if((parse_input.length()>1) && (parse_input[1]=='=')) result=2;
			else result=1;
			break;

		case '&':
		case '=':
			//Tests for '&', '&&', '=', and '=='
			if((parse_input.length()>1) && (parse_input[1]==front)) result=2;
			else result=1;
			break;

		case '|':
			//Tests for '||'
			if((parse_input.length()>1) && (parse_input[1]==front)) result=2;
			break;

		default:
			//No valid operator characters found
			break;
	}
	if(result!=0) cerr << "[GRAB_OPERATOR][SWITCH] Returned " << result << endl;
	return result;
}

//Returns 0 if first character is not part of a valid keyword. Otherwise returns the number of characters in the keyword at the front of the string.
size_t grab_keyword(string &parse_input){
	size_t result = 0;
	char front = parse_input[0];

	cerr << "[GRAB_KEYWORD] Entered keyword switch." << endl;

	switch(front){

		//Single-keyword first characters:
		case 'a':
			if(find_at_front(parse_input, "auto")) result=4;
			cerr << "[GRAB_KEYWORD][INFO] 'a' detected" << endl;
			break;

		case 'b':
			if(find_at_front(parse_input, "break")) result=5;
			break;

		case 'g':
			if(find_at_front(parse_input, "goto")) result=4;
			break;

		case 'l':
			if(find_at_front(parse_input, "long")) result=4;
			break;

		case 't':
			if(find_at_front(parse_input, "typedef")) result=7;
			break;

		case 'w':
			if(find_at_front(parse_input, "while")) result=5;
			break;

		//Multi-keyword first characters:
		case 'c':
			if(find_at_front(parse_input, "case") || find_at_front(parse_input, "char")) result=4;
			else if(find_at_front(parse_input, "const")) result=5;
			else if(find_at_front(parse_input, "continue")) result=8;
			break;

		case 'd':
			if(find_at_front(parse_input, "default")) result=7;
			else if(find_at_front(parse_input, "double")) result=6;
			else if(find_at_front(parse_input, "do")) result=2;
			break;

		case 'e':
			if(find_at_front(parse_input, "else") || find_at_front(parse_input, "enum")) result=4;
			else if(find_at_front(parse_input, "extern")) result=6;
			break;

		case 'f':
			if(find_at_front(parse_input, "float")) result=5;
			else if(find_at_front(parse_input, "for")) result=3;
			break;

		case 'i':
			if(find_at_front(parse_input, "int")) result=3;
			else if(find_at_front(parse_input, "if")) result=2;
			break;

		case 'r':
			if(find_at_front(parse_input, "register")) result=8;
			else if(find_at_front(parse_input, "return")) result=6;
			break;

		case 's':
			if(find_at_front(parse_input, "signed") || find_at_front(parse_input, "sizeof") || find_at_front(parse_input, "static") || find_at_front(parse_input, "struct")) result=6;
			else if(find_at_front(parse_input, "short")) result=5;
			break;

		case 'u':
			if(find_at_front(parse_input, "unsigned")) result=8;
			else if(find_at_front(parse_input, "union")) result=5;
			break;

		case 'v':
			if(find_at_front(parse_input, "volatile")) result=8;
			else if(find_at_front(parse_input, "void")) result=4;
			break;
		//No keywords found
		default:
			result=0;
			break;
	}

	if(result!=0) cerr << "[GRAB_KEYWORD][SWITCH] Returned " << result << endl;
	return result;
}

//Returns 0 if first character is not part of a valid identifier. Otherwise returns the number of characters in the string at the front of the string.
size_t grab_identifier(string &parse_input){
	size_t result = 0;
	size_t pos = 0;
	char front = parse_input[0];
	if(is_letter(front)){
		while( (result < parse_input.length()) && (is_identifier(front)) ){
			front = parse_input[result];
			result++;
		}
	}
	result--;
	return result;
}

//Returns 0 if first character is not part of a valid string. Otherwise returns the number of characters in the string at the front of input string.
size_t grab_string(string &parse_input){
	size_t result = 0;
	return result;
}

//Returns 0 if no comment-string is present starting at the first character, otherwise returns the length of the comment-string present.
size_t grab_comment(string &parse_input){

	size_t result = 0;
	string front_two = parse_input.substr(0,2);
	bool found_end = false;
	
	if(front_two == "/*"){

		result = result + 2; //Account for the first two characters.

		while( result < parse_input.length() ){
			//update front
			result++;
			//update front_two
			front_two = parse_input.substr(result, 2);
			//check for end of comment
			if(front_two == "*/"){
				found_end = true;
				break;
			}
		}
	}

	if(found_end){
		result = result + 2; //Account for the last two characters
		cerr << "[GRAB_COMMENT] Returned " << result << endl;
		return result;
	}
	else{
		cerr << "[GRAB_COMMENT][DEBUG] No end-comment found. Returned 0" << endl;
		return 0;
	}
}
