int f(int x)
{
  if (x<=1){
    return 1;
  } else {
    return f(x-1) + 1;
  }
}

int main()
{
  int i = f(12);
  return i;
}
