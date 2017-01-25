/* sum.c */

int main(void)
{
    int i, n, sum;

    i = 0;
    sum = 0;
    n = 10;

    while (i <= n) {
	sum = sum + i;
	i = i + 1;
    }

    printf("%d %d\n", sum, n * (n + 1) / 2);
}
