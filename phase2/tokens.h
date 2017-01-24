enum{
	ERROR=256, DONE, ID, NUM, STRING, AUTO, //JESSE'S SUGGESTIONS
	BREAK, CASE, CHAR, CONST, CONTINUE,
	DEFAULT, DO, DOUBLE, ELSE, ENUM,
	EXTERN, FLOAT, FOR, GOTO, IF,
	INT, LONG, REGISTER, RETURN, SHORT,
	SIGNED, SIZEOF, STATIC, STRUCT,
	SWITCH, TYPEDEF, UNION, UNSIGNED,
	VOID, VOLATILE, WHILE, OR, AND,
	EQUAL, NOTEQUAL, GREATERTHANOREQUAL,
	LESSTHANOREQUAL, INCREMENT, //END OF JESSE'S SUGGESTIONS

	INDEX, 			//Not sure how to deal with index operator; treating it like a two-character operator for now
	POINTER,		//Not sure how to deal with '->' operator; treating it like a two-character operator for now
	DEREF,			//Character conflict with multiplication operator
	NEGATIVE,		//Character conflict with subtraction operator

	ADDR='&',
	NOT='!',
	MUL='*',
	DIV='/',
	REM='%',
	ADD='+',
	SUB='-',
	LTN='<',
	GTN='>',
	ASG='=',
	COLON=':',
	SEMICOLON=';',
	LBRACKET='[',
	RBRACKET=']',
	LBRACE='{',
	RBRACE='}',
	LPAREN='(',
	RPAREN=')',
	COMMA=',',
	PERIOD='.'

};
