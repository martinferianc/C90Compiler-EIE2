int d(){
  return 20;
}

int main()
{
    int a;
    a = 20;
    a = (d() - d())*d();
    return a;
}
