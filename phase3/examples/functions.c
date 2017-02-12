/* functions.c */

int foo(int x, int y);
int bar(int x, void *p);

int foo(int a, int b) {
    bar(1, 0);
    foobar();
}

char foo(int x);		/* conflicting types for 'foo' */

int bar(int a, void *q);

int bar(int i, void *j) {
}

void foobar(void) {		/* conflicting types for 'foobar' */
}
