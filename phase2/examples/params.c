/* params.c */

int foo(int x, int y), bar(void *p, int x);

int foo(int x, int y)
{
    return -x + !y * 10 != 3;
}
