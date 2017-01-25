/* sum.c */

int main(void)
{
    int i, n, the_sum;

    the_sum = 0;
    n = 10;

    for (i = 0; i <= n; i = i + 1) {
	the_sum = the_sum + i;
    }

    printf("%d %d\n", the_sum, n * (n + 1) / 2);
}
