int f(int x);

int f(int x)
{
  if (x==123)
    return 9;
}


int main()
{
    return !(9 == f(123));
}
