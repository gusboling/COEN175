/* conflicting.c */

int x;
int x;

int a[10];
int a[5];			/* conflicting types for 'a' */

void *x;			/* conflicting types for 'x' */

int g(void);
int *g(void);			/* conflicting types for 'g' */

int *f(int q);

int *f(int z)
{
}

int f;				/* conflicting types for 'f' */

int h;
int h(void);			/* conflicting types for 'h' */
