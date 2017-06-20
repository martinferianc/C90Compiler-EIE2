int main(){
  int* i;
  int* p;
  int l = 20;
  int d = 7;
  i = &d;
  p = i;
  *p = 123;
  {
    int *p;
    p = &l;
    {
      p = &d;
      return *p;
    }
  }
  return d+d+l + *p + *i;
}
