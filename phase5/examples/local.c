/* Link your generated assembly code for this file with local-lib.c */

int print(int a, int b, int c);

int main(void)
{
    int x, y, z;

    x = 1;
    y = 2;
    z = 3;
    print(z, y, x);
}
