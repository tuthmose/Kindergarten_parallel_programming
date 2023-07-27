void foo(int *__restrict a, int *b, int *__restrict c)
{
    *a = 1492;
    *b = 1789;
    *c = *a;
}

int main()
{
    int *a, *b, *c;
    foo(a,b,c);
}