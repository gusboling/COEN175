#include <iostream>
#include <string>

using namespace std;

bool is_whitespace(char c);
bool is_digit(char c);
bool is_operator(char c);

string soft_read(char start);

int main(){
	char c_buffer;
	string s_buffer;

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
		
		//HANDLE NUMBERS
		if(is_digit(c_buffer)){

			//while c_buffer is a digit, append it to s_buffer and get the next c_buffer value.
			while( !cin.eof() && is_digit(c_buffer) ){
				s_buffer += c_buffer;	
				c_buffer = cin.get();
			}
		
			//generate output and clear s_buffer.	
			cout << "number: " << s_buffer << endl;
			s_buffer.clear();
			continue;
		}

		//HANDLE STRINGS
		//HANDLE IDENTIFIERS
		//HANDLE KEYWORDS
		
		//HANDLE OPERATORS
		if(is_operator(c_buffer)){
			//current character is operator
			s_buffer += c_buffer;
			c_buffer=cin.get();

			//test for duplicate second operator character; if found, append to s_buffer.
			if((s_buffer=="=") || (s_buffer=="&") || (s_buffer=="+") || (s_buffer=="-")){
				if(s_buffer[0] == c_buffer){
					s_buffer += c_buffer;
				}	
			}
		
			//test for different second operator character; if found, append to s_buffer.
			else if((s_buffer=="!") && (c_buffer=='=')){
				s_buffer += c_buffer;
			}

			else if((s_buffer=="<") && (c_buffer=='=')){
				s_buffer += c_buffer;
			}

			else if((s_buffer==">") && (c_buffer=='=')){
				s_buffer += c_buffer;
			}

			else if((s_buffer=="-") && (c_buffer=='>')){
				s_buffer += c_buffer;
			}	
						

			//generate output and clear s_buffer.
			cout << "operator: " << s_buffer << endl;
			c_buffer = cin.get();
			s_buffer.clear();
		}
		
		//HANDLE COMMENTS			
		else{
			c_buffer=cin.get();
		}
	}


	return 0;
}

//Returns true iff c is a digit [0,9]
bool is_digit(char c){
	return isdigit(c);
}

//Returns true iff c is equal to a whitespace character.
bool is_whitespace(char c){
	bool result = false;
	if( (c == ' ') || (c=='\t') || (c=='\n') || (c=='\f') || (c=='\v') || (c=='\r') ){
		result = true;
	}
	return result;
}

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

	//test for misc. operators ("->", ".", ",", "(", ")", "[", "]", "{", "}", ":", ";")
	//NOTE: testing for "->" is implied by testing for its first character ("-"), which is an arithmetic operator 
	//	in its own right.
	if((c=='.') || (c==',') || (c=='[') || (c==']') || (c=='{') || (c=='}') || (c=='(') || (c==')') || (c==':') || (c==';')){
		result = true;
	}

	return result;
}

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
}
