/* malloc.c */

int *malloc(int n);

int main(void)
{
    int n;
    int *p;

    n = 10;
    p = malloc(sizeof(int) * n);
}
