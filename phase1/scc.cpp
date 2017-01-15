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
	
	while(parse_buffer.length() > 0){
	
		token = "";
				
		const size_t len_char = 1;

		size_t len_whitespace = grab_whitespace(parse_buffer);
		size_t len_number = grab_number(parse_buffer);

		if(len_whitespace){
			//Erase consecutive whitespaces starting at the first character of parse_buffer
			parse_buffer.erase(0,len_whitespace);
			
			cerr << "[INFO] whitespace: " << len_whitespace << " spaces" << endl;			
		}

		else if(len_number){
			//Get the number token starting at the first character of parse_buffer
			token = parse_buffer.substr(0, len_number);
			//Erase token from buffer
			parse_buffer.erase(0, len_number);
			//Provide output
			cout << "number: " << token << endl;
			
			cerr << "[INFO] token: " << token << endl;
		}

		else{
			//If none of the prior checks found a valid token starting at the first character of parse_buffer,
			//then delete the first character and move on.
			token = parse_buffer.substr(0,1);
			parse_buffer.erase(0, 1);
			
			cerr << "[INFO] illegal: " << token << endl;	
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
