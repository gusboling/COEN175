#include <iostream>
#include <string>
#include <assert>
using namespace std;

string read_input();

int main(){
	size_t buffer_position = 0;
	size_t token_length = 0;
	string parse_buffer = read_input();
	

	while(parse_buffer.length() > 0){
		
		if(token_length=grab_whitespace(parse_buffer)){ //Activates if the first character of parse_string is whitespace
			
			//Delete all consecutive whitespace characters starting with the implied whitespace character at parse_buffer[0]
			parse_buffer.erase(0, token_length);
			//Output appropriate string
			cout << "Whitespace ignored." << endl;

		}

		else if(token_length=grab_number(parse_buffer)){
			//Delete the consecutive string of numbers with it's most significant digit at parse_buffer[0]
			
			parse_buffer.erase(0, token_length);
			//Output appropriate string
			cout << "number: 
				
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
	
	char parse_zero = parse_input[0];
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
