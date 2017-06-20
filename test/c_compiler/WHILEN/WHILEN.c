int f(int a)
{
  int i=0;
  while(a){
    a--;
    i+=2;
  }
  return i;
}

int main()
{
  int i = f(12);
  if (i==24)
    return 0;
  else
    return 1;
}
