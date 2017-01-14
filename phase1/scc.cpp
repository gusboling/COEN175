#include <iostream>
#include <string>

using namespace std;

string read_input();

string soft_read(char start);

int main(){
	size_t buffer_position = 0;
	string parse_buffer = read_input();

<<<<<<< HEAD
	c_buffer = cin.get();

	//unit test of soft_read function; delete when working
	string fstream = soft_read(c_buffer);

	cout << fstream << endl;

	//main parsing loop
	//NOTE: Each handler class should, at minimum, set c_buffer equal to the next character via cin.get()
	while( ! cin.eof() ){
		
		//HANDLER WHITESPACE
		if(is_whitespace(c_buffer)){
			c_buffer = cin.get();
			continue;
		}	
=======
	while(parse_buffer.length() > 0){
>>>>>>> full-read
		
		if(grab_whitespace(parse_buffer)){
			parse_buffer.erase(0,grab_whitespace(parse_buffer));
			cout << "Whitespace ignored." << endl;
		}

	}	
	
	return 0;
}

string read_input(){
	string input_buffer = "";
	while(!cin.eof()){
		input_buffer += cin.get();
	}
	return input_buffer;
}

//Returns 0 if first character of the string is not a number. Otherwise, returns the number of consecutive digits following the first character.
size_t grab_number(string &parse_input){
	size_t result = 0;
	return result; 
}

//Returns 0 if first character of the string is not whitespace. Otherwise returns the number of consecutive whitespace characters following the first character.
size_t grab_whitespace(string &parse_input){
	size_t result = 0;
	return result;
}

<<<<<<< HEAD
//Returns true if (c is a standalone operator character) or (c=='|' and c+1=='|')
bool is_operator(char c){
	bool result = false;

	//test for "||" operator		
	if(c == '|'){
		c = cin.get();
		if((!cin.eof()) && (c == '|')){
			//cin.putback(c);
			result = true;
		}
	}
	
	//test for logical operators ("&", "&&", "!", "!=", "==", "<", "<=", ">", ">=")
	//NOTE: testing for "&&", "!=", "==", "<=", and ">=" is implied by testing for their first characters,
	//	which are also operators in their own right.
	if((c=='&') || (c=='!') || (c=='<') || (c=='>')){
		result = true;	
	}
	
	//test for arithmetic operators ("+", "++", "-", "--", "/", "*", "=", "%")
	//NOTE: testing for "++" and "--" is implied by testing for their first characters, which are also operators in
	//	there own right.
	if((c=='+') || (c=='-') || (c=='/') || (c=='*') || (c=='%') || (c=='=')){
		result = true;	
	}	
=======
//Returns 0 if first character is not part of a valid operator. Otherwise returns the number of characters in the operator at the front of the string.
size_t grab_operator(string &parse_input){
	size_t result = 0;
	return result;
}
>>>>>>> full-read

//Returns 0 if first character is not part of a valid keyword. Otherwise returns the number of characters in the keyword at the front of the string.
size_t grab_keyword(string &parse_input){
	size_t result = 0;
	return result;
}

//Returns 0 if first character is not part of a valid string. Otherwise returns the number of characters in the string at the front of input string.
size_t grab_string(string &parse_input){
	size_t result = 0;
	return result;
}

<<<<<<< HEAD
//Pre-Condition: !(cin.eof())
//Post-Condition: Returns a string containing all remaining cin.get() characters, cin.get() is unchanged after read.
string soft_read(char start){
	
	string full_stream;
	full_stream += start;

	while(!cin.eof()){
		full_stream += cin.get();		
	}
	
	for(size_t i=0; i < full_stream.length(); i++){
		cin.putback(full_stream[i]);
	}		

	return full_stream;
//If c is the first character of a valid keyword, return the length of the keyword. Otherwise, return 0.
size_t is_keyword(char c){
	string keywords[32] = {"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static
=======
//Returns 0 if first character is not part of a valid identifier. Otherwise returns the number of characters in the string at the front of the string.
size_t grab_identifier(){
	size_t result = 0;
	return result;
>>>>>>> full-read
}
