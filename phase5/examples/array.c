/* Link your generated assembly code for this file with array-lib.c */

int a[10];
void init_array(int n), print_array(int n);

int main(void)
{
    int n;

    n = 10;
    init_array(n);
    print_array(n);
}
