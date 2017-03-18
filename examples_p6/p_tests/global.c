/* global.c */

int x;

int foo(void)
{
    x = x + 1;
    return x + 1;
}

int main(void)
{
    x = 65;
    putchar(x);
    putchar(foo());
    putchar(x);
    putchar(10);
}
