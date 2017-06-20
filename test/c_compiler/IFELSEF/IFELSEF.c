int f(int x);

int f(int x){
  if (x != 12234)
    return 19;
  else
    return 7;
}

int main()
{
  int i = f(12234);
  if (i==19)
    return 0;
  else
    return 1;
}
