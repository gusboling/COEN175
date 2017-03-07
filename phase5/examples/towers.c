/* Link your generated assembly code for this file with towers-lib.c */

void call_towers(int n, int from, int to, int spare);
void print_move(int from, int to), print(int n);

int towers(int n, int from, int to, int spare)
{
    call_towers(n, from, spare, to);
    print_move(from, to);
    call_towers(n, spare, to, from);
}

int main(void)
{
    int n;

    n = 3;
    print(n);
    towers(n, 1, 2, 3);
}
