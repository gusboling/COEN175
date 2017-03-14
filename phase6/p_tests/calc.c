/* Oh, for the lack of character constants */

int ADD, SUB, MUL, DIV, NUM, LF, LPAREN, RPAREN;
int lookahead, expr(void);

int c, lexval;

int lexan(void)
{
    int n;


    if (c == 0)
	c = getchar();

    while (isspace(c) && c != LF)
	c = getchar();

    if (!isdigit(c)) {
	int x;
	x = c;
	c = 0;
	return x;
    }

    n = 0;

    while (isdigit(c)) {
	n = n * 10 + c - 48;
	c = getchar(c);
    }

    lexval = n;
    return NUM;
}


/* Look familiar? */

void match(int token)
{
    if (lookahead != token) {
	printf("syntax error at %d\n", lookahead);
	exit(1);
    }

    lookahead = lexan();
}


int factor(void)
{
    int n;


    if (lookahead == LPAREN) {
	match(LPAREN);
	n = expr();
	match(RPAREN);
	return n;
    }

    n = lexval;
    match(NUM);
    return n;
}


int term(void)
{
    int n;
    
    
    n = factor();

    while (lookahead == MUL || lookahead == DIV) {
	if (lookahead == MUL) {
	    match(MUL);
	    n = n * factor();

	} else {
	    match(DIV);
	    n = n / factor();
	}
    }

    return n;
}


int expr(void)
{
    int n;


    n = term();

    while (lookahead == ADD || lookahead == SUB) {
	if (lookahead == ADD) {
	    match(ADD);
	    n = n + term();

	} else {
	    match(SUB);
	    n = n - term();
	}
    }

    return n;
}

int main(void)
{
    int n;


    LF = 10;
    LPAREN = 40;
    RPAREN = 41;
    MUL = 42;
    ADD = 43;
    SUB = 45;
    DIV = 47;
    NUM = 256;

    lookahead = lexan();

    while (lookahead != -1) {
	n = expr();
	printf("%d\n", n);

	while (lookahead == LF)
	    match(LF);
    }
}
