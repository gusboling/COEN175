/* undeclared.c */

void f(int x)
{
    x = y;			/* 'y' undeclared */
}


int g(int x, int y)
{
    int z;

    x = y + z + p();
}


int x;

char **h(int y)
{
    int z;

    x = y + z + w;		/* 'w' undeclared */
}
