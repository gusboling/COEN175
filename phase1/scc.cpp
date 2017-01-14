#include <iostream>
#include <string>
#include <cassert>

using namespace std;

string read_input();
size_t grab_whitespace(string &parse_input);
size_t grab_number(string &parse_input);

int main(){
	size_t buffer_position = 0;
	size_t token_length = 0;
	string token = "";
	string parse_buffer = read_input();
	
	cerr << "Starting main parse loop." << endl;
	while(parse_buffer.length() > 0){
	
		token_length = 0;
		token = "";
	
		token_length = grab_whitespace(parse_buffer);	
		if(token_length){ //Activates if the first character of parse_string is whitespace
			//Delete all consecutive whitespace characters starting with the implied whitespace character at parse_buffer[0]
			parse_buffer.erase(0, token_length);
			//Output appropriate string
		}
		
		token_length = grab_number(parse_buffer);
		if(token_length){ //Activates if the first character of the parse_string is part of a valid number token.
			//Delete the consecutive string of numbers with it's most significant digit at parse_buffer[0]
			token = parse_buffer.substr(0, token_length);
			parse_buffer.erase(0, token_length);
			//Output appropriate string
			cout << "number: " << token << endl;
		}
		
		if(!token_length){
			parse_buffer.erase(0,1);//Delete first character if no token is present.
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
	char front = parse_input[0];
	cerr << "(Starting numbers parse sub-loop; ";	

	while((result < parse_input.length()) && isdigit(front) ){
		front = parse_input[result];
		result++;
	} 

	cerr << "Exited numbers parse sub-loop; " ;
	cerr << "Returned " << result << ") "  << endl;
	return result; 
}

//Returns 0 if first character of the string is not whitespace. Otherwise returns the number of consecutive whitespace characters following the first character.
size_t grab_whitespace(string &parse_input){
	size_t result = 0;
	char front = parse_input[0];
	cerr << "(Starting whitespace parse sub-loop; ";
	while( (result < parse_input.length()) && ( (front==' ')||(front=='\t')||(front=='\n')||(front=='\f')||(front=='\v')||(front=='\r') ) ){
		front = parse_input[result];
		result++;
	}
	cerr << "Exited whitespace parse sub-loop; ";
	cerr << "Returned " << result << ")" << endl;	
	return result;
}

//Returns 0 if first character is not part of a valid operator. Otherwise returns the number of characters in the operator at the front of the string.
size_t grab_operator(string &parse_input){
	size_t result = 0;
	return result;
}

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

//Returns 0 if first character is not part of a valid identifier. Otherwise returns the number of characters in the string at the front of the string.
size_t grab_identifier(){
	size_t result = 0;
	return result;
}
